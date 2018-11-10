/* 
* BeerSlot.h
*
* Created: 28.10.2018 11:48:47
* Author: stenkelfled
*/


#ifndef __BEERSLOT_H__
#define __BEERSLOT_H__

#include <avr/io.h>
#include <avr/interrupt.h>

#include "b_cool.h"

class BeerSlot
{
//variables
public:
typedef enum {
  ledOff
  ,ledRed
  ,ledGreen
  ,ledYellow
} eLedColor_t;
protected:
private:
struct {
  PORT_t *port; //base address
  uint8_t pin;
} sSwitch;

struct {
  register16_t *red; //timer/counter compare register
  register16_t *green; //timer/counter compare register
} sLed;


//functions
public:
	BeerSlot();
	~BeerSlot();
  void pinInit(PORT_t * const switch_port, uint8_t const switch_pin);
  void ledInit(register16_t *red, register16_t *green);
  void ledSetColor(eLedColor_t color);
  
  void switchActivated(void);
  void switchReleased(void);
  void setLEDColor(void);
protected:
private:
	

}; //BeerSlot

#endif //__BEERSLOT_H__
