/*
 * power.cpp
 *
 * Created: 31.12.2018 10:24:47
 *  Author: stenkelfled
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "utils/macro_generation.h"
#include "b_cool.h"

#include "power.h"

#include "SlotManager.h"

/**
 * @brief Initialize ATMEL Power-management
 */
void power::init()
{
  light::init();
  
  //power reduction registers
  PR_PRGEN = PR_AES_bm | PR_DMA_bm;
  uint8_t pr_val = PR_ADC_bm | PR_DAC_bm | PR_AC_bm;
  PR_PRPA = pr_val;
  PR_PRPB = pr_val;
  pr_val = PR_TWI_bm | PR_USART0_bm | PR_SPI_bm;
  PR_PRPD = pr_val; //port D uses USART1 for WIFI module
  pr_val |= PR_USART1_bm;
  PR_PRPC = pr_val;
  PR_PRPE = pr_val;
  PR_PRPF = pr_val;
  
  //sleep mode
  SLEEP_CTRL = SLEEP_MODE_PWR_SAVE;
}

/**
 * @brief End the sleep mode
 */
void power::sleep_end()
{
  //re-enable all outputs
  SlotManager::enableLeds();
  SLEEP_CTRL &= ~SLEEP_SEN_bm;
}

/**
 * @brief Send uC to sleep mode
 */
void power::sleep()
{
  //disable all outputs
  SlotManager::disableLeds();
  SLEEP_CTRL |= SLEEP_SEN_bm;
  asm ("sleep");
  //_delay_ms(300);
  sleep_end();
}

/**
 * @brief Init fridge light detection
 */
void light::init()
{
  PORTn_func(NLIGHT_ON_PORT_NAME,DIRCLR) = 1<<NLIGHT_ON_PIN;
  PORTn_func(NLIGHT_ON_PORT_NAME,INTCTRL) |= PORT_INT0LVL_HI_gc;
  PORTn_func(NLIGHT_ON_PORT_NAME,INT0MASK) |= 1<<NLIGHT_ON_PIN;

  PORTn_func(NLIGHT_ON_PORT_NAME,PINnCTRL(NLIGHT_ON_PIN)) = PORT_ISC_LEVEL_gc;
}

/**
 * @brief Checks, if the light is on.
 * @return True, if the light is on.
 */
uint8_t light::isOn()
{
#ifndef LIGHT_ALWAYS_ON
  return !(PORTn_func(NLIGHT_ON_PORT_NAME,IN) & (1<<NLIGHT_ON_PIN));
#else
  #warning Override: Light is always on!
  return true;
#endif
}

/**
 * @brief Sets the light detection to "light on" to keep the uC running.
 */
void light::setOn()
{
  PORTn_func(NLIGHT_ON_PORT_NAME,PINnCTRL(NLIGHT_ON_PIN)) = PORT_ISC_INPUT_DISABLE_gc;
  PORTn_func(NLIGHT_ON_PORT_NAME,DIRSET) = 1<<NLIGHT_ON_PIN;
  PORTn_func(NLIGHT_ON_PORT_NAME,OUTCLR) = 1<<NLIGHT_ON_PIN;
}

/**
 * @brief Clears the overwritten light detection 
 */
void light::clearOn()
{
  PORTn_func(NLIGHT_ON_PORT_NAME,PINnCTRL(NLIGHT_ON_PIN)) = PORT_ISC_LEVEL_gc;
  PORTn_func(NLIGHT_ON_PORT_NAME,DIRCLR) = 1<<NLIGHT_ON_PIN;
}

#ifndef LIGHT_ALWAYS_ON
ISR(port_INTn_vect(NLIGHT_ON_PORT_NAME,0))
{
  
}
#endif