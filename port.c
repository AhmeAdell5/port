/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmed Adel 
 ******************************************************************************/

#include "port.h"
#include "port_regs.h"
#include "Det.h"
#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "tm4c123gh6pm_registers.h"

/* AUTOSAR Version checking between Det and port Modules */
#if ((DET_AR_MAJOR_VERSION != port_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != port_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != port_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC uint8 port_Status = port_NOT_INITIALIZED;
STATIC const Port_Configpins * PortChannels = NULL_PTR;
uint16 g_Module_Id ;
uint16 g_Vendor_Id ;
uint8 g_sw_major_version;
uint8 g_sw_minor_version;
uint8 g_sw_patch_version;
/************************************************************************************
* Service Name: port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): PortChannels - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the port module.
************************************************************************************/

void Port_Init( const Port_ConfigType* ConfigPtr )
{
   PortChannels = ConfigPtr->pins ;
  
  #if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == PortChannels)
	{
		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID, port_INIT_SID,
		     PORT_E_PARAM_CONFIG_ID);
	}
	else
#endif
        {
 uint8 counter =0;
   
 for (counter=0;counter<total_numper_of_pins;counter++ )
 {
 volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
 volatile uint32 delay = 0;

 switch(PortChannels[counter].port_num)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
 
/* Enable clock for PORT and allow time for clock to start*/
    SYSCTL_REGCGC2_REG |= (1<<PortChannels[counter].port_num);
    delay = SYSCTL_REGCGC2_REG;
    
     if( ((PortChannels[counter].port_num == 3) && (PortChannels[counter].pin_num == 7)) || ((PortChannels[counter].port_num == 5) && (PortChannels[counter].pin_num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[counter].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (PortChannels[counter].pin_num == 2) && (PortChannels[counter].pin_num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }
    /*    check if the pin support Adc module   */
    if(( counter==12 ||counter==13 || counter==20 || counter==21||counter==22||counter==23||counter==28||counter==29||counter==30||counter==31||counter==32||counter==33) && PortChannels[counter].mode!=PORT_PIN_MODE_DIO &&  PortChannels[counter].mode!=icu_mode && PortChannels[counter].direction== PORT_PIN_IN )
    {

     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[counter].pin_num);   /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */ 
    
     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[counter].pin_num);  /* Set the corresponding bit in the GPIOAMSE register to enable analog functionality on this pin */
    
     *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( PortChannels[counter].mode << (PortChannels[counter].pin_num * 4)); 
      
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[counter].pin_num);
      if(PortChannels[counter].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pin_num); 
    }
      else if(PortChannels[counter].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pin_num); 
    }
      else
      {
      
      }
      
        
    }
       
    
else if (PortChannels[counter].mode == PORT_PIN_MODE_DIO)
{
  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[counter].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[counter].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortChannels[counter].pin_num * 4));     /* Clear the PMCx bits for this pin */
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[counter].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
   
   if(PortChannels[counter].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if(PortChannels[counter].initial_value == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[counter].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PortChannels[counter].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if(PortChannels[counter].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(PortChannels[counter].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) ,PortChannels[counter].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(PortChannels[counter].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[counter].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PortChannels[counter].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortChannels[counter].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }
    
}
 

else
{
  
  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortChannels[counter].pin_num); 
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortChannels[counter].pin_num);
  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortChannels[counter].pin_num); 
  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( PortChannels[counter].mode << (PortChannels[counter].pin_num * 4));
  
    if(PortChannels[counter].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pin_num); 
    }
      else if(PortChannels[counter].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortChannels[counter].pin_num); 
    }
      else
      {
      
      }
}
 
 

 }
            
        }
port_Status = port_INITIALIZED;
            
}

/************************************************************************************
* Service Name: Port_SetPinDirection
 Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin , Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: The function Port_SetPinDirection shall set the port pin direction during runtime.
************************************************************************************/
#if ( Port_Set_PinDirection == STD_ON )

