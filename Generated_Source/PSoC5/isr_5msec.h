/*******************************************************************************
* File Name: isr_5msec.h
* Version 1.71
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
#if !defined(CY_ISR_isr_5msec_H)
#define CY_ISR_isr_5msec_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_5msec_Start(void);
void isr_5msec_StartEx(cyisraddress address);
void isr_5msec_Stop(void);

CY_ISR_PROTO(isr_5msec_Interrupt);

void isr_5msec_SetVector(cyisraddress address);
cyisraddress isr_5msec_GetVector(void);

void isr_5msec_SetPriority(uint8 priority);
uint8 isr_5msec_GetPriority(void);

void isr_5msec_Enable(void);
uint8 isr_5msec_GetState(void);
void isr_5msec_Disable(void);

void isr_5msec_SetPending(void);
void isr_5msec_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_5msec ISR. */
#define isr_5msec_INTC_VECTOR            ((reg32 *) isr_5msec__INTC_VECT)

/* Address of the isr_5msec ISR priority. */
#define isr_5msec_INTC_PRIOR             ((reg8 *) isr_5msec__INTC_PRIOR_REG)

/* Priority of the isr_5msec interrupt. */
#define isr_5msec_INTC_PRIOR_NUMBER      isr_5msec__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_5msec interrupt. */
#define isr_5msec_INTC_SET_EN            ((reg32 *) isr_5msec__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_5msec interrupt. */
#define isr_5msec_INTC_CLR_EN            ((reg32 *) isr_5msec__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_5msec interrupt state to pending. */
#define isr_5msec_INTC_SET_PD            ((reg32 *) isr_5msec__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_5msec interrupt. */
#define isr_5msec_INTC_CLR_PD            ((reg32 *) isr_5msec__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_5msec_H */


/* [] END OF FILE */
