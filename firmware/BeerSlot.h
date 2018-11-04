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

class BeerSlot
{
//variables
public:
protected:
private:
struct {
  PORT_t *port; //base address
  uint8_t pin;
} sSwitch;


//functions
public:
	BeerSlot();
	~BeerSlot();
  void init(PORT_t * const switch_port, uint8_t const switch_pin);
  
  void switchActivated(void);
  void switchReleased(void);
  void setLEDColor(void);
protected:
private:
	

}; //BeerSlot

#endif //__BEERSLOT_H__