void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{

	boolean error = FALSE;

#if (port_DEV_ERROR_DETECT == STD_ON)
	
	if (port_NOT_INITIALIZED == port_Status)
	{
		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				Port_Set_PinDirection_SID, PORT_E_UNINIT_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

        
	if (pin <= total_numper_of_pins)
	{

		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				 Port_Set_PinDirection_SID, PORT_E_PARAM_PIN_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        if (PortChannels[pin].direction_change== STD_OFF)
	{

		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				 Port_Set_PinDirection_SID, PORT_E_DIRECTION_UNCHANGEABLE_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
/* In-case there are no errors */
	if(FALSE == error)
	{
          
          volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
 volatile uint32 delay = 0;

 switch( PortChannels[pin].port_num)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
          
          
         if(direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  PortChannels[pin].pin_num); 
    }
      else if(direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,PortChannels[pin].pin_num); 
    }
      else
      {
      
      } 
           
        }
      
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
 Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): Non
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/

void Port_RefreshPortDirection( void )
{
boolean error = FALSE;

#if (port_DEV_ERROR_DETECT == STD_ON)
	
	if (port_NOT_INITIALIZED == port_Status)
	{
		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				Port_Set_PinDirection_SID, PORT_E_UNINIT_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

#endif

if(FALSE == error)
	{
uint8 counter ;
         for (counter=0;counter<total_numper_of_pins;counter++ )
 {
 volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
 volatile uint32 delay = 0;

 switch( PortChannels[counter].port_num)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    } 
          
       if( PortChannels[counter].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  PortChannels[counter].pin_num); 
    }
      else if( PortChannels[counter].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,PortChannels[counter].pin_num); 
    }
      else
      {
      
      }   
          
          
        }
        } 
}   


/************************************************************************************
* Service Name: Port_GetVersionInfo
 Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy:non reentrant
* Parameters (in): None
* Parameters (inout): Pointer to where to store the version information of this module.
* Parameters (out): None
* Return value: None
* Description: Returns the version information of this module..
************************************************************************************/
#if (port_VERSION_INFO_API == STD_ON )

void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
boolean error = FALSE;

#if (port_DEV_ERROR_DETECT == STD_ON)
	
	if (port_NOT_INITIALIZED == port_Status)
	{
		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				Port_Get_VersionInfo_SID, PORT_E_UNINIT_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

if (NULL_PTR == versioninfo)
	{
		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID, Port_Get_VersionInfo_SID,
		     PORT_E_PARAM_CONFIG_ID);
	}

else 
{
/* No Action Required */
}
#endif 
if(FALSE == error)
{

g_Module_Id = versioninfo->moduleID ;

g_Vendor_Id = versioninfo-> vendorID ;

g_sw_major_version = versioninfo->sw_major_version  ;

g_sw_minor_version = versioninfo->sw_minor_version  ;

g_sw_patch_version = versioninfo->sw_patch_version  ;
                               

}

}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
 Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin ,Mode
* Parameters (inout): none
* Parameters (out): None
* Return value: None
* Description: The function Port_SetPinMode shall set the port pin mode of the referenced pin during runtime
************************************************************************************/

#if ( Port_Set_PinMode  == STD_ON )
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{

boolean error = FALSE;

#if (port_DEV_ERROR_DETECT == STD_ON)
	
	if (port_NOT_INITIALIZED == port_Status)
	{
		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				Port_Set_PinMode_SID, PORT_E_UNINIT_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

        
	if (pin <= total_numper_of_pins)
	{

		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				 Port_Set_PinMode_SID, PORT_E_PARAM_PIN_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        if (PortChannels[pin].mode_change== STD_OFF)
	{

		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				 Port_Set_PinMode_SID, PPORT_E_MODE_UNCHANGEABLE_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        if (PortChannels[pin].mode > largest_mode_num )
	{

		Det_ReportError(port_MODULE_ID, port_INSTANCE_ID,
				 Port_Set_PinMode_SID, PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
/* In-case there are no errors */
	if(FALSE == error)
	{
     volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
 volatile uint32 delay = 0;

 switch( PortChannels[pin].port_num)
    {
        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
          
         
    }
  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( mode << (PortChannels[pin].pin_num * 4)); 
 
        }

}
#endif
