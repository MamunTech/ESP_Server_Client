#include <ESP8266WiFi.h>

WiFiServer server(80);

void setup()
{
  Serial.begin(9600);

  WiFi.softAP("Babu","1234");
  Serial.println((WiFi.softAPIP()));
  server.begin();

}


void loop()
{

    Serial.println("Connected station");
    Serial.println((WiFi.softAPgetStationNum()));
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(10);
    client.println("</html>");
    client.stop();
    delay(1000);

}
