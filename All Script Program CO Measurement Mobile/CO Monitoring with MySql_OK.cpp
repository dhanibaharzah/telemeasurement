#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>

SoftwareSerial mySerial(13, 15);
TinyGPS gps;

IPAddress server_addr(192,168,0,100);  // IP of the MySQL *server* here
char user[] = "dhani";                 // MySQL user login username
char password[] = "1234";              // MySQL user login password

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);
int AOUTpin= A0;
int DOUTpin= D0;
int value;

const char* ssid = "IISRC";             //ssid wifi server
const char* passwordd = "tanyapaksur";  //passwordnya

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup()  
{ 
  pinMode(DOUTpin, INPUT);
  Serial.begin(115200);
  mySerial.begin(9600);
  delay(5000);

  WiFi.begin(ssid, passwordd);
  Serial.println("");
  Serial.println("WiFi Terhubung");
  Serial.println(WiFi.localIP());

  Serial.println("GPS uBlox Neo 6M");
  Serial.print("Testing TinyGPS & MQ7 CO Sensors"); 
  Serial.println(TinyGPS::library_version());
  Serial.println("by dhani dhani");
  Serial.println();
  Serial.print("Sizeof(gpsobject) = "); 
  Serial.println(sizeof(TinyGPS));
  Serial.println(); 

 if (conn.connect(server_addr, 3306, user, password)) 
  {
    delay(1000);
  }
 else
    Serial.println("Connection failed.");
}

void loop()                                 
{
  bool newdata = false;
  unsigned long start = millis();
  while (millis() - start < 5000)           // Update tiap 5 detik
  {
    if (mySerial.available())  
    {
    Serial.println("   Data Realtime Jumlah CO  ");
    Serial.println(" serta posisi alat pengukur ");
    Serial.println("    (UTC +07:00 Jakarta)    ");
    Serial.println("----------------------------");
    gpsdump(gps);delay(5000);
    Serial.println("----------------------------");
    Serial.println();
    }
  }
}

void gpsdump(TinyGPS &gps)
{ long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  gps.get_datetime(&date, &time, &age);
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);   
  Serial.print("Waktu          : "); 
  Serial.print(static_cast<int>(hour+7));  
  Serial.print(":"); 
  Serial.print(static_cast<int>(minute));
  Serial.print(" WIB"); 

Serial.println();
  Serial.print("Tanggal        : "); 
  Serial.print(static_cast<int>(day)); 
  Serial.print("/");   
  Serial.print(static_cast<int>(month)); 
  Serial.print("/"); 
  Serial.print(static_cast<int>(year));

Serial.println(); 
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Posisi Lintang : "); 
  printFloat(flat, 5);

Serial.println(); 
  Serial.print("Posisi Bujur   : "); 
  printFloat(flon, 5);

Serial.println(); 
  Serial.print("Ketinggian     : "); 
  printFloat(gps.f_altitude());
  Serial.print(" mdpl"); 

Serial.println();
  Serial.print("Kadar CO       : ");
  Serial.print(value);
  value= analogRead(AOUTpin);
  Serial.print(" ppm");
Serial.println(); 
  {
    if (value >= 300){
  Serial.println("Kategori       : BAHAYA");
    }   
    else{
  Serial.println("Kategori       : AMAN");
    }
  }
  Serial.println();
    char INSERT_SQL[200]; 
    snprintf (INSERT_SQL,200,"INSERT INTO co_monitoring.po (shape, ppm) VALUES (geomfromtext('POINT ($flat, $flon)'), $value)"); //--> Lihat Opsi Snprintf dibawah
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);        // Initiate the query class instance
    cur_mem->execute(INSERT_SQL);                           // Execute the query
    delete cur_mem;
}                                                         

void printFloat(double number, int digits)
{
  if (number < 0.0)                                     // Handle negative numbers
  {
     Serial.print('-');
     number = -number;
  }
    double rounding = 0.5;                              // Round correctly so that print(1.999, 2) prints as "2.00"
    for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
    number += rounding;
    unsigned long int_part = (unsigned long)number;     // Extract the integer part of the number and print it
    double remainder = number - (double)int_part;
    Serial.print(int_part);
    if (digits > 0)                                     // Print the decimal point, but only if there are digits beyond
      Serial.print("."); 
    while (digits-- > 0)                                // Extract digits from the remainder one at a time 
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
} 

// Note: since there are no results, we do not need to read any dat
// Deleting the cursor also frees up memory usedi
// Cari diinternet tentang MEdia penyimpanan data di my sql 


//----------------------------------------------------------- OPSI ALTERNATIF SNPRINTF -----------------------------------------------------------------------------------------------------------
//snprintf (INSERT_SQL,200,"INSERT INTO co_monitoring.po (shape, ppm) VALUES (geomfromtext('POINT (%f, %f)'), %s)"); //--> ASLI
//snprintf(INSERT_SQL,200,"INSERT INTO co_monitoring.po (shape, ppm) VALUES (geomfromtext('POINT (%f %f)'),%ld)", flat, flon, value);
//snprintf(INSERT_SQL,200,"INSERT INTO co_monitoring.po (shape, ppm) VALUES (geomfromtext('POINT Serial.print(flat,5) Serial.print(flon,5)'), Serial.print(value,5)')", flat, flon, value);
//snprintf(INSERT_SQL,200,"INSERT INTO co_monitoring.po (shape, ppm) VALUES (geomfromtext('POINT (%f %f)'),%ld)", flat, flon, value); (awal banget ) 
//char INSERT_SQL[] = "INSERT INTO officeto_plants.TBL_READINGS(ID_PLANT, AIR_HUMIDITY, AIR_TEMPERATURE, SOIL_MOISTURE_1) VALUES (1, NULL, NULL, %d)"; (source dari internet)
//snprintf(INSERT_SQL,200,"INSERT INTO co_monitoring.po (shape, ppm) VALUES (geomfromtext('POINT ("printFloat(flat, 5)" "printFloat(flon, 5)")'), "printFloat(value/20)")", flat, flon, value);
//$sql = "INSERT INTO connected_car_1.sensor (value) VALUES ('".$_GET["value"]."')"; --> belum dicoba

/*<?php --> belum dicoba juga
$result = mysql_connect("123.123.123.123", "user", "password");
$temp = $_GET["temp"];
$humi = $_GET["humi"];
$sqlt = "insert into dht22.temphumi (temp,humi) values ($temp,$humi)";
mysql_query($sqlt);
?>*/
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
