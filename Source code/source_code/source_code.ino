int mq3_analogPin = A0; // connected to the output pin of MQ3 
int count=0;
int motorpin=4;
#include <SoftwareSerial.h>
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
  
}

void loop()
{
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

