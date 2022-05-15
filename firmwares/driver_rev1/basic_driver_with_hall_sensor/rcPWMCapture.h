#ifndef __RC_PWM_CAPTURE__
#define __RC_PWM_CAPTURE__

#include "Arduino.h"

class rcPWMCapture
{
  public:
    rcPWMCapture(int pin);
    rcPWMCapture(int pin, int max_width, int min_width);
    
    void enableInterrupts(void (*isr)());
    void isr();// This function is to be called on each pin change interrupt
    int32_t readMicroSecs();
    float readNormalized(); 

  private:
    int pwm_pin;
    int32_t max_pulse_width;
    int32_t min_pulse_width;
    // variables to store the RC pulse width 
    int32_t pulse_width;     // pulse width microseconds
    int32_t old_pulse_width; // old pulse width microseconds
    float normalized_width;  // pulse width normalized
};


#endif
