#include <SimpleFOC.h>
#include <SPI.h>
// MagneticSensorSPI(int cs, float _cpr, int _angle_register)
// cs              - SPI chip select pin 
// bit_resolution  - sensor resolution
// angle_register  - (optional) angle read register - default 0x3FFF
//As5045MagneticSensorSSI as5047u = As5045MagneticSensorSSI(15, 14, 0x3FFF);
// or quick config
MagneticSensorSPI as5047u = MagneticSensorSPI(15, 12, 0x3FFF);

SPIClass hspi = SPIClass(HSPI);

void setup() {
  // monitoring port
  Serial.begin(115200);

  // initialise magnetic sensor hardware

  as5047u.init(&hspi);

  Serial.println("as5047u ready");
  _delay(1000);
}

void loop() {
  // IMPORTANT - call as frequently as possible
  // update the sensor values 
  as5047u.update();
  // display the angle and the angular velocity to the terminal
  Serial.println(as5047u.getAngle());
//  Serial.print("\t");
//  Serial.println(as5047u.getVelocity());
  delay(10);
}
