/****************************************************************************************************
 *
 * Module: port.h
 *
 * File Name: port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - port Driver
 *
 * Author: Ahmed Adel
 ****************************************************************************************************/
#ifndef port_cfg_h 
#define port_cfg_h 

#include "Std_Types.h"

/*
 * Module Version 1.0.0
 */
#define port_CFG_SW_MAJOR_VERSION              (1U)
#define port_CFG_SW_MINOR_VERSION              (0U)
#define port_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define port_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define port_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define port_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */

#define port_DEV_ERROR_DETECT                (STD_ON)

/* Number of the configured port Channels  */

#define port_CONFIGURED_CHANNLES              (2U)

/*  Pre-compile to enable / disable the use of the function Port_SetPinDirection() */

#define Port_Set_PinDirection                (STD_OFF)

/* Pre-compile to enable disable the use of the function Port_SetPinMode() */

#define Port_Set_PinMode                    (STD_OFF)

/* Pre-compile option for Version Info API */

#define port_VERSION_INFO_API                (STD_OFF)

/* Pre-compile to initial direction of the led (IN or OUT). */

#define Port_Pin_Direction_for_led           (output)

/* Pre-compile to initial direction of the switch (IN or OUT). */

#define Port_Pin_Direction_for_switch        (input)

/* Pre-compile to indicate if the direction is changeable on a port pin during runtime for led */

#define Port_Pin_Direction_Changeable_for_led   (STD_OFF)

/* Pre-compile to indicate if the direction is changeable on a port pin during runtime for switch */

#define Port_Pin_Direction_Changeable_for_switch   (STD_OFF)

/* port Configured Port ID's  */
#define portConf_LED1_PORT_NUM                       5 /* PORTF */
#define portConf_SW1_PORT_NUM                        5 /* PORTF */
/* port Configured Channel ID's */
#define portConf_LED1_CHANNEL_NUM                    1 /* Pin 1 in PORTF */
#define portConf_SW1_CHANNEL_NUM                     4 /* Pin 4 in PORTF */

/* Port pin mode from mode list for use with Port_Init() function.*/

#define PORT_PIN_MODE_DIO                            0

/* Port pin mode from mode list for use with Port_Init() function.*/
#define Port_Pin_Mode_for_led                        0     

#define Port_Pin_Mode_for_swich                      0     

/* Pre-compile to indicate if the mode is changeable on a port pin during runtime for led */

#define Port_Pin_mode_Changeable_for_led   (STD_OFF)

/* Pre-compile to indicate if the mode is changeable on a port pin during runtime for switch */

#define Port_Pin_mode_Changeable_for_switch   (STD_OFF)

#define uart_mode 1
#define icu_mode 7
#define pwm_mode 4



#endif
