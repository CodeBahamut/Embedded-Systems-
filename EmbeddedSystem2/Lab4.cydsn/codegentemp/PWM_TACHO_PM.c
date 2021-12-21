/*******************************************************************************
* File Name: PWM_TACHO_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_TACHO.h"

static PWM_TACHO_backupStruct PWM_TACHO_backup;


/*******************************************************************************
* Function Name: PWM_TACHO_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_TACHO_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_TACHO_SaveConfig(void) 
{

    #if(!PWM_TACHO_UsingFixedFunction)
        #if(!PWM_TACHO_PWMModeIsCenterAligned)
            PWM_TACHO_backup.PWMPeriod = PWM_TACHO_ReadPeriod();
        #endif /* (!PWM_TACHO_PWMModeIsCenterAligned) */
        PWM_TACHO_backup.PWMUdb = PWM_TACHO_ReadCounter();
        #if (PWM_TACHO_UseStatus)
            PWM_TACHO_backup.InterruptMaskValue = PWM_TACHO_STATUS_MASK;
        #endif /* (PWM_TACHO_UseStatus) */

        #if(PWM_TACHO_DeadBandMode == PWM_TACHO__B_PWM__DBM_256_CLOCKS || \
            PWM_TACHO_DeadBandMode == PWM_TACHO__B_PWM__DBM_2_4_CLOCKS)
            PWM_TACHO_backup.PWMdeadBandValue = PWM_TACHO_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_TACHO_KillModeMinTime)
             PWM_TACHO_backup.PWMKillCounterPeriod = PWM_TACHO_ReadKillTime();
        #endif /* (PWM_TACHO_KillModeMinTime) */

        #if(PWM_TACHO_UseControl)
            PWM_TACHO_backup.PWMControlRegister = PWM_TACHO_ReadControlRegister();
        #endif /* (PWM_TACHO_UseControl) */
    #endif  /* (!PWM_TACHO_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_TACHO_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_TACHO_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_TACHO_RestoreConfig(void) 
{
        #if(!PWM_TACHO_UsingFixedFunction)
            #if(!PWM_TACHO_PWMModeIsCenterAligned)
                PWM_TACHO_WritePeriod(PWM_TACHO_backup.PWMPeriod);
            #endif /* (!PWM_TACHO_PWMModeIsCenterAligned) */

            PWM_TACHO_WriteCounter(PWM_TACHO_backup.PWMUdb);

            #if (PWM_TACHO_UseStatus)
                PWM_TACHO_STATUS_MASK = PWM_TACHO_backup.InterruptMaskValue;
            #endif /* (PWM_TACHO_UseStatus) */

            #if(PWM_TACHO_DeadBandMode == PWM_TACHO__B_PWM__DBM_256_CLOCKS || \
                PWM_TACHO_DeadBandMode == PWM_TACHO__B_PWM__DBM_2_4_CLOCKS)
                PWM_TACHO_WriteDeadTime(PWM_TACHO_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_TACHO_KillModeMinTime)
                PWM_TACHO_WriteKillTime(PWM_TACHO_backup.PWMKillCounterPeriod);
            #endif /* (PWM_TACHO_KillModeMinTime) */

            #if(PWM_TACHO_UseControl)
                PWM_TACHO_WriteControlRegister(PWM_TACHO_backup.PWMControlRegister);
            #endif /* (PWM_TACHO_UseControl) */
        #endif  /* (!PWM_TACHO_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_TACHO_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_TACHO_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_TACHO_Sleep(void) 
{
    #if(PWM_TACHO_UseControl)
        if(PWM_TACHO_CTRL_ENABLE == (PWM_TACHO_CONTROL & PWM_TACHO_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_TACHO_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_TACHO_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_TACHO_UseControl) */

    /* Stop component */
    PWM_TACHO_Stop();

    /* Save registers configuration */
    PWM_TACHO_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_TACHO_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_TACHO_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_TACHO_Wakeup(void) 
{
     /* Restore registers values */
    PWM_TACHO_RestoreConfig();

    if(PWM_TACHO_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_TACHO_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
