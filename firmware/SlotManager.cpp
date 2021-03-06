/* 
* SlotManager.cpp
*
* Created: 28.10.2018 12:14:53
* Author: stenkelfled
*/

#include <avr/interrupt.h>

#include "SlotManager.h"

// default constructor
SlotManager::SlotManager(BeerTimer * const timer)
{
  this->timer = timer;
  
  for(uint8_t i=0; i<BEER_CAPACITY; i++)
  {
    this->slots[i].setup(timer);
  }
  
  /////////////////////////////////////
  //#BeerSlotSwitchInit
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
  //#BeerSlotLEDInit
  SlotManager::enableLeds();
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
#if BEER_CAPACITY != 11
  #error Plese add Initialization routines for missing LEDs!
#endif

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

  /////////////////////////////////////
  //#UserSwitch
  // init switch pins
  PORTn_func(USER_SWITCH_PORT_NAME, DIRCLR) = USER_SWITCH_MASK_ALL; //mask Bits 0...(USER_SWITCH_COUNT-1)
    
  //Interrupt on both edges
  PORTCFG_MPCMASK = USER_SWITCH_MASK_ALL; //use Multi-pin Configuration Mask register
  PORTn_func(USER_SWITCH_PORT_NAME, PIN0CTRL) = PORT_ISC_BOTHEDGES_gc | PORT_OPC_PULLDOWN_gc;
    
  //set interrupts
  PORTn_func(USER_SWITCH_PORT_NAME, INTCTRL) = PORT_INT0LVL_LO_gc;
  PORTn_func(USER_SWITCH_PORT_NAME, INT0MASK) = USER_SWITCH_MASK_ALL;


} //SlotManager

// default destructor
SlotManager::~SlotManager()
{
} //~SlotManager

/**
 * @brief Enables the LED outputs
 */
void SlotManager::enableLeds()
{
  PORTn_DIRSET(LED_SLOT0_RED_PORT_NAME) = 1<<LED_SLOT0_RED_PIN;
  PORTn_DIRSET(LED_SLOT0_GREEN_PORT_NAME) = 1<<LED_SLOT0_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT1_RED_PORT_NAME) = 1<<LED_SLOT1_RED_PIN;
  PORTn_DIRSET(LED_SLOT1_GREEN_PORT_NAME) = 1<<LED_SLOT1_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT2_RED_PORT_NAME) = 1<<LED_SLOT2_RED_PIN;
  PORTn_DIRSET(LED_SLOT2_GREEN_PORT_NAME) = 1<<LED_SLOT2_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT3_RED_PORT_NAME) = 1<<LED_SLOT3_RED_PIN;
  PORTn_DIRSET(LED_SLOT3_GREEN_PORT_NAME) = 1<<LED_SLOT3_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT4_RED_PORT_NAME) = 1<<LED_SLOT4_RED_PIN;
  PORTn_DIRSET(LED_SLOT4_GREEN_PORT_NAME) = 1<<LED_SLOT4_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT5_RED_PORT_NAME) = 1<<LED_SLOT5_RED_PIN;
  PORTn_DIRSET(LED_SLOT5_GREEN_PORT_NAME) = 1<<LED_SLOT5_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT6_RED_PORT_NAME) = 1<<LED_SLOT6_RED_PIN;
  PORTn_DIRSET(LED_SLOT6_GREEN_PORT_NAME) = 1<<LED_SLOT6_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT7_RED_PORT_NAME) = 1<<LED_SLOT7_RED_PIN;
  PORTn_DIRSET(LED_SLOT7_GREEN_PORT_NAME) = 1<<LED_SLOT7_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT8_RED_PORT_NAME) = 1<<LED_SLOT8_RED_PIN;
  PORTn_DIRSET(LED_SLOT8_GREEN_PORT_NAME) = 1<<LED_SLOT8_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT9_RED_PORT_NAME) = 1<<LED_SLOT9_RED_PIN;
  PORTn_DIRSET(LED_SLOT9_GREEN_PORT_NAME) = 1<<LED_SLOT9_GREEN_PIN;
  PORTn_DIRSET(LED_SLOT10_RED_PORT_NAME) = 1<<LED_SLOT10_RED_PIN;
  PORTn_DIRSET(LED_SLOT10_GREEN_PORT_NAME) = 1<<LED_SLOT10_GREEN_PIN;
  
  PORTCFG_MPCMASK = USER_SWITCH_MASK_ALL; //use Multi-pin Configuration Mask register
  PORTn_func(USER_SWITCH_PORT_NAME, PIN0CTRL) = PORT_ISC_BOTHEDGES_gc | PORT_OPC_PULLDOWN_gc;
}

