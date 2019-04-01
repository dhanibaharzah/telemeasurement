int AOUTpin= A0;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduin
//int DOUTpin= D0;//the DOUT pin of the CO sensor goes into digital pin D8 of the arduino
//int ledPin= D0;//the anode of the LED connects to digital pin D13 of the arduino

//int limit;
int value;

void setup() {
  Serial.begin(115200);//sets the baud rate
 // pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
  //pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
}

void loop()
{
  value= analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
  //limit= digitalRead(DOUTpin);//reads the digital value from the CO sensor's DOUT pin
  Serial.print("CO value: ");
  Serial.println(value);//prints the CO value
  //Serial.print("Limit: ");
  //Serial.println(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
  //delay(350);
  //if (limit/20 == LOW){
    //digitalWrite(ledPin, LOW);//if limit has been reached, LED turns on as status indicator
  }
  //else{
    //digitalWrite(ledPin, HIGH);//if threshold not reached, LED remains off
//  }


