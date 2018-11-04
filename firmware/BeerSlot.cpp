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
 */
void BeerSlot::ledInit(register16_t *red, register16_t *green)
{
  this->sLed.green = green;
  this->sLed.red = red;

  *this->sLed.green = 0;
  *this->sLed.red = 0;
}

