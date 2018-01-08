/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 *
 *
 **************************************************************
 * 
 * 
 *
 * WARNING :
 * For this example you'll need SimpleTimer library:
 *   https://github.com/jfturcot/SimpleTimer
 * Visit this page for more information:
 *   http://playground.arduino.cc/Code/SimpleTimer
 *
 * DHT11 ----pin 12
 *  
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>

#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT11   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "04384562e6dd4a94a4d9b10c0b2547f3"; //insert here your token generated by Blynk
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IPaddr";
char pass[] = "password";

SimpleTimer timer;

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
   Blynk.begin(auth, ssid, pass); //insert here your SSID and password
  // Setup a function to be called every second
  dht.begin();
  timer.setInterval(60000L, sendUptime);
}

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendUptime()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(10, dht.readTemperature(true)); //virtual pin
  Blynk.virtualWrite(12, dht.readHumidity()); // virtual pin 
  //Serial.print("V10,V11 ");
  //Serial.println(pinValue);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
