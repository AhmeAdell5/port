/******************************************************************************
 *
 * Module: port.h
 *
 * File Name: port_types.h
 *
 * Description: Header file for types of port driver  
 *
 * Author: Ahmed Adel 
 ******************************************************************************/
#ifndef port_types_h 
#define port_types_h

#include "std_types.h"
#include "Common_Macros.h"

/* The type Port_PinType shall be used for the symbolic name of a Port Pin */
typedef uint8 Port_PinType ;

/* The type Port_PinDirectionType is a type for defining the direction of a Port Pin*/
typedef enum 
{
PORT_PIN_IN = 0 ,PORT_PIN_OUT = 1
}Port_PinDirectionType;

/* A port pin shall be configurable with a number of port pin modes (type Port_PinModeType) */

typedef uint8 Port_PinModeType;

/*  Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF = 0,PULL_UP = 1,PULL_DOWN = 2
}Port_InternalResistor;


/* enum to hold the possiblity of change the direction */
typedef enum
{
 STD_OFF_ = 0,STD_ON_ = 1 
}change_direction;

/* enum to hold the possiblity of change the mode */

typedef enum
{
 STD_OFF__ ,STD_ON__  
}change_mode;

/* The type Port_ConfigType is a type for the external data structure containing the initialization data for the PORT Driver*/
typedef struct 
{ 
uint8 port_num; 
uint8 pin_num; 
Port_PinDirectionType direction;
Port_PinModeType mode;
Port_InternalResistor resistor;
change_direction direction_change;
change_mode mode_change;
uint8 initial_value;
}Port_Configpins;

typedef struct
{
Port_Configpins pins[total_numper_of_pins] ;

}Port_ConfigType;

#endif
