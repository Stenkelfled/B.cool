/*
 * B_Cool.cpp
 *
 * Created: 28.10.2018 09:50:52
 * Author : stenkelfled
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "utils/macro_generation.h"
#include "b_cool.h"

#include "SlotManager.h"
#include "power.h"

BeerTimer beer_timer;
SlotManager slot_mgr(&beer_timer);

#define DELAY_VALUE   250

int main(void)
{
  // Initialize
  // RTC initialize by constructor
  // SlotManager initialized by Constructor
  power::init();
  
  //Interrupts
  PMIC_CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;

  sei();
  
  while (1)
  {
    if(!light::isOn())
    {
      power::sleep();
    }
    else
    {
      slot_mgr.updateAll();
    }
  }
  return 0;
}



//// Interrupt service handlers ///////////////////////////////////////////////

//RTC overflow -> update extended variable
ISR(RTC_OVF_vect)
{
  beer_timer.rtcOvfHdl();
}

/*
ISR(port_INTn_vect(SLOT_GROUP_0_PORT_NAME,0))
{
  slot_mgr.pinChgHdl(SLOT_GROUP_0_START, SLOT_GROUP_0_END);
}

ISR(port_INTn_vect(SLOT_GROUP_1_PORT_NAME, 0))
{
  slot_mgr.pinChgHdl(SLOT_GROUP_0_MEMBER_COUNT+SLOT_GROUP_1_START
                    , SLOT_GROUP_0_MEMBER_COUNT+SLOT_GROUP_1_END);
}
*/






















