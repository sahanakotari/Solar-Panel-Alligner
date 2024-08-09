#define BLYNK_TEMPLATE_ID "final2"
#define BLYNK_TEMPLATE_NAME "final2"

#include <BlynkSimpleEsp32.h>
// other includes and code...

#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
//for blynk
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Simpletimer.h>
//for servo motor
#include <ESP32Servo.h>
const int LDR1 = 34;
const int LDR2 = 35;
const int TEMP = 21;
#define error 10
int Spoint =  90;
Servo servo;
char auth[] = "andwvBtXjBgUVugL9kE36X5_goNtuNji";
char ssid[] = "Rakshii bhat";
char pass[] = "rakshitha5803";
SimpleTimer timer;

void solar(){
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);
  Serial.println(ldr1);
  delay(1000);
  Serial.println(ldr2);
  delay(1000);
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println("*C");
  delay(1000);

  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

  if ((value1 <= error) || (value2 <= error)) {

  } 
  else {
    if (ldr1 > ldr2) {
      Spoint = Spoint-9;
    }
    if (ldr1 < ldr2) {
      Spoint = Spoint+9;
    }
  }

servo.write(Spoint);
delay(80);
Blynk.virtualWrite(V2,bmp.readTemperature() ); 
}

void setup()
{
  if (!bmp.begin()) {
	Serial.println("FAILED TO BOOT!!!");
	while (1) {}
  }
  Serial.begin(9600);
  servo.attach(33);
  servo.write(Spoint);
  delay(1000);
  Blynk.begin(auth, ssid, pass,IPAddress(117,236,190,213),8080);
  timer.setInterval(10L,solar);
}

void loop()
{
  Blynk.run();
  timer.run();
}