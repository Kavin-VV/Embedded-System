#include <WiFi.h>
#include <ThingSpeak.h>
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
int Trigpin=18;
int echopin=5;
long Duration,Distance;
WiFiClient client;
unsigned long myChannelNumber = 2241467;
const char * myWriteAPIKey = "3Y1KYX3ZXJJ5FC5C";
int distance,statusCode;
void setup() {
Serial.begin(115200);
pinMode(Trigpin,OUTPUT);
pinMode(echopin,INPUT);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);
}
void loop() {
   digitalWrite(Trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(Trigpin,HIGH);
 delayMicroseconds(10);
 digitalWrite(Trigpin,LOW);
 delayMicroseconds(2);
 Duration=pulseIn(echopin,HIGH);
 Distance=Duration*0.034/2;
 Serial.print("Distance=");
 Serial.println((400-Distance));
 delay(1000);
if(WiFi.status() != WL_CONNECTED)
{
Serial.print("Attempting to connect");
while(WiFi.status() != WL_CONNECTED)
{
WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change
//this line if using open or WEP network
Serial.print(".");
delay(5000);
}
Serial.println("\nConnected.");
}

statusCode = ThingSpeak.writeField(myChannelNumber, 1, (400-Distance),
myWriteAPIKey);
if(statusCode == 200) { //successful writing code
Serial.println("Channel update successful.");
}
else {
Serial.println("Problem Writing data. HTTP error code :" +
String(statusCode));
}
if(Distance<30){
  Serial.print("Your Bin is Almost full");
}
delay(15000); // data to be uploaded every 15secs
}