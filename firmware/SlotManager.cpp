/* 
* SlotManager.cpp
*
* Created: 28.10.2018 12:14:53
* Author: stenkelfled
*/


#include "SlotManager.h"

// default constructor
SlotManager::SlotManager()
{
  //group 0
  for(uint8_t pin_i = SLOT_GROUP_0_START; pin_i<=SLOT_GROUP_0_END; pin_i++)  
  {
    this->slots[pin_i].init(&SLOT_GROUP_0_PORT, pin_i);
  }

  //group1
  for(uint8_t pin_i = SLOT_GROUP_1_START; pin_i<=SLOT_GROUP_1_END; pin_i++)
  {
    this->slots[pin_i+SLOT_GROUP_0_MEMBER_COUNT].init(&SLOT_GROUP_1_PORT, pin_i);
  }

#if SLOT_GROUP_COUNT > 2
  #error Please add the code for additional groups here!
#endif
} //SlotManager

// default destructor
SlotManager::~SlotManager()
{
} //~SlotManager
