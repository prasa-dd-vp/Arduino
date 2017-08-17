int mq3_analogPin = A0; // connected to the output pin of MQ3 
int count=0;
int motorpin=4;
#include <SoftwareSerial.h>
#include <CayenneSerial.h>
#include "WiFiEsp.h"
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

char ssid[] = "prasad";            // your network SSID (name)
char pass[] = "12345678";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "u68oqqxl38";
SoftwareSerial gsm(2,3);
String outMessage = "DRUNK daw!";
String destinationNumber = "+919600030107";
void fun();


void setup(){
  Serial.begin(9600); // open serial at 9600 bps
  pinMode(motorpin, OUTPUT);
      //digitalWrite(motorpin, HIGH);
    //delay(1000);
    //digitalWrite(motorpin,LOW);
  //Baud rate can be specified by calling Cayenne.begin(token, 9600);
  Cayenne.begin(token);


  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network"); 
  
}

void loop()
{
  Cayenne.run();
  // give ample warmup time for readings to stabilize
  int mq3_value = analogRead(mq3_analogPin);
  Serial.println(mq3_value);

  delay(500); //Just here to slow down the output.
  if(mq3_value<340&&count==0){
    fun();    
  }
  
}
void fun()
  {
    count=1;
  gsm.begin(4800); 
  gsm.print("AT+CMGF=1\r");
  delay(1000);
  gsm.println("AT + CMGS = \"" + destinationNumber +"\"");
  delay(1000);
  gsm.print(outMessage);
  delay(1000);
  gsm.write((char)26); //ctrl+z
  delay(1000);
  gsm.println("AT+CLTS=1");
  gsm.println("AT+CCLK?");
  motor();
      
  }

  void motor()
  {
    digitalWrite(motorpin, HIGH);
    delay(450);
    digitalWrite(motorpin,LOW);
  }

