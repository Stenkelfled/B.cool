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

BeerTimer beer_timer;
SlotManager slot_mgr(&beer_timer);

#define DELAY_VALUE   250

int main(void)
{
  // Initialize
  // RTC initialize by constructor
  // SlotManager initialized by Constructor
  
  //Interrupts
  PMIC_CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm;

  sei();

//   PORTn_DIRSET(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN) | (1<<LED_SLOT0_RED_PIN);
//   PORTn_OUTCLR(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN) | (1<<LED_SLOT0_RED_PIN);
//   
//   PORTJ_DIRCLR = 1<<SLOT_GROUP_0_START;
//   PORTJ_PIN0CTRL = PORT_OPC_PULLUP_gc;
  
  while (1)
  {
//     if(PORTJ_IN & (1<<0))
//     {
//       PORTn_OUTSET(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN);
//     }
//     else
//     {
//       PORTn_OUTCLR(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN);
//     }
  }
  return 0;
}



//// Interrupt service handlers ///////////////////////////////////////////////

//RTC overflow -> update extended variable
ISR(RTC_OVF_vect)
{
  beer_timer.rtcOvfHdl();
}


ISR(port_INTn_vect(SLOT_GROUP_0_PORT_NAME,0))
{
  slot_mgr.pinChgHdl(SLOT_GROUP_0_START, SLOT_GROUP_0_END);
}

ISR(port_INTn_vect(SLOT_GROUP_1_PORT_NAME, 0))
{
  slot_mgr.pinChgHdl(SLOT_GROUP_0_MEMBER_COUNT+SLOT_GROUP_1_START
                    , SLOT_GROUP_0_MEMBER_COUNT+SLOT_GROUP_1_END);
}























