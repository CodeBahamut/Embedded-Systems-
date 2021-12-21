/*******************************************************************************
* File Name: BuiltInLed.h  
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

#if !defined(CY_PINS_BuiltInLed_H) /* Pins BuiltInLed_H */
#define CY_PINS_BuiltInLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BuiltInLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BuiltInLed__PORT == 15 && ((BuiltInLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BuiltInLed_Write(uint8 value);
void    BuiltInLed_SetDriveMode(uint8 mode);
uint8   BuiltInLed_ReadDataReg(void);
uint8   BuiltInLed_Read(void);
void    BuiltInLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   BuiltInLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BuiltInLed_SetDriveMode() function.
     *  @{
     */
        #define BuiltInLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BuiltInLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BuiltInLed_DM_RES_UP          PIN_DM_RES_UP
        #define BuiltInLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define BuiltInLed_DM_OD_LO           PIN_DM_OD_LO
        #define BuiltInLed_DM_OD_HI           PIN_DM_OD_HI
        #define BuiltInLed_DM_STRONG          PIN_DM_STRONG
        #define BuiltInLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BuiltInLed_MASK               BuiltInLed__MASK
#define BuiltInLed_SHIFT              BuiltInLed__SHIFT
#define BuiltInLed_WIDTH              1u

/* Interrupt constants */
#if defined(BuiltInLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BuiltInLed_SetInterruptMode() function.
     *  @{
     */
        #define BuiltInLed_INTR_NONE      (uint16)(0x0000u)
        #define BuiltInLed_INTR_RISING    (uint16)(0x0001u)
        #define BuiltInLed_INTR_FALLING   (uint16)(0x0002u)
        #define BuiltInLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BuiltInLed_INTR_MASK      (0x01u) 
#endif /* (BuiltInLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BuiltInLed_PS                     (* (reg8 *) BuiltInLed__PS)
/* Data Register */
#define BuiltInLed_DR                     (* (reg8 *) BuiltInLed__DR)
/* Port Number */
#define BuiltInLed_PRT_NUM                (* (reg8 *) BuiltInLed__PRT) 
/* Connect to Analog Globals */                                                  
#define BuiltInLed_AG                     (* (reg8 *) BuiltInLed__AG)                       
/* Analog MUX bux enable */
#define BuiltInLed_AMUX                   (* (reg8 *) BuiltInLed__AMUX) 
/* Bidirectional Enable */                                                        
#define BuiltInLed_BIE                    (* (reg8 *) BuiltInLed__BIE)
/* Bit-mask for Aliased Register Access */
#define BuiltInLed_BIT_MASK               (* (reg8 *) BuiltInLed__BIT_MASK)
/* Bypass Enable */
#define BuiltInLed_BYP                    (* (reg8 *) BuiltInLed__BYP)
/* Port wide control signals */                                                   
#define BuiltInLed_CTL                    (* (reg8 *) BuiltInLed__CTL)
/* Drive Modes */
#define BuiltInLed_DM0                    (* (reg8 *) BuiltInLed__DM0) 
#define BuiltInLed_DM1                    (* (reg8 *) BuiltInLed__DM1)
#define BuiltInLed_DM2                    (* (reg8 *) BuiltInLed__DM2) 
/* Input Buffer Disable Override */
#define BuiltInLed_INP_DIS                (* (reg8 *) BuiltInLed__INP_DIS)
/* LCD Common or Segment Drive */
#define BuiltInLed_LCD_COM_SEG            (* (reg8 *) BuiltInLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define BuiltInLed_LCD_EN                 (* (reg8 *) BuiltInLed__LCD_EN)
/* Slew Rate Control */
#define BuiltInLed_SLW                    (* (reg8 *) BuiltInLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BuiltInLed_PRTDSI__CAPS_SEL       (* (reg8 *) BuiltInLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BuiltInLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BuiltInLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BuiltInLed_PRTDSI__OE_SEL0        (* (reg8 *) BuiltInLed__PRTDSI__OE_SEL0) 
#define BuiltInLed_PRTDSI__OE_SEL1        (* (reg8 *) BuiltInLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BuiltInLed_PRTDSI__OUT_SEL0       (* (reg8 *) BuiltInLed__PRTDSI__OUT_SEL0) 
#define BuiltInLed_PRTDSI__OUT_SEL1       (* (reg8 *) BuiltInLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BuiltInLed_PRTDSI__SYNC_OUT       (* (reg8 *) BuiltInLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BuiltInLed__SIO_CFG)
    #define BuiltInLed_SIO_HYST_EN        (* (reg8 *) BuiltInLed__SIO_HYST_EN)
    #define BuiltInLed_SIO_REG_HIFREQ     (* (reg8 *) BuiltInLed__SIO_REG_HIFREQ)
    #define BuiltInLed_SIO_CFG            (* (reg8 *) BuiltInLed__SIO_CFG)
    #define BuiltInLed_SIO_DIFF           (* (reg8 *) BuiltInLed__SIO_DIFF)
#endif /* (BuiltInLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(BuiltInLed__INTSTAT)
    #define BuiltInLed_INTSTAT            (* (reg8 *) BuiltInLed__INTSTAT)
    #define BuiltInLed_SNAP               (* (reg8 *) BuiltInLed__SNAP)
    
	#define BuiltInLed_0_INTTYPE_REG 		(* (reg8 *) BuiltInLed__0__INTTYPE)
#endif /* (BuiltInLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BuiltInLed_H */


/* [] END OF FILE */
