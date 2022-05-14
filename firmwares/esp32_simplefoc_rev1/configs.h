
// sensor type
#define HALL_SENSOR
// control type
#define CONTROL_TYPE_VOLTAGE

// PIN Definitions
// RC channle 1 pin
#define RC1_PIN 15 

// driver pins
#define PWM_U 26
#define PWM_V 33
#define PWM_W 32
#define GATE_EN 25

// sensor pins
#ifdef HALL_SENSOR
  #define HALL_U 22
  #define HALL_V 21
  #define HALL_W 5
#endif
// System Parameters
#define PWM_FREQ 15000 // the pwm frequency of the driver
#define POLE_PAIRS 10
#define DC_BUS_VOLTAGE 12
#define CAL_PWM_VOLTAGE 1 //the volage used during sensor alignment
