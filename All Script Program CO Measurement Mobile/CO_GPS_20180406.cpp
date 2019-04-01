#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(13, 15);
TinyGPS gps;

void bacagps1(TinyGPS &gps);
void bacagps2(TinyGPS &gps);
void bacasensorco();

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
//=================================================================================
//                                      PROGRAM UTAMA
//=================================================================================
void loop() // run over and over
{
  ESP.wdtFeed();
  if (Serial.available())
   {
    char alamat=Serial.read();

      if (alamat=='1') //dicoba dirumah
    {
      bool newdata = false;
      unsigned long start = millis();
      while (millis() - start < 5000) // Every 5 seconds we print an update
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
    bacagps1(gps);
  }
}
   
   //=============================================================================

   if (alamat=='2') //dicoba dirumah
    {
      bool newdata = false;
      unsigned long start = millis();
      while (millis() - start < 5000) // Every 5 seconds we print an update
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
        bacagps2(gps);
      }
    }

//=================================================================================
   if (alamat=='3')
    {
      bacasensorco();
    }
  }
}

//=================================================================================

void bacagps1(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;

  gps.f_get_position(&flat, &flon, &age);
  printFloat(flat, 9); //latitude
}

//=================================================================================

void bacagps2(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;

  gps.f_get_position(&flat, &flon, &age);
  printFloat(flon, 9); //longitude  
}

//=================================================================================

void bacasensorco()
{
  Serial.println(value); //sensor CO
  value = analogRead(AOUTpin);
}

void printFloat(double number, int digits)
{
  Serial.println()
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
