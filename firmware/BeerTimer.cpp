/*
 * BeerTimer.cpp
 *
 * Created: 02.12.2018 16:52:40
 *  Author: stenkelfled
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "BeerTimer.h"

BeerTimer::BeerTimer()
{
  if( (RTC_CTRL&0x01) == 0)
  {
    this->my_time = (uint32_t)0;
    //RTC is not running -> initialize RTC
    RTC_CNT = 0;
    RTC_CTRL = RTC_PRESCALER_DIV1024_gc | 0x01; //RTC Tick is 1 second
    RTC_INTCTRL = RTC_OVFINTLVL_MED_gc;
  }
  
  
}

/**
 * @brief Update the time to current time.
 */
void BeerTimer::update()
{
  while (RTC_STATUS & RTC_SYNCBUSY_bm)
  { //wait for RTC to finish sync
  }
  
  this->my_time = (uint16_t)RTC_CNT;
}

/**
 * @brief RTC overflow Handler.
 */
void BeerTimer::rtcOvfHdl()
{
  this->my_time.incrExt();
  this->update(); // get current RTC time  
}

/**
 * @brief Returns the current time
 * @retval The current time
 */
BeerTime BeerTimer::getTime() const
{
  return this->my_time;
}