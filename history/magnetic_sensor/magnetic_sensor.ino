
#include <SimpleFOC.h>
#include <SPI.h>

BLDCMotor motor = BLDCMotor(10);
//BLDCDriver6PWM driver = BLDCDriver6PWM(33, 32, 27, 26, 25, 23, 18);
BLDCDriver3PWM driver = BLDCDriver3PWM(26, 33, 32, 25); // U,V,W

MagneticSensorSPI as5047u = MagneticSensorSPI(15, 12, 0x3FFF);
SPIClass hspi = SPIClass(HSPI);

//void doA(){encoder.handleA();}
//void doB(){encoder.handleB();}

void setup() {
  Serial.begin(115200);
  as5047u.init(&hspi);

  driver.voltage_power_supply = 12;
  driver.pwm_frequency = 10000;
  driver.init();
  // init sensor
  // link the motor to the sensor
  motor.linkSensor(&as5047u);
  //link the motor and the driver
  motor.linkDriver(&driver);

  motor.voltage_limit = 1.5; 
//  motor.controller = MotionControlType::velocity;
  motor.torque_controller = TorqueControlType::voltage;

  motor.init();
  motor.initFOC();
  motor.voltage_limit = 6; 

}
unsigned long i = 0;
void loop() {
 motor.loopFOC();
// Serial.println(hall.getVelocity());

 //float knob = analogRead(36);
 //knob = ((knob-2048)/2048)*50;
 //motor.move(knob);
 //motor.move((3/40.4)*encoder.getVelocity()+1.5);
 motor.move(2.5);
 /*
 if(i>50000)
 {
  i=0;
  Serial.println(encoder.getVelocity());
 }
 i++;
 */
}
