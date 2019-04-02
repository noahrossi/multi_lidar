// SDA -> White -> A4
// SCL -> Green -> A5

#include <Wire.h>
#include <VL53L0X.h>

#define NUM_SENSORS 3

struct lidar {
  VL53L0X sensor;
  byte port; // XSHUT port on the DIO
};

lidar lidars[NUM_SENSORS];

void setup() {

  Serial.begin(9600);
  Wire.begin();

  for (byte i = 1; i < NUM_SENSORS; i++) {
    lidars[i].port = 1 + i;
    pinMode(lidars[i].port, OUTPUT);
    digitalWrite(lidars[i].port, LOW); // put em into sleep mode
  }

  for (byte i = 0; i < NUM_SENSORS; i++) {
    if (i != 0) {
      Serial.print("pulling high ");
      Serial.print(lidars[i].port);
      Serial.println();
      pinMode(lidars[i].port, INPUT);  // IMPORTANT-- NEVER pull pin high (5V will FRY it)
    }
    delay(100);

    Serial.print("init");

    lidars[i].sensor.init();
    Serial.print("set address");
    lidars[i].sensor.setAddress(0x30 + i);
    Serial.print("set timeout");
    lidars[i].sensor.setTimeout(500);
    Serial.print("start continuous");
    lidars[i].sensor.startContinuous();
  }

  Serial.print("working");
}


void loop()
{
  for (byte i = 0; i < NUM_SENSORS; i++) {
    Serial.print(i);
    Serial.print("-");
    Serial.print(lidars[i].sensor.readRangeContinuousMillimeters());
    Serial.print(' ');
  }
   
  //Serial.println();
}
