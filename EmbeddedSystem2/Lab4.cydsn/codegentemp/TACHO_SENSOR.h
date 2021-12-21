/*******************************************************************************
* File Name: TACHO_SENSOR.h  
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

#if !defined(CY_PINS_TACHO_SENSOR_H) /* Pins TACHO_SENSOR_H */
#define CY_PINS_TACHO_SENSOR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TACHO_SENSOR_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TACHO_SENSOR__PORT == 15 && ((TACHO_SENSOR__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TACHO_SENSOR_Write(uint8 value);
void    TACHO_SENSOR_SetDriveMode(uint8 mode);
uint8   TACHO_SENSOR_ReadDataReg(void);
uint8   TACHO_SENSOR_Read(void);
void    TACHO_SENSOR_SetInterruptMode(uint16 position, uint16 mode);
uint8   TACHO_SENSOR_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TACHO_SENSOR_SetDriveMode() function.
     *  @{
     */
        #define TACHO_SENSOR_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TACHO_SENSOR_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TACHO_SENSOR_DM_RES_UP          PIN_DM_RES_UP
        #define TACHO_SENSOR_DM_RES_DWN         PIN_DM_RES_DWN
        #define TACHO_SENSOR_DM_OD_LO           PIN_DM_OD_LO
        #define TACHO_SENSOR_DM_OD_HI           PIN_DM_OD_HI
        #define TACHO_SENSOR_DM_STRONG          PIN_DM_STRONG
        #define TACHO_SENSOR_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TACHO_SENSOR_MASK               TACHO_SENSOR__MASK
#define TACHO_SENSOR_SHIFT              TACHO_SENSOR__SHIFT
#define TACHO_SENSOR_WIDTH              1u

/* Interrupt constants */
#if defined(TACHO_SENSOR__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TACHO_SENSOR_SetInterruptMode() function.
     *  @{
     */
        #define TACHO_SENSOR_INTR_NONE      (uint16)(0x0000u)
        #define TACHO_SENSOR_INTR_RISING    (uint16)(0x0001u)
        #define TACHO_SENSOR_INTR_FALLING   (uint16)(0x0002u)
        #define TACHO_SENSOR_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TACHO_SENSOR_INTR_MASK      (0x01u) 
#endif /* (TACHO_SENSOR__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TACHO_SENSOR_PS                     (* (reg8 *) TACHO_SENSOR__PS)
/* Data Register */
#define TACHO_SENSOR_DR                     (* (reg8 *) TACHO_SENSOR__DR)
/* Port Number */
#define TACHO_SENSOR_PRT_NUM                (* (reg8 *) TACHO_SENSOR__PRT) 
/* Connect to Analog Globals */                                                  
#define TACHO_SENSOR_AG                     (* (reg8 *) TACHO_SENSOR__AG)                       
/* Analog MUX bux enable */
#define TACHO_SENSOR_AMUX                   (* (reg8 *) TACHO_SENSOR__AMUX) 
/* Bidirectional Enable */                                                        
#define TACHO_SENSOR_BIE                    (* (reg8 *) TACHO_SENSOR__BIE)
/* Bit-mask for Aliased Register Access */
#define TACHO_SENSOR_BIT_MASK               (* (reg8 *) TACHO_SENSOR__BIT_MASK)
/* Bypass Enable */
#define TACHO_SENSOR_BYP                    (* (reg8 *) TACHO_SENSOR__BYP)
/* Port wide control signals */                                                   
#define TACHO_SENSOR_CTL                    (* (reg8 *) TACHO_SENSOR__CTL)
/* Drive Modes */
#define TACHO_SENSOR_DM0                    (* (reg8 *) TACHO_SENSOR__DM0) 
#define TACHO_SENSOR_DM1                    (* (reg8 *) TACHO_SENSOR__DM1)
#define TACHO_SENSOR_DM2                    (* (reg8 *) TACHO_SENSOR__DM2) 
/* Input Buffer Disable Override */
#define TACHO_SENSOR_INP_DIS                (* (reg8 *) TACHO_SENSOR__INP_DIS)
/* LCD Common or Segment Drive */
#define TACHO_SENSOR_LCD_COM_SEG            (* (reg8 *) TACHO_SENSOR__LCD_COM_SEG)
/* Enable Segment LCD */
#define TACHO_SENSOR_LCD_EN                 (* (reg8 *) TACHO_SENSOR__LCD_EN)
/* Slew Rate Control */
#define TACHO_SENSOR_SLW                    (* (reg8 *) TACHO_SENSOR__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TACHO_SENSOR_PRTDSI__CAPS_SEL       (* (reg8 *) TACHO_SENSOR__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TACHO_SENSOR_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TACHO_SENSOR__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TACHO_SENSOR_PRTDSI__OE_SEL0        (* (reg8 *) TACHO_SENSOR__PRTDSI__OE_SEL0) 
#define TACHO_SENSOR_PRTDSI__OE_SEL1        (* (reg8 *) TACHO_SENSOR__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TACHO_SENSOR_PRTDSI__OUT_SEL0       (* (reg8 *) TACHO_SENSOR__PRTDSI__OUT_SEL0) 
#define TACHO_SENSOR_PRTDSI__OUT_SEL1       (* (reg8 *) TACHO_SENSOR__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TACHO_SENSOR_PRTDSI__SYNC_OUT       (* (reg8 *) TACHO_SENSOR__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TACHO_SENSOR__SIO_CFG)
    #define TACHO_SENSOR_SIO_HYST_EN        (* (reg8 *) TACHO_SENSOR__SIO_HYST_EN)
    #define TACHO_SENSOR_SIO_REG_HIFREQ     (* (reg8 *) TACHO_SENSOR__SIO_REG_HIFREQ)
    #define TACHO_SENSOR_SIO_CFG            (* (reg8 *) TACHO_SENSOR__SIO_CFG)
    #define TACHO_SENSOR_SIO_DIFF           (* (reg8 *) TACHO_SENSOR__SIO_DIFF)
#endif /* (TACHO_SENSOR__SIO_CFG) */

/* Interrupt Registers */
#if defined(TACHO_SENSOR__INTSTAT)
    #define TACHO_SENSOR_INTSTAT            (* (reg8 *) TACHO_SENSOR__INTSTAT)
    #define TACHO_SENSOR_SNAP               (* (reg8 *) TACHO_SENSOR__SNAP)
    
	#define TACHO_SENSOR_0_INTTYPE_REG 		(* (reg8 *) TACHO_SENSOR__0__INTTYPE)
#endif /* (TACHO_SENSOR__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TACHO_SENSOR_H */


/* [] END OF FILE */
