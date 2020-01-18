#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

String  i;
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

  }
  Serial.println("Connected");

}


void loop()
{

    i = (SendWithAnswer("192.168.4.1","Yes"));
    i.remove(0, 25);
    i.remove(i.length()-11,11);
    Serial.println(i);

}
