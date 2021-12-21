/*******************************************************************************
* File Name: BUZZER.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_BUZZER_H)
#define CY_PWM_BUZZER_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BUZZER_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define BUZZER_Resolution                     (16u)
#define BUZZER_UsingFixedFunction             (0u)
#define BUZZER_DeadBandMode                   (0u)
#define BUZZER_KillModeMinTime                (0u)
#define BUZZER_KillMode                       (0u)
#define BUZZER_PWMMode                        (0u)
#define BUZZER_PWMModeIsCenterAligned         (0u)
#define BUZZER_DeadBandUsed                   (0u)
#define BUZZER_DeadBand2_4                    (0u)

#if !defined(BUZZER_PWMUDB_genblk8_stsreg__REMOVED)
    #define BUZZER_UseStatus                  (1u)
#else
    #define BUZZER_UseStatus                  (0u)
#endif /* !defined(BUZZER_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(BUZZER_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define BUZZER_UseControl                 (1u)
#else
    #define BUZZER_UseControl                 (0u)
#endif /* !defined(BUZZER_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define BUZZER_UseOneCompareMode              (1u)
#define BUZZER_MinimumKillTime                (1u)
#define BUZZER_EnableMode                     (0u)

#define BUZZER_CompareMode1SW                 (0u)
#define BUZZER_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define BUZZER__B_PWM__DISABLED 0
#define BUZZER__B_PWM__ASYNCHRONOUS 1
#define BUZZER__B_PWM__SINGLECYCLE 2
#define BUZZER__B_PWM__LATCHED 3
#define BUZZER__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define BUZZER__B_PWM__DBMDISABLED 0
#define BUZZER__B_PWM__DBM_2_4_CLOCKS 1
#define BUZZER__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define BUZZER__B_PWM__ONE_OUTPUT 0
#define BUZZER__B_PWM__TWO_OUTPUTS 1
#define BUZZER__B_PWM__DUAL_EDGE 2
#define BUZZER__B_PWM__CENTER_ALIGN 3
#define BUZZER__B_PWM__DITHER 5
#define BUZZER__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define BUZZER__B_PWM__LESS_THAN 1
#define BUZZER__B_PWM__LESS_THAN_OR_EQUAL 2
#define BUZZER__B_PWM__GREATER_THAN 3
#define BUZZER__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define BUZZER__B_PWM__EQUAL 0
#define BUZZER__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!BUZZER_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!BUZZER_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!BUZZER_PWMModeIsCenterAligned) */
        #if (BUZZER_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (BUZZER_UseStatus) */

        /* Backup for Deadband parameters */
        #if(BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_256_CLOCKS || \
            BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(BUZZER_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (BUZZER_KillModeMinTime) */

        /* Backup control register */
        #if(BUZZER_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (BUZZER_UseControl) */

    #endif /* (!BUZZER_UsingFixedFunction) */

}BUZZER_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    BUZZER_Start(void) ;
void    BUZZER_Stop(void) ;

#if (BUZZER_UseStatus || BUZZER_UsingFixedFunction)
    void  BUZZER_SetInterruptMode(uint8 interruptMode) ;
    uint8 BUZZER_ReadStatusRegister(void) ;
#endif /* (BUZZER_UseStatus || BUZZER_UsingFixedFunction) */

#define BUZZER_GetInterruptSource() BUZZER_ReadStatusRegister()

#if (BUZZER_UseControl)
    uint8 BUZZER_ReadControlRegister(void) ;
    void  BUZZER_WriteControlRegister(uint8 control)
          ;
#endif /* (BUZZER_UseControl) */

#if (BUZZER_UseOneCompareMode)
   #if (BUZZER_CompareMode1SW)
       void    BUZZER_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (BUZZER_CompareMode1SW) */
#else
    #if (BUZZER_CompareMode1SW)
        void    BUZZER_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (BUZZER_CompareMode1SW) */
    #if (BUZZER_CompareMode2SW)
        void    BUZZER_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (BUZZER_CompareMode2SW) */
