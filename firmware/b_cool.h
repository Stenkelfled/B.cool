//Hardware specifications

#include "macro_generation.h"
#include <avr/io.h>
#include <stdint.h>

#ifndef _B_COOL_H
#define _B_COOL_H

//Beer slot definition
#define BEER_CAPACITY               (11)
#define SLOT_GROUP_COUNT            (2) //number of slot groups (aka how many ports are in use for the beer-recognition-switches)
#define SLOT_GROUP_0_PORT_NAME      J
#define SLOT_GROUP_0_PORT           PORT_(SLOT_GROUP_0_PORT_NAME)
#define SLOT_GROUP_0_MEMBER_COUNT   (6) //number of slots in group 0
#define SLOT_GROUP_0_START          (0)
#define SLOT_GROUP_0_END            (5)
#define SLOT_GROUP_1_PORT_NAME      K
#define SLOT_GROUP_1_PORT           PORT_(SLOT_GROUP_1_PORT_NAME)
#define SLOT_GROUP_1_MEMBER_COUNT   (5)
#define SLOT_GROUP_1_START          (0)
#define SLOT_GROUP_1_END            (4)

//Beer LED definition
#define LED_PRESCALER               TC_CLKSEL_DIV1_gc
#define LED_PERIOD                  (2^10)
#define LED_WGMODE                  TC_WGMODE_DS_T_gc

#define LED_ON_VALUE               LED_PERIOD //maximal value for LED compare register (highest brightness!)

#define LED_SLOT0_RED               &TCC0_CCA
#define LED_SLOT0_RED_PORT_NAME     C
#define LED_SLOT0_RED_PIN           0
#define LED_SLOT0_GREEN             &TCC0_CCB
#define LED_SLOT0_GREEN_PORT_NAME   C
#define LED_SLOT0_GREEN_PIN         1
#define LED_SLOT1_RED               &TCC0_CCC
#define LED_SLOT1_RED_PORT_NAME     C
#define LED_SLOT1_RED_PIN           2
#define LED_SLOT1_GREEN             &TCC0_CCD
#define LED_SLOT1_GREEN_PORT_NAME   C
#define LED_SLOT1_GREEN_PIN         3
#define LED_SLOT2_RED               &TCC1_CCA
#define LED_SLOT2_RED_PORT_NAME     C
#define LED_SLOT2_RED_PIN           4
#define LED_SLOT2_GREEN             &TCC1_CCB
#define LED_SLOT2_GREEN_PORT_NAME   C
#define LED_SLOT2_GREEN_PIN         5
#define LED_SLOT3_RED               &TCD0_CCA
#define LED_SLOT3_RED_PORT_NAME     D
#define LED_SLOT3_RED_PIN           0
#define LED_SLOT3_GREEN             &TCD0_CCB
#define LED_SLOT3_GREEN_PORT_NAME   D
#define LED_SLOT3_GREEN_PIN         1
#define LED_SLOT4_RED               &TCD0_CCC
#define LED_SLOT4_RED_PORT_NAME     D
#define LED_SLOT4_RED_PIN           2
#define LED_SLOT4_GREEN             &TCD0_CCD
#define LED_SLOT4_GREEN_PORT_NAME   D
#define LED_SLOT4_GREEN_PIN         3
#define LED_SLOT5_RED               &TCD1_CCA
#define LED_SLOT5_RED_PORT_NAME     D
#define LED_SLOT5_RED_PIN           4
#define LED_SLOT5_GREEN             &TCD1_CCB
#define LED_SLOT5_GREEN_PORT_NAME   D
#define LED_SLOT5_GREEN_PIN         5
#define LED_SLOT6_RED               &TCE0_CCA
#define LED_SLOT6_RED_PORT_NAME     E
#define LED_SLOT6_RED_PIN           0
#define LED_SLOT6_GREEN             &TCE0_CCB
#define LED_SLOT6_GREEN_PORT_NAME   E
#define LED_SLOT6_GREEN_PIN         1
#define LED_SLOT7_RED               &TCE0_CCC
#define LED_SLOT7_RED_PORT_NAME     E
#define LED_SLOT7_RED_PIN           2
#define LED_SLOT7_GREEN             &TCE0_CCD
#define LED_SLOT7_GREEN_PORT_NAME   E
#define LED_SLOT7_GREEN_PIN         3
#define LED_SLOT8_RED               &TCE1_CCA
#define LED_SLOT8_RED_PORT_NAME     E
#define LED_SLOT8_RED_PIN           4
#define LED_SLOT8_GREEN             &TCE1_CCB
#define LED_SLOT8_GREEN_PORT_NAME   E
#define LED_SLOT8_GREEN_PIN         5
#define LED_SLOT9_RED               &TCF0_CCA
#define LED_SLOT9_RED_PORT_NAME     F
#define LED_SLOT9_RED_PIN           0
#define LED_SLOT9_GREEN             &TCF0_CCB
#define LED_SLOT9_GREEN_PORT_NAME   F
#define LED_SLOT9_GREEN_PIN         1
#define LED_SLOT10_RED              &TCF0_CCC
#define LED_SLOT10_RED_PORT_NAME     F
#define LED_SLOT10_RED_PIN           2
#define LED_SLOT10_GREEN            &TCF0_CCD
#define LED_SLOT10_GREEN_PORT_NAME   F
#define LED_SLOT10_GREEN_PIN         3
#if BEER_CAPACITY > 11
  #error Please define the LEDs for the missing slots!
#endif


#define USER_SWITCH_PORT_NAME       A
#define USER_SWITCH_PORT            PORT_(USER_SWITCH_PORT_NAME)
#define USER_SWITCH_COUNT           (6)

#define NLIGHT_ON_PORT_NAME         H
#define NLIGHT_ON_PORT              PORT_(NLIGHT_ON_PORT_NAME)
#define NLIGHT_ON_PIN               2

#define WIFI_ENABLE_PORT_NAME       K       
#define WIFI_ENABLE_PORT            PORT_(WIFI_ENABLE_PORT_NAME)
#define WIFI_ENABLE_PIN             6
#define WIFI_USART_NAME             USARTD1

#endif