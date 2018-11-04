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
  /////////////////////////////////////
  //Beer slot switch
  //group 0
  for(uint8_t pin_i = SLOT_GROUP_0_START; pin_i<=SLOT_GROUP_0_END; pin_i++)  
  {
    this->slots[pin_i - SLOT_GROUP_0_START].pinInit(&SLOT_GROUP_0_PORT, pin_i);
  }

  //group1
  for(uint8_t pin_i = SLOT_GROUP_1_START; pin_i<=SLOT_GROUP_1_END; pin_i++)
  {
    this->slots[pin_i - SLOT_GROUP_1_START + SLOT_GROUP_0_MEMBER_COUNT].pinInit(&SLOT_GROUP_1_PORT, pin_i);
  }

#if SLOT_GROUP_COUNT > 2
  #error Please add the code for additional groups here!
#endif

  /////////////////////////////////////
  // BeerSlot LED

  this->slots[0].ledInit(LED_SLOT0_RED, LED_SLOT0_GREEN);
  this->slots[1].ledInit(LED_SLOT1_RED, LED_SLOT1_GREEN);
  this->slots[2].ledInit(LED_SLOT2_RED, LED_SLOT2_GREEN);
  this->slots[3].ledInit(LED_SLOT3_RED, LED_SLOT3_GREEN);
  this->slots[4].ledInit(LED_SLOT4_RED, LED_SLOT4_GREEN);
  this->slots[5].ledInit(LED_SLOT5_RED, LED_SLOT5_GREEN);
  this->slots[6].ledInit(LED_SLOT6_RED, LED_SLOT6_GREEN);
  this->slots[7].ledInit(LED_SLOT7_RED, LED_SLOT7_GREEN);
  this->slots[8].ledInit(LED_SLOT8_RED, LED_SLOT8_GREEN);
  this->slots[9].ledInit(LED_SLOT9_RED, LED_SLOT9_GREEN);
  this->slots[10].ledInit(LED_SLOT10_RED, LED_SLOT10_GREEN);

  TCC0_CTRLB = TC0_CCAEN_bm|TC0_CCBEN_bm|TC0_CCCEN_bm|TC0_CCDEN_bm | LED_WGMODE;
  TCC0_PER = LED_PERIOD;
  TCC0_CTRLA = LED_PRESCALER;

  TCC1_CTRLB = TC1_CCAEN_bm|TC1_CCBEN_bm | LED_WGMODE;
  TCC1_PER = LED_PERIOD;
  TCC1_CTRLA = LED_PRESCALER;

  TCD0_CTRLB = TC0_CCAEN_bm|TC0_CCBEN_bm|TC0_CCCEN_bm|TC0_CCDEN_bm | LED_WGMODE;
  TCD0_PER = LED_PERIOD;
  TCD0_CTRLA = LED_PRESCALER;

  TCD1_CTRLB = TC1_CCAEN_bm|TC1_CCBEN_bm | LED_WGMODE;
  TCD1_PER = LED_PERIOD;
  TCD1_CTRLA = LED_PRESCALER;

  TCE0_CTRLB = TC0_CCAEN_bm|TC0_CCBEN_bm|TC0_CCCEN_bm|TC0_CCDEN_bm | LED_WGMODE;
  TCE0_PER = LED_PERIOD;
  TCE0_CTRLA = LED_PRESCALER;

  TCE1_CTRLB = TC1_CCAEN_bm|TC1_CCBEN_bm | LED_WGMODE;
  TCE1_PER = LED_PERIOD;
  TCE1_CTRLA = LED_PRESCALER;

  TCF0_CTRLB = TC0_CCAEN_bm|TC0_CCBEN_bm|TC0_CCCEN_bm|TC0_CCDEN_bm | LED_WGMODE;
  TCF0_PER = LED_PERIOD;
  TCF0_CTRLA = LED_PRESCALER;



} //SlotManager

// default destructor
SlotManager::~SlotManager()
{
} //~SlotManager
