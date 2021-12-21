/*******************************************************************************
* File Name: DIRECTION.h  
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

#if !defined(CY_PINS_DIRECTION_H) /* Pins DIRECTION_H */
#define CY_PINS_DIRECTION_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIRECTION_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIRECTION__PORT == 15 && ((DIRECTION__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIRECTION_Write(uint8 value);
void    DIRECTION_SetDriveMode(uint8 mode);
uint8   DIRECTION_ReadDataReg(void);
uint8   DIRECTION_Read(void);
void    DIRECTION_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIRECTION_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIRECTION_SetDriveMode() function.
     *  @{
     */
        #define DIRECTION_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIRECTION_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIRECTION_DM_RES_UP          PIN_DM_RES_UP
        #define DIRECTION_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIRECTION_DM_OD_LO           PIN_DM_OD_LO
        #define DIRECTION_DM_OD_HI           PIN_DM_OD_HI
        #define DIRECTION_DM_STRONG          PIN_DM_STRONG
        #define DIRECTION_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIRECTION_MASK               DIRECTION__MASK
#define DIRECTION_SHIFT              DIRECTION__SHIFT
#define DIRECTION_WIDTH              1u

/* Interrupt constants */
#if defined(DIRECTION__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIRECTION_SetInterruptMode() function.
     *  @{
     */
        #define DIRECTION_INTR_NONE      (uint16)(0x0000u)
        #define DIRECTION_INTR_RISING    (uint16)(0x0001u)
        #define DIRECTION_INTR_FALLING   (uint16)(0x0002u)
        #define DIRECTION_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIRECTION_INTR_MASK      (0x01u) 
#endif /* (DIRECTION__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIRECTION_PS                     (* (reg8 *) DIRECTION__PS)
/* Data Register */
#define DIRECTION_DR                     (* (reg8 *) DIRECTION__DR)
/* Port Number */
#define DIRECTION_PRT_NUM                (* (reg8 *) DIRECTION__PRT) 
/* Connect to Analog Globals */                                                  
#define DIRECTION_AG                     (* (reg8 *) DIRECTION__AG)                       
/* Analog MUX bux enable */
#define DIRECTION_AMUX                   (* (reg8 *) DIRECTION__AMUX) 
/* Bidirectional Enable */                                                        
#define DIRECTION_BIE                    (* (reg8 *) DIRECTION__BIE)
/* Bit-mask for Aliased Register Access */
#define DIRECTION_BIT_MASK               (* (reg8 *) DIRECTION__BIT_MASK)
/* Bypass Enable */
#define DIRECTION_BYP                    (* (reg8 *) DIRECTION__BYP)
/* Port wide control signals */                                                   
#define DIRECTION_CTL                    (* (reg8 *) DIRECTION__CTL)
/* Drive Modes */
#define DIRECTION_DM0                    (* (reg8 *) DIRECTION__DM0) 
#define DIRECTION_DM1                    (* (reg8 *) DIRECTION__DM1)
#define DIRECTION_DM2                    (* (reg8 *) DIRECTION__DM2) 
/* Input Buffer Disable Override */
#define DIRECTION_INP_DIS                (* (reg8 *) DIRECTION__INP_DIS)
/* LCD Common or Segment Drive */
#define DIRECTION_LCD_COM_SEG            (* (reg8 *) DIRECTION__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIRECTION_LCD_EN                 (* (reg8 *) DIRECTION__LCD_EN)
/* Slew Rate Control */
#define DIRECTION_SLW                    (* (reg8 *) DIRECTION__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIRECTION_PRTDSI__CAPS_SEL       (* (reg8 *) DIRECTION__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIRECTION_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIRECTION__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIRECTION_PRTDSI__OE_SEL0        (* (reg8 *) DIRECTION__PRTDSI__OE_SEL0) 
#define DIRECTION_PRTDSI__OE_SEL1        (* (reg8 *) DIRECTION__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIRECTION_PRTDSI__OUT_SEL0       (* (reg8 *) DIRECTION__PRTDSI__OUT_SEL0) 
#define DIRECTION_PRTDSI__OUT_SEL1       (* (reg8 *) DIRECTION__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIRECTION_PRTDSI__SYNC_OUT       (* (reg8 *) DIRECTION__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIRECTION__SIO_CFG)
    #define DIRECTION_SIO_HYST_EN        (* (reg8 *) DIRECTION__SIO_HYST_EN)
    #define DIRECTION_SIO_REG_HIFREQ     (* (reg8 *) DIRECTION__SIO_REG_HIFREQ)
    #define DIRECTION_SIO_CFG            (* (reg8 *) DIRECTION__SIO_CFG)
    #define DIRECTION_SIO_DIFF           (* (reg8 *) DIRECTION__SIO_DIFF)
#endif /* (DIRECTION__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIRECTION__INTSTAT)
    #define DIRECTION_INTSTAT            (* (reg8 *) DIRECTION__INTSTAT)
    #define DIRECTION_SNAP               (* (reg8 *) DIRECTION__SNAP)
    
	#define DIRECTION_0_INTTYPE_REG 		(* (reg8 *) DIRECTION__0__INTTYPE)
#endif /* (DIRECTION__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIRECTION_H */


/* [] END OF FILE */