/**
 * @brief Disables the LED output
 */
void SlotManager::disableLeds()
{
  PORTn_DIRCLR(LED_SLOT0_RED_PORT_NAME) = 1<<LED_SLOT0_RED_PIN;
  PORTn_DIRCLR(LED_SLOT0_GREEN_PORT_NAME) = 1<<LED_SLOT0_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT1_RED_PORT_NAME) = 1<<LED_SLOT1_RED_PIN;
  PORTn_DIRCLR(LED_SLOT1_GREEN_PORT_NAME) = 1<<LED_SLOT1_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT2_RED_PORT_NAME) = 1<<LED_SLOT2_RED_PIN;
  PORTn_DIRCLR(LED_SLOT2_GREEN_PORT_NAME) = 1<<LED_SLOT2_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT3_RED_PORT_NAME) = 1<<LED_SLOT3_RED_PIN;
  PORTn_DIRCLR(LED_SLOT3_GREEN_PORT_NAME) = 1<<LED_SLOT3_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT4_RED_PORT_NAME) = 1<<LED_SLOT4_RED_PIN;
  PORTn_DIRCLR(LED_SLOT4_GREEN_PORT_NAME) = 1<<LED_SLOT4_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT5_RED_PORT_NAME) = 1<<LED_SLOT5_RED_PIN;
  PORTn_DIRCLR(LED_SLOT5_GREEN_PORT_NAME) = 1<<LED_SLOT5_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT6_RED_PORT_NAME) = 1<<LED_SLOT6_RED_PIN;
  PORTn_DIRCLR(LED_SLOT6_GREEN_PORT_NAME) = 1<<LED_SLOT6_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT7_RED_PORT_NAME) = 1<<LED_SLOT7_RED_PIN;
  PORTn_DIRCLR(LED_SLOT7_GREEN_PORT_NAME) = 1<<LED_SLOT7_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT8_RED_PORT_NAME) = 1<<LED_SLOT8_RED_PIN;
  PORTn_DIRCLR(LED_SLOT8_GREEN_PORT_NAME) = 1<<LED_SLOT8_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT9_RED_PORT_NAME) = 1<<LED_SLOT9_RED_PIN;
  PORTn_DIRCLR(LED_SLOT9_GREEN_PORT_NAME) = 1<<LED_SLOT9_GREEN_PIN;
  PORTn_DIRCLR(LED_SLOT10_RED_PORT_NAME) = 1<<LED_SLOT10_RED_PIN;
  PORTn_DIRCLR(LED_SLOT10_GREEN_PORT_NAME) = 1<<LED_SLOT10_GREEN_PIN;
  
  PORTCFG_MPCMASK = USER_SWITCH_MASK_ALL; //use Multi-pin Configuration Mask register
  PORTn_func(USER_SWITCH_PORT_NAME, PIN0CTRL) = PORT_ISC_BOTHEDGES_gc;
}

/**
 * @brief Register a pin change on one of the slots.
 * @param first First possibly changed slot.
 * @param last Last possibly changed slot.
 */
void SlotManager::pinChgHdl(uint8_t const first_slot, uint8_t const last_slot)
{
  for(uint8_t slot_i=first_slot; slot_i<=last_slot; slot_i++)
  {
    this->slots[slot_i].update(getUserState());
  }
}

/**
 * @brief Updates ALL Beer slots
 */
void SlotManager::updateAll()
{
  for(uint8_t slot_i=0; slot_i<BEER_CAPACITY; slot_i++)
  {
    this->slots[slot_i].update(getUserState());
  }
}

/**
 * @brief Reads the state of the user switch
 * @return The current user switch configuration
 */
BeerSlot::user_t SlotManager::getUserState()
{
  return ( PORTn_func(USER_SWITCH_PORT_NAME,IN) & USER_SWITCH_MASK_ALL );
}
