#endif /* (BUZZER_UseOneCompareMode) */

#if (!BUZZER_UsingFixedFunction)
    uint16   BUZZER_ReadCounter(void) ;
    uint16 BUZZER_ReadCapture(void) ;

    #if (BUZZER_UseStatus)
            void BUZZER_ClearFIFO(void) ;
    #endif /* (BUZZER_UseStatus) */

    void    BUZZER_WriteCounter(uint16 counter)
            ;
#endif /* (!BUZZER_UsingFixedFunction) */

void    BUZZER_WritePeriod(uint16 period)
        ;
uint16 BUZZER_ReadPeriod(void) ;

#if (BUZZER_UseOneCompareMode)
    void    BUZZER_WriteCompare(uint16 compare)
            ;
    uint16 BUZZER_ReadCompare(void) ;
#else
    void    BUZZER_WriteCompare1(uint16 compare)
            ;
    uint16 BUZZER_ReadCompare1(void) ;
    void    BUZZER_WriteCompare2(uint16 compare)
            ;
    uint16 BUZZER_ReadCompare2(void) ;
#endif /* (BUZZER_UseOneCompareMode) */


#if (BUZZER_DeadBandUsed)
    void    BUZZER_WriteDeadTime(uint8 deadtime) ;
    uint8   BUZZER_ReadDeadTime(void) ;
#endif /* (BUZZER_DeadBandUsed) */

#if ( BUZZER_KillModeMinTime)
    void BUZZER_WriteKillTime(uint8 killtime) ;
    uint8 BUZZER_ReadKillTime(void) ;
#endif /* ( BUZZER_KillModeMinTime) */

void BUZZER_Init(void) ;
void BUZZER_Enable(void) ;
void BUZZER_Sleep(void) ;
void BUZZER_Wakeup(void) ;
void BUZZER_SaveConfig(void) ;
void BUZZER_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define BUZZER_INIT_PERIOD_VALUE          (1000u)
#define BUZZER_INIT_COMPARE_VALUE1        (127u)
#define BUZZER_INIT_COMPARE_VALUE2        (63u)
#define BUZZER_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    BUZZER_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BUZZER_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BUZZER_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BUZZER_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define BUZZER_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  BUZZER_CTRL_CMPMODE2_SHIFT)
#define BUZZER_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  BUZZER_CTRL_CMPMODE1_SHIFT)
#define BUZZER_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (BUZZER_UsingFixedFunction)
   #define BUZZER_PERIOD_LSB              (*(reg16 *) BUZZER_PWMHW__PER0)
   #define BUZZER_PERIOD_LSB_PTR          ( (reg16 *) BUZZER_PWMHW__PER0)
   #define BUZZER_COMPARE1_LSB            (*(reg16 *) BUZZER_PWMHW__CNT_CMP0)
   #define BUZZER_COMPARE1_LSB_PTR        ( (reg16 *) BUZZER_PWMHW__CNT_CMP0)
   #define BUZZER_COMPARE2_LSB            (0x00u)
   #define BUZZER_COMPARE2_LSB_PTR        (0x00u)
   #define BUZZER_COUNTER_LSB             (*(reg16 *) BUZZER_PWMHW__CNT_CMP0)
   #define BUZZER_COUNTER_LSB_PTR         ( (reg16 *) BUZZER_PWMHW__CNT_CMP0)
   #define BUZZER_CAPTURE_LSB             (*(reg16 *) BUZZER_PWMHW__CAP0)
   #define BUZZER_CAPTURE_LSB_PTR         ( (reg16 *) BUZZER_PWMHW__CAP0)
   #define BUZZER_RT1                     (*(reg8 *)  BUZZER_PWMHW__RT1)
   #define BUZZER_RT1_PTR                 ( (reg8 *)  BUZZER_PWMHW__RT1)

