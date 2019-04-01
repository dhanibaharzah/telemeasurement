#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(13, 15);
TinyGPS gps;

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);
int AOUTpin = A0;
int DOUTpin = D0;
int value;
char c;
void setup()
{
  pinMode(DOUTpin, INPUT);
  Serial.begin(115200);
  mySerial.begin(9600);
  delay(5000);
  ESP.wdtDisable();
  
}

void loop() // run over and over
{
  ESP.wdtFeed();
  if (Serial.available())
   {
    char alamat=Serial.read();
      if (alamat='1')
      {
          bool newdata = false;
  unsigned long start = millis();
  // Every 5 seconds we print an update
  while (millis() - start < 5000) 
  {
    if (mySerial.available()) 
    
    {
      c = mySerial.read();
      //Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) 
      {
        newdata = true;
        break;  // uncomment to print new data immediately!
      }
    }
  }
  
  
  if (newdata) 
  {
//    Serial.println("   Data Realtime Jumlah CO  ");
//    Serial.println(" serta posisi alat pengukur ");
//    Serial.println("    (UTC +07:00 Jakarta)    ");
//    Serial.println("----------------------------");

    gpsdump(gps);
//    Serial.println("----------------------------");
//    Serial.println();
  }
      }
      delay(100);
   }

   
}
void gpsdump(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  //gps.get_datetime(&date, &time, &age);
//  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  //Serial.print("Waktu          : ");
  //Serial.print(static_cast<int>(hour + 7));
  //Serial.print(":");
  //Serial.print(static_cast<int>(minute));
  //Serial.print(" WIB");

  //Serial.println();
  //Serial.print("Tanggal        : ");
  //Serial.print(static_cast<int>(day));
  //Serial.print("/");
  //Serial.print(static_cast<int>(month));
  //Serial.print("/");
  //Serial.print(static_cast<int>(year));

  //Serial.println();
  gps.f_get_position(&flat, &flon, &age);
 // Serial.print("Posisi Lintang : ");
  printFloat(flat, 9);

  //Serial.println();
  //Serial.print("Posisi Bujur   : ");
  //printFloat(flon, 9);

  //Serial.println();
  //Serial.print("Ketinggian     : ");
  //printFloat(gps.f_altitude());
  //Serial.print(" mdpl");

  //Serial.println();
  //Serial.print("Kadar CO       : ");
  //Serial.print(value / 20);
  //value = analogRead(AOUTpin);
  //Serial.print(" ppm");
  //Serial.println();
  
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
    Serial.print('-');
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}

