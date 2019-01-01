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
#include "BeerTimer.h"

class BeerSlot
{
//variables
public:
  enum class eLedColor {
     Off
    ,Red
    ,Green
    ,Yellow
  };
protected:
private:
  enum class eState : uint8_t
  {
    empty  = 0
    ,full  = 1
  };

  struct {
    PORT_t *port; //base address
    uint8_t pin;
    eState state;
  } sSwitch;

  struct {
    register16_t *red; //timer/counter compare register
    register16_t *green; //timer/counter compare register
  } sLed;
  
  BeerTimer * timer;
  
  BeerTimer::uTime fill_time;

//functions
public:
	BeerSlot();
	~BeerSlot();
  void setup(BeerTimer * timer);
  void pinInit(PORT_t * const switch_port, uint8_t const switch_pin);
  void ledInit(register16_t *red, register16_t *green);
  void update();
  
//   void switchActivated(void);
//   void switchReleased(void);
//  void setLEDColor(void);
protected:
private:
	
  void ledSetColor(eLedColor color);
}; //BeerSlot

#endif //__BEERSLOT_H__