#else
   #if (BUZZER_Resolution == 8u) /* 8bit - PWM */

       #if(BUZZER_PWMModeIsCenterAligned)
           #define BUZZER_PERIOD_LSB      (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define BUZZER_PERIOD_LSB_PTR  ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define BUZZER_PERIOD_LSB      (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define BUZZER_PERIOD_LSB_PTR  ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (BUZZER_PWMModeIsCenterAligned) */

       #define BUZZER_COMPARE1_LSB        (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define BUZZER_COMPARE1_LSB_PTR    ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define BUZZER_COMPARE2_LSB        (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define BUZZER_COMPARE2_LSB_PTR    ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define BUZZER_COUNTERCAP_LSB      (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define BUZZER_COUNTERCAP_LSB_PTR  ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define BUZZER_COUNTER_LSB         (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define BUZZER_COUNTER_LSB_PTR     ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define BUZZER_CAPTURE_LSB         (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define BUZZER_CAPTURE_LSB_PTR     ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(BUZZER_PWMModeIsCenterAligned)
               #define BUZZER_PERIOD_LSB      (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define BUZZER_PERIOD_LSB_PTR  ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define BUZZER_PERIOD_LSB      (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define BUZZER_PERIOD_LSB_PTR  ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (BUZZER_PWMModeIsCenterAligned) */

            #define BUZZER_COMPARE1_LSB       (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define BUZZER_COMPARE1_LSB_PTR   ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define BUZZER_COMPARE2_LSB       (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define BUZZER_COMPARE2_LSB_PTR   ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define BUZZER_COUNTERCAP_LSB     (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define BUZZER_COUNTERCAP_LSB_PTR ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define BUZZER_COUNTER_LSB        (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define BUZZER_COUNTER_LSB_PTR    ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define BUZZER_CAPTURE_LSB        (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define BUZZER_CAPTURE_LSB_PTR    ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(BUZZER_PWMModeIsCenterAligned)
               #define BUZZER_PERIOD_LSB      (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define BUZZER_PERIOD_LSB_PTR  ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define BUZZER_PERIOD_LSB      (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define BUZZER_PERIOD_LSB_PTR  ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (BUZZER_PWMModeIsCenterAligned) */

            #define BUZZER_COMPARE1_LSB       (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define BUZZER_COMPARE1_LSB_PTR   ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define BUZZER_COMPARE2_LSB       (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define BUZZER_COMPARE2_LSB_PTR   ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define BUZZER_COUNTERCAP_LSB     (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define BUZZER_COUNTERCAP_LSB_PTR ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define BUZZER_COUNTER_LSB        (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define BUZZER_COUNTER_LSB_PTR    ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define BUZZER_CAPTURE_LSB        (*(reg16 *) BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define BUZZER_CAPTURE_LSB_PTR    ((reg16 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define BUZZER_AUX_CONTROLDP1          (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define BUZZER_AUX_CONTROLDP1_PTR      ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (BUZZER_Resolution == 8) */

   #define BUZZER_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define BUZZER_AUX_CONTROLDP0          (*(reg8 *)  BUZZER_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define BUZZER_AUX_CONTROLDP0_PTR      ((reg8 *)   BUZZER_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (BUZZER_UsingFixedFunction) */

#if(BUZZER_KillModeMinTime )
    #define BUZZER_KILLMODEMINTIME        (*(reg8 *)  BUZZER_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define BUZZER_KILLMODEMINTIME_PTR    ((reg8 *)   BUZZER_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (BUZZER_KillModeMinTime ) */

#if(BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_256_CLOCKS)
    #define BUZZER_DEADBAND_COUNT         (*(reg8 *)  BUZZER_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BUZZER_DEADBAND_COUNT_PTR     ((reg8 *)   BUZZER_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BUZZER_DEADBAND_LSB_PTR       ((reg8 *)   BUZZER_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define BUZZER_DEADBAND_LSB           (*(reg8 *)  BUZZER_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (BUZZER_UsingFixedFunction)
        #define BUZZER_DEADBAND_COUNT         (*(reg8 *)  BUZZER_PWMHW__CFG0)
        #define BUZZER_DEADBAND_COUNT_PTR     ((reg8 *)   BUZZER_PWMHW__CFG0)
        #define BUZZER_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BUZZER_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define BUZZER_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define BUZZER_DEADBAND_COUNT         (*(reg8 *)  BUZZER_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BUZZER_DEADBAND_COUNT_PTR     ((reg8 *)   BUZZER_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BUZZER_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BUZZER_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define BUZZER_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (BUZZER_UsingFixedFunction) */
