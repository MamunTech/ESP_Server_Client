#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

#define TRIGGER1 5 //D1
#define ECHO1    4 //D2

#define TRIGGER2 0 //D3
#define ECHO2    2 //D4

#define Relay1    13 //D7 (relay -1 helps to open the gate)
#define Relay2    15 //D8  (relay 2 helps to close the gate)

 
String  i;
long  newvar;
String  httpurl;
String  TheHiddenAnswerOfClient;
HTTPClient http;

String SendWithAnswer(String IPcache, String monmessagecache) {
httpurl = "http://";
httpurl+=IPcache;
httpurl+="/";
httpurl+=monmessagecache;
http.begin(httpurl);
http.GET();
TheHiddenAnswerOfClient = (http.getString());
http.end();
return TheHiddenAnswerOfClient;
}

void setup()
{
  i = "";

  Serial.begin(9600);

   WiFi.disconnect();
   WiFi.begin("ESP_B2F646","1234");
   while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);



  }
  Serial.println("Connected");

}


void loop()
{
    long duration1, distance1,duration2, distance2;

    i = (SendWithAnswer("192.168.4.1","Yes"));
    i.remove(0, 25);
    i.remove(i.length()-11,11);
    Serial.println(i);
    newvar = i.toInt();
    Serial.println((100 + newvar));


// distance sensor 
  digitalWrite(TRIGGER1, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER1, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER1, LOW);
  duration1 = pulseIn(ECHO1, HIGH);
  distance1 = (duration1/2) / 29.1;
  
 // Serial.print(distance1);
 // Serial.println("Centimeter:");
 // delay(1000);

  digitalWrite(TRIGGER2, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER2, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER2, LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 = (duration2/2) / 29.1;

  // Serial.print(distance2);
 // Serial.println("Centimeter:");
 // delay(1000);

 
// For gate open
 if(newvar==10 && distance1<=400)
 {
   digitalWrite(Relay1, HIGH);
   delay(60000); //1 minute opning the garage gate
   digitalWrite(Relay1, LOW);
   delay(180000); //3 minutes time gate will be stayed open
  }
// For gate close
  else
  {
    digitalWrite(Relay2, HIGH);
    delay(60000); //1 minute closing the garage gate
    digitalWrite(Relay2, LOW);
  }
  
  

}
