
#include <SimpleFOC.h>

BLDCMotor motor = BLDCMotor(10);
//BLDCDriver6PWM driver = BLDCDriver6PWM(33, 32, 27, 26, 25, 23, 18);
BLDCDriver3PWM driver = BLDCDriver3PWM(26, 33, 32, 25); // U,V,W

//HallSensor sensor = HallSensor(HALL1, HALL2, HALL3, 15);
Encoder encoder = Encoder(22, 21, 400);

//void doA(){sensor.handleA();}
//void doB(){sensor.handleB();}
//void doC(){sensor.handleC();}

void doA(){encoder.handleA();}
void doB(){encoder.handleB();}

void setup() {
  Serial.begin(115200);
  //sensor.init();
  //sensor.enableInterrupts(doA, doB, doC);
  encoder.quadrature = Quadrature::ON;
  encoder.init();
  encoder.enableInterrupts(doA, doB);
  
  driver.voltage_power_supply = 12;
  driver.pwm_frequency = 10000;
//  driver.dead_zone = 0.01;
  driver.init();
  // init sensor
  // link the motor to the sensor
  motor.linkSensor(&encoder);
  //link the motor and the driver
  motor.linkDriver(&driver);

  motor.voltage_limit = 1.5; 
//  motor.controller = MotionControlType::velocity_openloop;
  motor.torque_controller = TorqueControlType::voltage;

  motor.init();
  motor.initFOC();
}
unsigned long i = 0;
void loop() {
 motor.loopFOC();

 //float knob = analogRead(36);
 //knob = ((knob-2048)/2048)*50;
 //motor.move(knob);
 //motor.move((3/40.4)*encoder.getVelocity()+1.5);
 motor.move(12);
 /*
 if(i>50000)
 {
  i=0;
  Serial.println(encoder.getVelocity());
 }
 i++;
 */
}
