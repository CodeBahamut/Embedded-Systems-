/*******************************************************************************
* File Name: PWM_MOTOR_SPEED_PM.c
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

#include "PWM_MOTOR_SPEED.h"

static PWM_MOTOR_SPEED_backupStruct PWM_MOTOR_SPEED_backup;


/*******************************************************************************
* Function Name: PWM_MOTOR_SPEED_SaveConfig
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
*  PWM_MOTOR_SPEED_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_MOTOR_SPEED_SaveConfig(void) 
{

    #if(!PWM_MOTOR_SPEED_UsingFixedFunction)
        #if(!PWM_MOTOR_SPEED_PWMModeIsCenterAligned)
            PWM_MOTOR_SPEED_backup.PWMPeriod = PWM_MOTOR_SPEED_ReadPeriod();
        #endif /* (!PWM_MOTOR_SPEED_PWMModeIsCenterAligned) */
        PWM_MOTOR_SPEED_backup.PWMUdb = PWM_MOTOR_SPEED_ReadCounter();
        #if (PWM_MOTOR_SPEED_UseStatus)
            PWM_MOTOR_SPEED_backup.InterruptMaskValue = PWM_MOTOR_SPEED_STATUS_MASK;
        #endif /* (PWM_MOTOR_SPEED_UseStatus) */

        #if(PWM_MOTOR_SPEED_DeadBandMode == PWM_MOTOR_SPEED__B_PWM__DBM_256_CLOCKS || \
            PWM_MOTOR_SPEED_DeadBandMode == PWM_MOTOR_SPEED__B_PWM__DBM_2_4_CLOCKS)
            PWM_MOTOR_SPEED_backup.PWMdeadBandValue = PWM_MOTOR_SPEED_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_MOTOR_SPEED_KillModeMinTime)
             PWM_MOTOR_SPEED_backup.PWMKillCounterPeriod = PWM_MOTOR_SPEED_ReadKillTime();
        #endif /* (PWM_MOTOR_SPEED_KillModeMinTime) */

        #if(PWM_MOTOR_SPEED_UseControl)
            PWM_MOTOR_SPEED_backup.PWMControlRegister = PWM_MOTOR_SPEED_ReadControlRegister();
        #endif /* (PWM_MOTOR_SPEED_UseControl) */
    #endif  /* (!PWM_MOTOR_SPEED_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_MOTOR_SPEED_RestoreConfig
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
*  PWM_MOTOR_SPEED_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_MOTOR_SPEED_RestoreConfig(void) 
{
        #if(!PWM_MOTOR_SPEED_UsingFixedFunction)
            #if(!PWM_MOTOR_SPEED_PWMModeIsCenterAligned)
                PWM_MOTOR_SPEED_WritePeriod(PWM_MOTOR_SPEED_backup.PWMPeriod);
            #endif /* (!PWM_MOTOR_SPEED_PWMModeIsCenterAligned) */

            PWM_MOTOR_SPEED_WriteCounter(PWM_MOTOR_SPEED_backup.PWMUdb);

            #if (PWM_MOTOR_SPEED_UseStatus)
                PWM_MOTOR_SPEED_STATUS_MASK = PWM_MOTOR_SPEED_backup.InterruptMaskValue;
            #endif /* (PWM_MOTOR_SPEED_UseStatus) */

            #if(PWM_MOTOR_SPEED_DeadBandMode == PWM_MOTOR_SPEED__B_PWM__DBM_256_CLOCKS || \
                PWM_MOTOR_SPEED_DeadBandMode == PWM_MOTOR_SPEED__B_PWM__DBM_2_4_CLOCKS)
                PWM_MOTOR_SPEED_WriteDeadTime(PWM_MOTOR_SPEED_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_MOTOR_SPEED_KillModeMinTime)
                PWM_MOTOR_SPEED_WriteKillTime(PWM_MOTOR_SPEED_backup.PWMKillCounterPeriod);
            #endif /* (PWM_MOTOR_SPEED_KillModeMinTime) */

            #if(PWM_MOTOR_SPEED_UseControl)
                PWM_MOTOR_SPEED_WriteControlRegister(PWM_MOTOR_SPEED_backup.PWMControlRegister);
            #endif /* (PWM_MOTOR_SPEED_UseControl) */
        #endif  /* (!PWM_MOTOR_SPEED_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_MOTOR_SPEED_Sleep
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
*  PWM_MOTOR_SPEED_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_MOTOR_SPEED_Sleep(void) 
{
    #if(PWM_MOTOR_SPEED_UseControl)
        if(PWM_MOTOR_SPEED_CTRL_ENABLE == (PWM_MOTOR_SPEED_CONTROL & PWM_MOTOR_SPEED_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_MOTOR_SPEED_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_MOTOR_SPEED_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_MOTOR_SPEED_UseControl) */

    /* Stop component */
    PWM_MOTOR_SPEED_Stop();

    /* Save registers configuration */
    PWM_MOTOR_SPEED_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_MOTOR_SPEED_Wakeup
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
*  PWM_MOTOR_SPEED_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_MOTOR_SPEED_Wakeup(void) 
{
     /* Restore registers values */
    PWM_MOTOR_SPEED_RestoreConfig();

    if(PWM_MOTOR_SPEED_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_MOTOR_SPEED_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
