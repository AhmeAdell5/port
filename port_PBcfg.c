/*************************************************************************************************
 *
 * Module: port
 *
 * File Name: port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - port Driver
 *
 * Author: Ahmed Adel
 **************************************************************************************************/
#include "port.h"

/*
 * Module Version 1.0.0
 */
#define port_PBCFG_SW_MAJOR_VERSION              (1U)
#define port_PBCFG_SW_MINOR_VERSION              (0U)
#define port_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define port_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define port_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define port_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between port_PBcfg.c and port.h files */
#if ((port_PBCFG_AR_RELEASE_MAJOR_VERSION != port_AR_RELEASE_MAJOR_VERSION)\
 ||  (port_PBCFG_AR_RELEASE_MINOR_VERSION != port_AR_RELEASE_MINOR_VERSION)\
 ||  (port_PBCFG_AR_RELEASE_PATCH_VERSION != port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between port_PBcfg.c and port.h files */
#if ((port_PBCFG_SW_MAJOR_VERSION != port_SW_MAJOR_VERSION)\
 ||  (port_PBCFG_SW_MINOR_VERSION != port_SW_MINOR_VERSION)\
 ||  (port_PBCFG_SW_PATCH_VERSION != port_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with port_Init API */

const Port_ConfigType  port_Configuration =  {                 portA,pin0,PORT_PIN_OUT,uart_mode,OFF,STD_OFF_,STD_OFF__,initial_value_ , /************/
                                                              portA,pin1,PORT_PIN_OUT,uart_mode,OFF,STD_OFF_,STD_OFF__,initial_value_,   /************/
                                                              portA,pin2,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portA,pin3,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portA,pin4,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portA,pin5,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portA,pin6,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portA,pin7,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              
                                                              
                                                              portB,pin0,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portB,pin1,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portB,pin2,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portB,pin3,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portB,pin4,PORT_PIN_OUT,pwm_mode,OFF,STD_OFF_,STD_OFF__,initial_value_,      /************/
                                                              portB,pin5,PORT_PIN_OUT,pwm_mode,OFF,STD_OFF_,STD_OFF__,initial_value_,       /************/
                                                              portB,pin6,PORT_PIN_IN,icu_mode,OFF,STD_OFF_,STD_OFF__,initial_value_,           /************/
                                                              portB,pin7,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              
                                                              
                                                              portC,pin4,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portC,pin5,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portC,pin6,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portC,pin7,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              
                                                              
                                                              portD,pin0,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin1,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin2,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin3,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin4,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin5,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin6,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portD,pin7,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              
                                                              
                                                              portE,pin0,PORT_PIN_OUT,uart_mode,OFF,STD_OFF_,STD_OFF__,initial_value_, /********/
                                                              portE,pin1,PORT_PIN_OUT,uart_mode,OFF,STD_OFF_,STD_OFF__,initial_value_, /***********/
                                                              portE,pin2,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portE,pin3,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portE,pin4,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portE,pin5,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              
                                                              
                                                              portF,pin0,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portF,pin1 ,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,/*     the configuration of led in (pf1)        */
                                                              portF,pin2,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portF,pin3,PORT_PIN_OUT,PORT_PIN_MODE_DIO,OFF,STD_OFF_,STD_OFF__,initial_value_,
                                                              portF,pin4,PORT_PIN_OUT,PORT_PIN_MODE_DIO,PULL_UP,STD_OFF_, STD_OFF__,initial_value_,

                                                                                                                                               } ;

Std_VersionInfoType information ={STD_TYPES_VENDOR_ID ,port_MODULE_ID ,port_SW_MAJOR_VERSION , port_SW_MINOR_VERSION ,port_SW_PATCH_VERSION   };








