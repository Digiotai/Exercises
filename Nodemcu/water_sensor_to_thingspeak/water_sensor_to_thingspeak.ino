
#include <ESP8266WiFi.h>
#include <Wire.h> 
// replace with your channel's thingspeak API key, 
String apiKey = "0042H0CD53CP11I8";
const char* ssid = "ACT FIBERNET";
const char* password = "act12345";
 
const char* server = "api.thingspeak.com";
 
 const int sensorpin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
float liquid_level;
int liquid_percentage;
int top_level = 512;
int bottom_level = 3;

WiFiClient client;
void setup() {     
  Serial.begin(115200);
   WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("connecting to....");
  Serial.println("WiFi connected");
  
}



void loop() {
 liquid_level = analogRead(sensorpin);
  liquid_percentage = ((liquid_level-bottom_level)/top_level)*100;
  Serial.print("Water Sensor Value: ");
     Serial.print(sensorpin);
       Serial.println("sent to Thingspeak");

      
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(sensorpin);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     
  client.stop();
   

   Serial.println("Waiting...");    
  // thingspeak needs minimum 15 sec delay between updates
  // Here I set upload every 60 seconds
  
  {
    delay(10000);                         
  }                       
}
