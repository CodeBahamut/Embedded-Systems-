/*******************************************************************************
* File Name: Led_Slow_Blink.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Led_Slow_Blink_H) /* Pins Led_Slow_Blink_H */
#define CY_PINS_Led_Slow_Blink_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Led_Slow_Blink_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Led_Slow_Blink__PORT == 15 && ((Led_Slow_Blink__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Led_Slow_Blink_Write(uint8 value);
void    Led_Slow_Blink_SetDriveMode(uint8 mode);
uint8   Led_Slow_Blink_ReadDataReg(void);
uint8   Led_Slow_Blink_Read(void);
void    Led_Slow_Blink_SetInterruptMode(uint16 position, uint16 mode);
uint8   Led_Slow_Blink_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Led_Slow_Blink_SetDriveMode() function.
     *  @{
     */
        #define Led_Slow_Blink_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Led_Slow_Blink_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Led_Slow_Blink_DM_RES_UP          PIN_DM_RES_UP
        #define Led_Slow_Blink_DM_RES_DWN         PIN_DM_RES_DWN
        #define Led_Slow_Blink_DM_OD_LO           PIN_DM_OD_LO
        #define Led_Slow_Blink_DM_OD_HI           PIN_DM_OD_HI
        #define Led_Slow_Blink_DM_STRONG          PIN_DM_STRONG
        #define Led_Slow_Blink_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Led_Slow_Blink_MASK               Led_Slow_Blink__MASK
#define Led_Slow_Blink_SHIFT              Led_Slow_Blink__SHIFT
#define Led_Slow_Blink_WIDTH              1u

/* Interrupt constants */
#if defined(Led_Slow_Blink__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Led_Slow_Blink_SetInterruptMode() function.
     *  @{
     */
        #define Led_Slow_Blink_INTR_NONE      (uint16)(0x0000u)
        #define Led_Slow_Blink_INTR_RISING    (uint16)(0x0001u)
        #define Led_Slow_Blink_INTR_FALLING   (uint16)(0x0002u)
        #define Led_Slow_Blink_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Led_Slow_Blink_INTR_MASK      (0x01u) 
#endif /* (Led_Slow_Blink__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Led_Slow_Blink_PS                     (* (reg8 *) Led_Slow_Blink__PS)
/* Data Register */
#define Led_Slow_Blink_DR                     (* (reg8 *) Led_Slow_Blink__DR)
/* Port Number */
#define Led_Slow_Blink_PRT_NUM                (* (reg8 *) Led_Slow_Blink__PRT) 
/* Connect to Analog Globals */                                                  
#define Led_Slow_Blink_AG                     (* (reg8 *) Led_Slow_Blink__AG)                       
/* Analog MUX bux enable */
#define Led_Slow_Blink_AMUX                   (* (reg8 *) Led_Slow_Blink__AMUX) 
/* Bidirectional Enable */                                                        
#define Led_Slow_Blink_BIE                    (* (reg8 *) Led_Slow_Blink__BIE)
/* Bit-mask for Aliased Register Access */
#define Led_Slow_Blink_BIT_MASK               (* (reg8 *) Led_Slow_Blink__BIT_MASK)
/* Bypass Enable */
#define Led_Slow_Blink_BYP                    (* (reg8 *) Led_Slow_Blink__BYP)
/* Port wide control signals */                                                   
#define Led_Slow_Blink_CTL                    (* (reg8 *) Led_Slow_Blink__CTL)
/* Drive Modes */
#define Led_Slow_Blink_DM0                    (* (reg8 *) Led_Slow_Blink__DM0) 
#define Led_Slow_Blink_DM1                    (* (reg8 *) Led_Slow_Blink__DM1)
#define Led_Slow_Blink_DM2                    (* (reg8 *) Led_Slow_Blink__DM2) 
/* Input Buffer Disable Override */
#define Led_Slow_Blink_INP_DIS                (* (reg8 *) Led_Slow_Blink__INP_DIS)
/* LCD Common or Segment Drive */
#define Led_Slow_Blink_LCD_COM_SEG            (* (reg8 *) Led_Slow_Blink__LCD_COM_SEG)
/* Enable Segment LCD */
#define Led_Slow_Blink_LCD_EN                 (* (reg8 *) Led_Slow_Blink__LCD_EN)
/* Slew Rate Control */
#define Led_Slow_Blink_SLW                    (* (reg8 *) Led_Slow_Blink__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Led_Slow_Blink_PRTDSI__CAPS_SEL       (* (reg8 *) Led_Slow_Blink__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Led_Slow_Blink_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Led_Slow_Blink__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Led_Slow_Blink_PRTDSI__OE_SEL0        (* (reg8 *) Led_Slow_Blink__PRTDSI__OE_SEL0) 
#define Led_Slow_Blink_PRTDSI__OE_SEL1        (* (reg8 *) Led_Slow_Blink__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Led_Slow_Blink_PRTDSI__OUT_SEL0       (* (reg8 *) Led_Slow_Blink__PRTDSI__OUT_SEL0) 
#define Led_Slow_Blink_PRTDSI__OUT_SEL1       (* (reg8 *) Led_Slow_Blink__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Led_Slow_Blink_PRTDSI__SYNC_OUT       (* (reg8 *) Led_Slow_Blink__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Led_Slow_Blink__SIO_CFG)
    #define Led_Slow_Blink_SIO_HYST_EN        (* (reg8 *) Led_Slow_Blink__SIO_HYST_EN)
    #define Led_Slow_Blink_SIO_REG_HIFREQ     (* (reg8 *) Led_Slow_Blink__SIO_REG_HIFREQ)
    #define Led_Slow_Blink_SIO_CFG            (* (reg8 *) Led_Slow_Blink__SIO_CFG)
    #define Led_Slow_Blink_SIO_DIFF           (* (reg8 *) Led_Slow_Blink__SIO_DIFF)
#endif /* (Led_Slow_Blink__SIO_CFG) */

/* Interrupt Registers */
#if defined(Led_Slow_Blink__INTSTAT)
    #define Led_Slow_Blink_INTSTAT            (* (reg8 *) Led_Slow_Blink__INTSTAT)
    #define Led_Slow_Blink_SNAP               (* (reg8 *) Led_Slow_Blink__SNAP)
    
	#define Led_Slow_Blink_0_INTTYPE_REG 		(* (reg8 *) Led_Slow_Blink__0__INTTYPE)
#endif /* (Led_Slow_Blink__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Led_Slow_Blink_H */


/* [] END OF FILE */
