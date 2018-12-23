/*
 * B_Cool.cpp
 *
 * Created: 28.10.2018 09:50:52
 * Author : stenkelfled
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "utils/macro_generation.h"
#include "b_cool.h"

#include "SlotManager.h"

//SlotManager slot_mgr;
BeerTimer beer_timer;

#define DELAY_VALUE   250

int main(void)
{
  // Initialize
  // SlotManager initialized by Constructor

  sei();

  //PORTn_DIRSET(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN) | (1<<LED_SLOT0_RED_PIN);
  //PORTn_OUTCLR(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN) | (1<<LED_SLOT0_RED_PIN);
  while (1) 
  { 
#if 0 
//LED_blinking for Test ;-)
    PORTn_OUTSET(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN) | (1<<LED_SLOT0_RED_PIN);
    _delay_ms(DELAY_VALUE);
    PORTn_OUTCLR(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN);
    _delay_ms(DELAY_VALUE);
    PORTn_OUTSET(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN);
    PORTn_OUTCLR(LED_SLOT0_RED_PORT_NAME) = (1<<LED_SLOT0_RED_PIN);
    _delay_ms(DELAY_VALUE);
    PORTn_OUTCLR(LED_SLOT0_GREEN_PORT_NAME) = (1<<LED_SLOT0_GREEN_PIN);
    _delay_ms(DELAY_VALUE);
#endif
  }
  return 0;
}



//// Interrupt service handlers ///////////////////////////////////////////////

//RTC overflow -> update extended variable
ISR(RTC_OVF_vect)
{
  beer_timer.rfcOvfHdl();
}
























