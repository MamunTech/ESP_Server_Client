#include <ESP8266WiFi.h>

WiFiServer server(80);

void setup()
{
  Serial.begin(9600);

    WiFi.disconnect();
   WiFi.begin("SSID","SSID_Password");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  }
  Serial.println("Connected");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(analogRead(A0));
    client.println("</html>");
    client.stop();
    delay(1);

}
