//Hardware specifications

#include "macro_generation.h"
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



#define USER_SWITCH_PORT_NAME       A
#define USER_SWITCH_PORT            PORT_(USER_SWITCH_PORT_NAME)
#define USER_SWITCH_COUNT           (6)

#define NLIGHT_ON_PORT_NAME         H
#define NLIGHT_ON_PORT              PORT_(NLIGHT_ON_PORT_NAME)
#define NLIGHT_ON_PIN_NR            2
#define NLIGNT_ON_PIN               PIN(NLIGHT_ON_PIN_NR)

#define WIFI_ENABLE_PORT_NAME       K       
#define WIFI_ENABLE_PORT            PORT_(WIFI_ENABLE_PORT_NAME)
#define WIFI_ENABLE_PIN_NR          6
#define WIFI_ENABLE_PIN             PIN(WIFI_ENABLE_PIN_NR)
#define WIFI_USART_NAME             USARTD1

#endif