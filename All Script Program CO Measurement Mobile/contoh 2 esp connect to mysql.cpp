#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

float memoldtmpb1=20.25;
float memoldhb1=80.78;
float memoldtmpc2=10.56;
float memoldhc2=55.08;
float memoldtmpbc=20.10;
float memoldhbc=54.00;
float memoldtmpgj=12.40;
float memoldhgj=54.00;
float memoldtmppi=28.10;
float memhpi=0;


char tmpb1[6];
char hb1[6];
char tmpc2[6];
char hc2[6];
char tmpbc[6];
char hbc[6];
char tmpgj[6];
char hgj[6];
char tmppi[6];
char hpi[6];

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte arduinoIP[] = { 192, 168, 0, 100 };    
byte gatewayIP[] = { 192, 168, 0, 1 };
byte subnetIP[] = { 255, 255, 255, 0 };
byte dnsIP[] = { 8, 8, 8, 8 };
IPAddress server_addr(5, 15, 54, 88);  // IP of the MySQL *server* here

char user[] = "arduino";              // MySQL user login username
char password[] = "myarduino";        // MySQL user login password

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr, arduinoIP, dnsIP, gatewayIP, subnetIP);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
 
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
}


void loop() {
  delay(2000);
dtostrf(memoldtmppi, 5 , 2, tmppi);
dtostrf(memhpi, 5, 2, hpi);

dtostrf(memoldtmpb1, 5 , 2, tmpb1);
dtostrf(memoldhb1, 5, 2, hb1);

dtostrf(memoldtmpc2, 5 , 2, tmpc2);
dtostrf(memoldhc2, 5, 2, hc2);

dtostrf(memoldtmpbc, 5 , 2, tmpbc);
dtostrf(memoldhbc, 5, 2, hbc);

dtostrf(memoldtmpgj, 5 , 2, tmpgj);
dtostrf(memoldhgj, 5, 2, hgj);

Serial.println(memoldtmpb1);
      Serial.println(memoldhb1);
      Serial.println("Values after converting to string:");
      Serial.println(tmpb1);
      Serial.println(hb1);
      Serial.println(tmpc2);
      Serial.println(hc2);
      
      Serial.println("Recording data.");

     insertb1();
     insertc2();
     insertbc();
    // insertgj();
    // insertpi();
}

void insertb1() {
      const char INSERT_SQL[] = {" INSERT INTO arduino_roomtemp.roomtemp (LOCATION, TEMPERATURE, HUMIDITY) VALUES ('ETAJ-DORMITOR', %s , %s)" };
      char query[255];
      sprintf(query, INSERT_SQL, tmpb1, hb1);
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(query);
      delete cur_mem;
      Serial.println("Data saved!");
      
}
 
void insertc2() {      
      const char INSERT_SQL[] = {"INSERT INTO arduino_roomtemp.roomtemp (LOCATION, TEMPERATURE, HUMIDITY) VALUES ('ETAJ-CAMERA', %s , %s)"};
      char query[255];
      sprintf(query, INSERT_SQL, tmpc2, hc2);
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(query);
      delete cur_mem;
      
      }

void insertbc() {      
      delay(1200);
      const char INSERT_SQL[] = {"INSERT INTO arduino_roomtemp.roomtemp (LOCATION, TEMPERATURE, HUMIDITY) VALUES ('BUCATARIE', %s , %s)"};
      char query[255];
      sprintf(query, INSERT_SQL, tmpbc, hbc);
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(query);
      delete cur_mem;
      
      }

void insertgj() {      
      const char INSERT_SQL[] = {"INSERT INTO arduino_roomtemp.roomtemp (LOCATION, TEMPERATURE, HUMIDITY) VALUES ('GARAJ', %s , %s)"};
      char query[255];
      sprintf(query, INSERT_SQL, tmpgj, hgj);
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(query);
      delete cur_mem;
      
      }
      void insertpi() {      
      const char INSERT_SQL[] = {"INSERT INTO arduino_roomtemp.roomtemp (LOCATION, TEMPERATURE, HUMIDITY) VALUES ('POOL WATER TEMP.', %s , %s)"};
      char query[255];
      sprintf(query, INSERT_SQL, tmppi, hpi);
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      cur_mem->execute(query);
      delete cur_mem;
      
      }




