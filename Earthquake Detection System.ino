/* REX ENGINEERING SERVICES
   www.rex-es.com
*/ 
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Network Credentials
const char* ssid = "REX-ES";
const char* password = "RES12345";

int val;
uint16_t raw;

AsyncWebServer server(80);  // Create WebServer object on port 80

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin())
  {
    Serial.println("webpage error eeprom");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/AnalogValue", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", ReadSensor().c_str());
  });


  // Start server
  server.begin();
}


String ReadSensor()
{
  raw = analogRead(34);

  val = map(raw, 0, 4095, 0, 180);

  return String(val);
}


void loop()
{

}
