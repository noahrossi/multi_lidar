#include <Wire.h>
#include <VL53L0X.h>

#define NUM_SENSORS 8

struct lidar {
  VL53L0X sensor;
  byte port; // XSHUT port on the DIO
};

lidar lidars[NUM_SENSORS];

void setup() {

  Serial.begin(9600);  
  Wire.begin();

  for (byte i = 0; i < NUM_SENSORS; i++) {
    lidars[i].port = 3 + i;
    pinMode(lidars[i].port, OUTPUT);
    digitalWrite(lidars[i].port, LOW); // put em into sleep mode
  }

  for (byte i = 0; i < NUM_SENSORS; i++) {
    pinMode(lidars[i].port, INPUT);  // IMPORTANT-- NEVER pull pin high (5V will FRY it)
    delay(100);
    lidars[i].sensor.setAddress(0x30 + i);
    lidars[i].sensor.init(true);
    lidars[i].sensor.setTimeout(500);
    lidars[i].sensor.startContinuous();
  }
}


void loop()
{
  for (byte i = 0; i < NUM_SENSORS; i++) {
    Serial.print(lidars[i].sensor.readRangeContinuousMillimeters());
    Serial.print(" ");
  }
   
  Serial.println();
}
