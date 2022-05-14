
#include <SimpleFOC.h>
#include "rcPWMCapture.h"
#include "configs.h"

// System Components
// Simple FOC Components
BLDCMotor motor = BLDCMotor(POLE_PAIRS);
BLDCDriver3PWM driver = BLDCDriver3PWM(PWM_U, PWM_V, PWM_W, GATE_EN); // U,V,W

#ifdef HALL_SENSOR
  HallSensor sensor = HallSensor(HALL_U, HALL_V, HALL_W, POLE_PAIRS);
#endif

// Ineterface Components
rcPWMCapture rc1 = rcPWMCapture(RC1_PIN, 1000, 2000);

// taks management
hw_timer_t * foc_loop_timer = NULL;


//ISR functions to handle system events
void handleRC() {rc1.isr();}

#ifdef HALL_SENSOR
  void doA(){sensor.handleA();}
  void doB(){sensor.handleB();}
  void doC(){sensor.handleC();}
#endif

void IRAM_ATTR focLoopCallback() {
  motor.loopFOC();
}
 
void setup() {
  
  // Setup the interface
  Serial.begin(115200);
  rc1.enableInterrupts(handleRC);
  
  // Setup the sensor
  sensor.init();
  
  #ifdef HALL_SENSOR
    sensor.enableInterrupts(doA, doB, doC);
  #endif
  
  // Setup the driver stage
  driver.voltage_power_supply = DC_BUS_VOLTAGE;
  driver.pwm_frequency = PWM_FREQ;
  driver.init();
  
  // link the driver and sensor to the motor
  motor.linkSensor(&sensor);
  //link the motor and the driver
  motor.linkDriver(&driver);
  
  //perform the calibration
  motor.voltage_limit = CAL_PWM_VOLTAGE; 
  #ifdef CAL_PWM_VOLTAGE
    motor.torque_controller = TorqueControlType::voltage;
  #endif

  motor.init();
  motor.initFOC();
  //after calibration the max output voltage to the motor should not be limited
  motor.voltage_limit = DC_BUS_VOLTAGE/2; 

  //Set up a timer to execute the loopFPC every 500 us (2KHz loop frequency)
  foc_loop_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(foc_loop_timer, &focLoopCallback, true);
  timerAlarmWrite(foc_loop_timer, 500, true);
  timerAlarmEnable(foc_loop_timer);
}

float motor_cmd = 0;

void loop() {
 motor.move(rc1.readNormalized());
 delay(10);
}
