/* 
* SlotManager.h
*
* Created: 28.10.2018 12:14:53
* Author: stenkelfled
*/


#ifndef __SLOTMANAGER_H__
#define __SLOTMANAGER_H__

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
protected:
private:
	

}; //SlotManager

#endif //__SLOTMANAGER_H__
