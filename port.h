/******************************************************************************
 *
 * Module: port
 *
 * File Name: port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - port Driver
 *
 * Author: Ahmed Adel
 ******************************************************************************/
#ifndef port_h 
#define port_h 

/* Id for the company in the AUTOSAR
                                        */
#define port_VENDOR_ID    (1000U)

/* port Module Id */
#define port_MODULE_ID    (124U)

/* port Instance Id */
#define port_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define port_SW_MAJOR_VERSION           (1U)
#define port_SW_MINOR_VERSION           (0U)
#define port_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define port_AR_RELEASE_MAJOR_VERSION   (4U)
#define port_AR_RELEASE_MINOR_VERSION   (0U)
#define port_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for port Status
 */
#define port_INITIALIZED                (1U)
#define port_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != port_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != port_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* port Pre-Compile Configuration Header file */
#include "port_cfg.h"

/* AUTOSAR Version checking between port_cfg.h and port.h files */
#if ((port_CFG_AR_RELEASE_MAJOR_VERSION != port_AR_RELEASE_MAJOR_VERSION)\
 ||  (port_CFG_AR_RELEASE_MINOR_VERSION != port_AR_RELEASE_MINOR_VERSION)\
 ||  (port_CFG_AR_RELEASE_PATCH_VERSION != port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between port_Cfg.h and port.h files */
#if ((port_CFG_SW_MAJOR_VERSION != port_SW_MAJOR_VERSION)\
 ||  (port_CFG_SW_MINOR_VERSION != port_SW_MINOR_VERSION)\
 ||  (port_CFG_SW_PATCH_VERSION != port_SW_PATCH_VERSION))
  #error "The SW version of port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files and defines */
#include "Common_Macros.h"

#define portA  0
#define portB  1
#define portC  2
#define portD  3
#define portE  4
#define portF  5

#define pin0   0
#define pin1   1
#define pin2   2
#define pin3   3
#define pin4   4
#define pin5   5
#define pin6   6
#define pin7   7

#define total_numper_of_pins     39
#define initial_value_            0

#define largest_mode_num          14 
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for Port_Init*/
#define Port_Init_SID           (uint8)0x00

/* Service ID for Port_Set_PinDirection*/
#define Port_Set_PinDirection_SID       (uint8)0x01

/* Service ID for Port_Refresh_Port_Direction*/
#define Port_Refresh_Port_Direction_SID       (uint8)0x02

/* Service ID for Port_Get_VersionInfo*/
#define Port_Get_VersionInfo_SID       (uint8)0x03

/* Service ID for Port_Set_PinMode*/
#define  Port_Set_PinMode_SID       (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN_ID (uint8)0x0A

/* DET code to report when Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE_ID (uint8)0x0B

/* DET code to report when API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG_ID (uint8)0x0C

/* DET code to report when API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE_ID (uint8)0x0E

/* DET code to report whenAPI service called without module initialization */
#define PORT_E_UNINIT_ID (uint8)0x0F

/* DET code to report when APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER_ID (uint8)0x10
/* API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE (uint8)0x0D

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
#include "port_types.h"

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to Initializes the Port Driver module. */
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Function for Sets the port pin direction */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );

/* Function for Refreshes port direction. */
void Port_RefreshPortDirection( void );

/* Function for Returns the version information of this module.. */
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );

/* Function for Sets the port pin mode*/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

#include "port_PBcfg.h"





#endif
