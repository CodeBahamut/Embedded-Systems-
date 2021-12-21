/*******************************************************************************
* File Name: Counter_TACHO_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_TACHO.h"

static Counter_TACHO_backupStruct Counter_TACHO_backup;


/*******************************************************************************
* Function Name: Counter_TACHO_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_TACHO_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_TACHO_SaveConfig(void) 
{
    #if (!Counter_TACHO_UsingFixedFunction)

        Counter_TACHO_backup.CounterUdb = Counter_TACHO_ReadCounter();

        #if(!Counter_TACHO_ControlRegRemoved)
            Counter_TACHO_backup.CounterControlRegister = Counter_TACHO_ReadControlRegister();
        #endif /* (!Counter_TACHO_ControlRegRemoved) */

    #endif /* (!Counter_TACHO_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_TACHO_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_TACHO_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_TACHO_RestoreConfig(void) 
{      
    #if (!Counter_TACHO_UsingFixedFunction)

       Counter_TACHO_WriteCounter(Counter_TACHO_backup.CounterUdb);

        #if(!Counter_TACHO_ControlRegRemoved)
            Counter_TACHO_WriteControlRegister(Counter_TACHO_backup.CounterControlRegister);
        #endif /* (!Counter_TACHO_ControlRegRemoved) */

    #endif /* (!Counter_TACHO_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_TACHO_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_TACHO_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_TACHO_Sleep(void) 
{
    #if(!Counter_TACHO_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_TACHO_CTRL_ENABLE == (Counter_TACHO_CONTROL & Counter_TACHO_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_TACHO_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_TACHO_backup.CounterEnableState = 0u;
        }
    #else
        Counter_TACHO_backup.CounterEnableState = 1u;
        if(Counter_TACHO_backup.CounterEnableState != 0u)
        {
            Counter_TACHO_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_TACHO_ControlRegRemoved) */
    
    Counter_TACHO_Stop();
    Counter_TACHO_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_TACHO_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_TACHO_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_TACHO_Wakeup(void) 
{
    Counter_TACHO_RestoreConfig();
    #if(!Counter_TACHO_ControlRegRemoved)
        if(Counter_TACHO_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_TACHO_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_TACHO_ControlRegRemoved) */
    
}


/* [] END OF FILE */