#endif /* (BUZZER_DeadBandMode == BUZZER__B_PWM__DBM_256_CLOCKS) */



#if (BUZZER_UsingFixedFunction)
    #define BUZZER_STATUS                 (*(reg8 *) BUZZER_PWMHW__SR0)
    #define BUZZER_STATUS_PTR             ((reg8 *) BUZZER_PWMHW__SR0)
    #define BUZZER_STATUS_MASK            (*(reg8 *) BUZZER_PWMHW__SR0)
    #define BUZZER_STATUS_MASK_PTR        ((reg8 *) BUZZER_PWMHW__SR0)
    #define BUZZER_CONTROL                (*(reg8 *) BUZZER_PWMHW__CFG0)
    #define BUZZER_CONTROL_PTR            ((reg8 *) BUZZER_PWMHW__CFG0)
    #define BUZZER_CONTROL2               (*(reg8 *) BUZZER_PWMHW__CFG1)
    #define BUZZER_CONTROL3               (*(reg8 *) BUZZER_PWMHW__CFG2)
    #define BUZZER_GLOBAL_ENABLE          (*(reg8 *) BUZZER_PWMHW__PM_ACT_CFG)
    #define BUZZER_GLOBAL_ENABLE_PTR      ( (reg8 *) BUZZER_PWMHW__PM_ACT_CFG)
    #define BUZZER_GLOBAL_STBY_ENABLE     (*(reg8 *) BUZZER_PWMHW__PM_STBY_CFG)
    #define BUZZER_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) BUZZER_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define BUZZER_BLOCK_EN_MASK          (BUZZER_PWMHW__PM_ACT_MSK)
    #define BUZZER_BLOCK_STBY_EN_MASK     (BUZZER_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define BUZZER_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define BUZZER_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define BUZZER_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define BUZZER_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define BUZZER_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define BUZZER_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define BUZZER_CTRL_ENABLE            (uint8)((uint8)0x01u << BUZZER_CTRL_ENABLE_SHIFT)
    #define BUZZER_CTRL_RESET             (uint8)((uint8)0x01u << BUZZER_CTRL_RESET_SHIFT)
    #define BUZZER_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BUZZER_CTRL_CMPMODE2_SHIFT)
    #define BUZZER_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BUZZER_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BUZZER_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define BUZZER_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << BUZZER_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define BUZZER_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define BUZZER_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define BUZZER_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define BUZZER_STATUS_TC_INT_EN_MASK_SHIFT            (BUZZER_STATUS_TC_SHIFT - 4u)
    #define BUZZER_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define BUZZER_STATUS_CMP1_INT_EN_MASK_SHIFT          (BUZZER_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define BUZZER_STATUS_TC              (uint8)((uint8)0x01u << BUZZER_STATUS_TC_SHIFT)
    #define BUZZER_STATUS_CMP1            (uint8)((uint8)0x01u << BUZZER_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define BUZZER_STATUS_TC_INT_EN_MASK              (uint8)((uint8)BUZZER_STATUS_TC >> 4u)
    #define BUZZER_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)BUZZER_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define BUZZER_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define BUZZER_RT1_MASK              (uint8)((uint8)0x03u << BUZZER_RT1_SHIFT)
    #define BUZZER_SYNC                  (uint8)((uint8)0x03u << BUZZER_RT1_SHIFT)
    #define BUZZER_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define BUZZER_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << BUZZER_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define BUZZER_SYNCDSI_EN            (uint8)((uint8)0x0Fu << BUZZER_SYNCDSI_SHIFT)


