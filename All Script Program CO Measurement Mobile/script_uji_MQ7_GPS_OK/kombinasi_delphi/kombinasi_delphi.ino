#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(13, 15);        // Serial untuk baca GPS
TinyGPS gps;                            // Library GPS

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);
long lat, lon;
float flat, flon;
int AOUTpin= A0;
int DOUTpin= D0;
int value;

void setup()  
{
  pinMode(DOUTpin, INPUT);
  Serial.begin(115200);         // Serial COM ke komputer
  mySerial.begin(115200);
}


//======================================================================
//          PROGRAM UTAMA
//======================================================================
void loop() 
{

//=================================================================   Idle   
if (Serial.available()) 
{
char alamat=Serial.read();

//=================================================================   Alamat 1 = suhu 
    if (alamat=='1')
{
     
  bool newdata = false;
  unsigned long start = millis();
  long lat, lon;
  float flat, flon;
     
  while (millis() - start < 3000)                   // update tiap 3 detik
  {
    if (mySerial.available()) 
    
    {
      char c = mySerial.read();
      if (gps.encode(c)) 
      {
        newdata = true;
        break;  
      }
    }
  }
}
 
 //=================================================================   Alamat 2
  if (alamat=='2')
  {
  gps.f_get_position(&flat, &flon);             
  Serial.println(flat, 5);                       // Latitude
  }
  
 //=================================================================   Alamat 3
  if (alamat=='3')
  {
  Serial.println(flon,5);                        // Longitude
  } 
  
 //=================================================================   Alamat 4
  if (alamat=='4')
  {
  Serial.println(gps.f_altitude());             // Ketingginan
  }
  
//================================================================   Alamat 5
  if (alamat=='5')
  {
  value= analogRead(AOUTpin);
  Serial.println(value,5);                      // CO
  }
}}
