//  ============================================================================================================
//                      PROGRAM SISTEM AKUSISI DATA COAL BED METHANE 
//  ======================================================================================= mBAh Buyut Singoranu


//========================================================================================= Preprocessing
          int     ADC_suhu,ADC_tekanan,suhu;
          
volatile  int     pulsa;                              //variable yang akan dicacah
          float   kalk,frek,kece1,kece2,debit;
          float   tekanan,hasil;                               
    

//================================================================================================ Preprocessing
void rpm()                                            //memanggil fungsi interupsi 
{ 
  pulsa++;                                            //mencacah keluaran dari sensor
} 


//=============================================================================================== Setup
void setup() 
{
pinMode(12, OUTPUT);      // Power
pinMode(11, OUTPUT);      // Serial
pinMode(10, OUTPUT);      // ADC
pinMode(9, OUTPUT);       // Flow
pinMode(3, OUTPUT);       // ADC
pinMode(2, OUTPUT);       // Flow

Serial.begin(9600);
pinMode(43, INPUT);                                 //inisialisasi pin 43 sebagai input hall sensor
attachInterrupt(43, rpm, RISING);                   //menggunakan mode rising dalam counter
digitalWrite(12, LOW);
}

 
//============================================================================================== Program Utama
void loop()
{ 
digitalWrite(11, HIGH);
digitalWrite(10, HIGH);
digitalWrite(9, HIGH);
digitalWrite(3, LOW);                     // Relay Depan
digitalWrite(2, LOW);                     // Relay Belakang


//=================================================================   Idle   
if (Serial.available()) 
{
char alamat=Serial.read();
digitalWrite(11, LOW);
      
//=================================================================   Alamat 1 = suhu 
    if (alamat=='1')
    {
      digitalWrite(10, LOW);            // Indikator LED
      analogReadResolution(12);       
      ADC_suhu=analogRead(A6);
      Serial.print(ADC_suhu,1);  
                   
    } 
//================================================================   Alamat 1 = suhu     
    if (alamat=='2')
    {
      digitalWrite(10, LOW); 
      analogReadResolution(12);
      ADC_tekanan=analogRead(A6);
      delay(100);
      Serial.print(ADC_tekanan,1);              
    } 
    
//================================================================   Alamat 2 = suhu         
    if (alamat=='3')
    {
      digitalWrite(9, LOW); 
      pulsa = 0;                                   
      delay (3000);                           //delay 3 detik
      kalk = ((pulsa*0.3322)+0.2208);         //frekuensi = Q x 4,8 (4,8/60) liter/sec
      frek = kalk;
      kece1 = (2*3.14*frek);
      kece2 = (kece1*0.0127);
      Serial.print(frek,1);                  //mencetak hasil dari kece 2     
    } 
 //================================================================   Alamat 4 = suhu 
    if (alamat=='4')
    {
      digitalWrite(10, LOW); 
      analogReadResolution(12);
      ADC_tekanan=analogRead(A6);
      delay(100);
      Serial.print(ADC_tekanan,1); 
                     
    } 
    
//================================================================   Alamat 5 = suhu
   if (alamat=='5')
   {
      digitalWrite(10, LOW);   
      analogReadResolution(12);
      ADC_tekanan=analogRead(A6);
      delay(100);
      Serial.print(ADC_tekanan);              
    } 

//================================================================   Alamat 6 = suhu
   if (alamat=='6')
   {
      digitalWrite(10, LOW);   
      analogReadResolution(12);
      ADC_tekanan=analogRead(A6);
      delay(100);
      Serial.print(ADC_tekanan,1);              
    } 
    

//================================================================   Alamat 7 = suhu
   if (alamat=='7')
   {
      digitalWrite(10, LOW);   
      analogReadResolution(12);
      ADC_tekanan=analogRead(A6);
      delay(100);
      Serial.print(ADC_tekanan,1);              
    }     
    
} 
}   // END       

