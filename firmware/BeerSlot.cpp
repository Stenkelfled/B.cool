/* 
* BeerSlot.cpp
*
* Created: 28.10.2018 11:48:47
* Author: stenkelfled
*/


#include "BeerSlot.h"

// default constructor
BeerSlot::BeerSlot()
{
} //BeerSlot

// default destructor
BeerSlot::~BeerSlot()
{
} //~BeerSlot

/**
 * @brief Initialize beer slot
 * @param switch_port The port-adress for the switch. Use e.g. &PORTA
 * @param switch_pin The pin number.
 */
void BeerSlot::pinInit(PORT_t * const switch_port, uint8_t const switch_pin)
{
  this->sSwitch.port = switch_port;
  this->sSwitch.pin = switch_pin;
    
  // init switch pin
  this->sSwitch.port->DIRCLR = (1<<this->sSwitch.pin);
  *(&this->sSwitch.port->PIN0CTRL + this->sSwitch.pin) = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
    
  //set interrupts
  this->sSwitch.port->INTCTRL = PORT_INT0LVL_LO_gc;
  this->sSwitch.port->INT0MASK |= (1<<this->sSwitch.pin);

}

/**
 * @brief Set timer compare registers for LEDs
 * @param red Timer-Compare register for red LED
 * @param green Timer-Compare register for green LED
 */
void BeerSlot::ledInit(register16_t *red, register16_t *green)
{
  this->sLed.red = red;
  this->sLed.green = green;
  
  *this->sLed.red = 0;
  *this->sLed.green = 0;
}

/**
 * @brief Set BeerSlotLed-Color
 */
void BeerSlot::ledSetColor(BeerSlot::eLedColor_t const color)
{
  switch (color)
  {
    case ledOff:
      *this->sLed.red = 0;
      *this->sLed.green = 0;
      break;
    case ledRed:
      *this->sLed.red = LED_ON_VALUE;
      *this->sLed.green = 0;
      break;
    case ledGreen:
      *this->sLed.red = 0;
      *this->sLed.green = LED_ON_VALUE;
      break;
    case ledYellow:
      *this->sLed.red = LED_ON_VALUE;
      *this->sLed.green = LED_ON_VALUE;
      break;
  }
}
