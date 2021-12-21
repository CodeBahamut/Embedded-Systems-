/*******************************************************************************
* File Name: BUZZER_PM.c
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

#include "BUZZER.h"

static BUZZER_backupStruct BUZZER_backup;


/*******************************************************************************
* Function Name: BUZZER_SaveConfig
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
*  BUZZER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BUZZER_SaveConfig(void) 
{

    #if(!BUZZER_UsingFixedFunction)
        #if(!BUZZER_PWMModeIsCenterAligned)
            BUZZER_backup.PWMPeriod = BUZZER_ReadPeriod();
        #endif /* (!BUZZER_PWMModeIsCenterAligned) */
        BUZZER_backup.PWMUdb = BUZZER_ReadCounter();
        #if (BUZZER_UseStatus)
            BUZZER_backup.InterruptMaskValue = BUZZER_STATUS_MASK;
        #endif /* (BUZZER_UseStatus) */

        #if(BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_256_CLOCKS || \
            BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_2_4_CLOCKS)
            BUZZER_backup.PWMdeadBandValue = BUZZER_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BUZZER_KillModeMinTime)
             BUZZER_backup.PWMKillCounterPeriod = BUZZER_ReadKillTime();
        #endif /* (BUZZER_KillModeMinTime) */

        #if(BUZZER_UseControl)
            BUZZER_backup.PWMControlRegister = BUZZER_ReadControlRegister();
        #endif /* (BUZZER_UseControl) */
    #endif  /* (!BUZZER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BUZZER_RestoreConfig
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
*  BUZZER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BUZZER_RestoreConfig(void) 
{
        #if(!BUZZER_UsingFixedFunction)
            #if(!BUZZER_PWMModeIsCenterAligned)
                BUZZER_WritePeriod(BUZZER_backup.PWMPeriod);
            #endif /* (!BUZZER_PWMModeIsCenterAligned) */

            BUZZER_WriteCounter(BUZZER_backup.PWMUdb);

            #if (BUZZER_UseStatus)
                BUZZER_STATUS_MASK = BUZZER_backup.InterruptMaskValue;
            #endif /* (BUZZER_UseStatus) */

            #if(BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_256_CLOCKS || \
                BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_2_4_CLOCKS)
                BUZZER_WriteDeadTime(BUZZER_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BUZZER_KillModeMinTime)
                BUZZER_WriteKillTime(BUZZER_backup.PWMKillCounterPeriod);
            #endif /* (BUZZER_KillModeMinTime) */

            #if(BUZZER_UseControl)
                BUZZER_WriteControlRegister(BUZZER_backup.PWMControlRegister);
            #endif /* (BUZZER_UseControl) */
        #endif  /* (!BUZZER_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BUZZER_Sleep
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
*  BUZZER_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BUZZER_Sleep(void) 
{
    #if(BUZZER_UseControl)
        if(BUZZER_CTRL_ENABLE == (BUZZER_CONTROL & BUZZER_CTRL_ENABLE))
        {
            /*Component is enabled */
            BUZZER_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BUZZER_backup.PWMEnableState = 0u;
        }
    #endif /* (BUZZER_UseControl) */

    /* Stop component */
    BUZZER_Stop();

    /* Save registers configuration */
    BUZZER_SaveConfig();
}


/*******************************************************************************
* Function Name: BUZZER_Wakeup
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
*  BUZZER_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BUZZER_Wakeup(void) 
{
     /* Restore registers values */
    BUZZER_RestoreConfig();

    if(BUZZER_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BUZZER_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
