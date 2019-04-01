#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>

SoftwareSerial mySerial(13, 15);
TinyGPS gps;


void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);
int AOUTpin= A0;
int DOUTpin= D0;
int value;

void setup()  
{ 
  pinMode(DOUTpin, INPUT);
  Serial.begin(115200);
  mySerial.begin(9600);
  delay(5000);
}



void loop()                                 
{
//=================================================================   Idle   
if (Serial.available()) 
{
char alamat=Serial.read();
    if (alamat=='1')
    {
    Serial.println("   Data Realtime Jumlah CO  ");
    Serial.println(" serta posisi alat pengukur ");
    Serial.println("    (UTC +07:00 Jakarta)    ");
    Serial.println("----------------------------");
    gpsdump(gps);delay(5000);
    Serial.println("----------------------------");
    Serial.println();
    }
 
void gpsdump(TinyGPS &gps)
  { 
  long lat, lon;
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
}
}
