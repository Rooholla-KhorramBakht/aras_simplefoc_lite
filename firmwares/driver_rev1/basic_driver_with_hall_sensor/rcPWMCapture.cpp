#include "rcPWMCapture.h"


rcPWMCapture::rcPWMCapture(int pin)
{
  pwm_pin = pin;
  // The default min and max values are 1 and 2 ms (servo standard)
  max_pulse_width = 1000;
  min_pulse_width = 1500;
  // if no pulse are fed to the system, the default reading should correspond to zero
  pulse_width = (max_pulse_width+min_pulse_width)/2;
  old_pulse_width = pulse_width;
  normalized_width=0;
}

rcPWMCapture::rcPWMCapture(int pin, int max_width, int min_width)
{
  pwm_pin = pin;
  max_pulse_width = max_width;
  min_pulse_width = min_width;
  // if no pulse are fed to the system, the default reading should correspond to zero
  pulse_width = (max_pulse_width+min_pulse_width)/2;
  old_pulse_width = pulse_width;
  normalized_width=0;
}


// The interrupt service rutine that is to be called on each pin change interrupt
void rcPWMCapture::isr()
{
  static int32_t tmp = 0;
  int32_t width;
  
  if(digitalRead(pwm_pin) == HIGH) // is it the start of the pulse or its end?
    tmp = micros(); //save the stamp correspoinding the the rising edge of the pulse
  else
    width  = micros() - tmp;
    //The reading is valid only if the pulse width is between the min and max width
    if(width < max_pulse_width && width > min_pulse_width)
    {
      old_pulse_width = pulse_width;
      pulse_width = width;
      //Normalize the pulse width to be between -1 and 1
//      normalized_width = ((float)width-(max_pulse_width+min_pulse_width)/2)/(max_pulse_width-min_pulse_width)/2);
    }
}

float rcPWMCapture::readNormalized()
{
  return normalized_width;
}

int32_t rcPWMCapture::readMicroSecs()
{
  return pulse_width;
}

void rcPWMCapture::enableInterrupts(void (*isr)())
{
  
  pinMode(pwm_pin, INPUT);
  attachInterrupt(pwm_pin, isr, CHANGE);
  
}
