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
    //RTC is not running -> initialize RTC  
    this->mtime = (uint32_t)0;
    
    //configure clock source
    OSC_CTRL |= OSC_RC32KEN_bm;
    while(!(OSC_STATUS & OSC_RC32KRDY_bm)) {}
    CLK_RTCCTRL = CLK_RTCSRC_RCOSC_gc | CLK_RTCEN_bm; //1.024kHz from 32.768kHz internal oscillator
    
    
    RTC_CNT = 0;
    RTC_INTCTRL = RTC_OVFINTLVL_MED_gc;
    RTC_CTRL = RTC_PRESCALER_DIV1024_gc | 0x01; //RTC Tick is 1 second
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
  
  this->mtime = (uint16_t)RTC_CNT;
}

/**
 * @brief RTC overflow Handler.
 */
void BeerTimer::rtcOvfHdl()
{
  this->mtime.incrExt();
  this->update(); // get current RTC time  
}

/**
 * @brief Returns the current time
 * @retval The current time
 */
BeerTime BeerTimer::getTime()
{
  this->update();
  return this->mtime;
}