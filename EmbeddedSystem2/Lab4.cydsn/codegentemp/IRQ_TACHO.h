/*******************************************************************************
* File Name: IRQ_TACHO.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_IRQ_TACHO_H)
#define CY_ISR_IRQ_TACHO_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void IRQ_TACHO_Start(void);
void IRQ_TACHO_StartEx(cyisraddress address);
void IRQ_TACHO_Stop(void);

CY_ISR_PROTO(IRQ_TACHO_Interrupt);

void IRQ_TACHO_SetVector(cyisraddress address);
cyisraddress IRQ_TACHO_GetVector(void);

void IRQ_TACHO_SetPriority(uint8 priority);
uint8 IRQ_TACHO_GetPriority(void);

void IRQ_TACHO_Enable(void);
uint8 IRQ_TACHO_GetState(void);
void IRQ_TACHO_Disable(void);

void IRQ_TACHO_SetPending(void);
void IRQ_TACHO_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the IRQ_TACHO ISR. */
#define IRQ_TACHO_INTC_VECTOR            ((reg32 *) IRQ_TACHO__INTC_VECT)

/* Address of the IRQ_TACHO ISR priority. */
#define IRQ_TACHO_INTC_PRIOR             ((reg8 *) IRQ_TACHO__INTC_PRIOR_REG)

/* Priority of the IRQ_TACHO interrupt. */
#define IRQ_TACHO_INTC_PRIOR_NUMBER      IRQ_TACHO__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable IRQ_TACHO interrupt. */
#define IRQ_TACHO_INTC_SET_EN            ((reg32 *) IRQ_TACHO__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the IRQ_TACHO interrupt. */
#define IRQ_TACHO_INTC_CLR_EN            ((reg32 *) IRQ_TACHO__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the IRQ_TACHO interrupt state to pending. */
#define IRQ_TACHO_INTC_SET_PD            ((reg32 *) IRQ_TACHO__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the IRQ_TACHO interrupt. */
#define IRQ_TACHO_INTC_CLR_PD            ((reg32 *) IRQ_TACHO__INTC_CLR_PD_REG)


#endif /* CY_ISR_IRQ_TACHO_H */


/* [] END OF FILE */
