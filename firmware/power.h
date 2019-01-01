/*
 * power.h
 *
 * Created: 31.12.2018 10:25:03
 *  Author: stenkelfled
 */ 


#ifndef POWER_H_
#define POWER_H_

#include "b_cool.h"

namespace power
{
  void init();
  
  void sleep();
  void sleep_end();
}

namespace light
{
  void init();
  
  uint8_t isOn();
  void setOn();
  void clearOn();
}




#endif /* POWER_H_ */