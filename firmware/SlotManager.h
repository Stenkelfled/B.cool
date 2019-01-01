/* 
* SlotManager.h
*
* Created: 28.10.2018 12:14:53
* Author: stenkelfled
*/


#ifndef __SLOTMANAGER_H__
#define __SLOTMANAGER_H__

#include <stdint.h>

#include "utils/macro_generation.h"

#include "BeerSlot.h"
#include "b_cool.h"

class SlotManager
{
//variables
public:
protected:
private:
  BeerSlot slots[BEER_CAPACITY];

  BeerTimer * timer;

//functions
public:
	SlotManager(BeerTimer * const timer);
	~SlotManager();
  
  static void enableLeds();
  static void disableLeds();
  
  void pinChgHdl(uint8_t const first_slot, uint8_t const last_slot);
protected:
private:
	

}; //SlotManager

#endif //__SLOTMANAGER_H__
