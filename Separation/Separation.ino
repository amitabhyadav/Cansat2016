//Team Astral #1274
//CanSat 2016 Burkett, Texas, USA
//Re-Entry Code
//Author(s): Amitabh Yadav, Aditya Savio Paul and Raghav Garg
//Date: 22-05-2016
//Time: 2253hrs IST


//BMP180 Connections:
// VCC of the BMP180 sensor to 3.3V (NOT 5.0V!)
// GND to Ground
// SCL to I2C clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// SDA to I2C data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Servo.h>

Servo myservo;

Adafruit_BMP085 bmp;
int pos = 0;
int count = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(13, OUTPUT);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
}
  
void loop() {
    int alt = bmp.readAltitude();
    digitalWrite(13, LOW);
    while(1)
    {
      Serial.print("Ground Altitude: ");
      Serial.println(alt);
      int alt1=bmp.readAltitude();
      Serial.print("Altitude: ");
      Serial.println(alt1);
      if(count == 0)
        Serial.print("Status: Accent");
      else if (count == 1)
        Serial.print("Status: Decent");
      if(alt1>alt+450)
      {
        count = 1;
      }
      if (alt1<alt+400 && count == 1)
      {
        while(1)
        {
          digitalWrite(13, HIGH);
          Serial.print("Ground Altitude: ");
          Serial.println(alt);
          Serial.print("Separated Altitude: ");
          Serial.println(alt1);
          Serial.print("Status: Separated");
           for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
             // in steps of 1 degree
             myservo.write(pos);              // tell servo to go to position in variable 'pos'
             delay(5);                       // waits 15ms for the servo to reach the position
             }
             delay(500);
             for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              delay(5);                       // waits 15ms for the servo to reach the position
             }
          }
        }
      delay(100);
    }
}