#else
    #define BUZZER_STATUS                (*(reg8 *)   BUZZER_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BUZZER_STATUS_PTR            ((reg8 *)    BUZZER_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BUZZER_STATUS_MASK           (*(reg8 *)   BUZZER_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BUZZER_STATUS_MASK_PTR       ((reg8 *)    BUZZER_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BUZZER_STATUS_AUX_CTRL       (*(reg8 *)   BUZZER_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define BUZZER_CONTROL               (*(reg8 *)   BUZZER_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define BUZZER_CONTROL_PTR           ((reg8 *)    BUZZER_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define BUZZER_CTRL_ENABLE_SHIFT      (0x07u)
    #define BUZZER_CTRL_RESET_SHIFT       (0x06u)
    #define BUZZER_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define BUZZER_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define BUZZER_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define BUZZER_CTRL_ENABLE            (uint8)((uint8)0x01u << BUZZER_CTRL_ENABLE_SHIFT)
    #define BUZZER_CTRL_RESET             (uint8)((uint8)0x01u << BUZZER_CTRL_RESET_SHIFT)
    #define BUZZER_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BUZZER_CTRL_CMPMODE2_SHIFT)
    #define BUZZER_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BUZZER_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define BUZZER_STATUS_KILL_SHIFT          (0x05u)
    #define BUZZER_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define BUZZER_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define BUZZER_STATUS_TC_SHIFT            (0x02u)
    #define BUZZER_STATUS_CMP2_SHIFT          (0x01u)
    #define BUZZER_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define BUZZER_STATUS_KILL_INT_EN_MASK_SHIFT          (BUZZER_STATUS_KILL_SHIFT)
    #define BUZZER_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (BUZZER_STATUS_FIFONEMPTY_SHIFT)
    #define BUZZER_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (BUZZER_STATUS_FIFOFULL_SHIFT)
    #define BUZZER_STATUS_TC_INT_EN_MASK_SHIFT            (BUZZER_STATUS_TC_SHIFT)
    #define BUZZER_STATUS_CMP2_INT_EN_MASK_SHIFT          (BUZZER_STATUS_CMP2_SHIFT)
    #define BUZZER_STATUS_CMP1_INT_EN_MASK_SHIFT          (BUZZER_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define BUZZER_STATUS_KILL            (uint8)((uint8)0x00u << BUZZER_STATUS_KILL_SHIFT )
    #define BUZZER_STATUS_FIFOFULL        (uint8)((uint8)0x01u << BUZZER_STATUS_FIFOFULL_SHIFT)
    #define BUZZER_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << BUZZER_STATUS_FIFONEMPTY_SHIFT)
    #define BUZZER_STATUS_TC              (uint8)((uint8)0x01u << BUZZER_STATUS_TC_SHIFT)
    #define BUZZER_STATUS_CMP2            (uint8)((uint8)0x01u << BUZZER_STATUS_CMP2_SHIFT)
    #define BUZZER_STATUS_CMP1            (uint8)((uint8)0x01u << BUZZER_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define BUZZER_STATUS_KILL_INT_EN_MASK            (BUZZER_STATUS_KILL)
    #define BUZZER_STATUS_FIFOFULL_INT_EN_MASK        (BUZZER_STATUS_FIFOFULL)
    #define BUZZER_STATUS_FIFONEMPTY_INT_EN_MASK      (BUZZER_STATUS_FIFONEMPTY)
    #define BUZZER_STATUS_TC_INT_EN_MASK              (BUZZER_STATUS_TC)
    #define BUZZER_STATUS_CMP2_INT_EN_MASK            (BUZZER_STATUS_CMP2)
    #define BUZZER_STATUS_CMP1_INT_EN_MASK            (BUZZER_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define BUZZER_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define BUZZER_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define BUZZER_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define BUZZER_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define BUZZER_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* BUZZER_UsingFixedFunction */

#endif  /* CY_PWM_BUZZER_H */


/* [] END OF FILE */
