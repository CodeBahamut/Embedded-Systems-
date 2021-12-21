/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
/* The clock frequency for the PWM_TACHO.
*
* It must be in KHz. Please update this define if the clock is updated in the
* Top-Design.
*/
#define PWM_FREQ 100
/* Define to represent 1 second in terms of millisecond */
#define NO_OF_MSEC 1000
/* Interrupt occurrence flag */
uint8 compare_occured = 0;
/* Define your Interrupt Service Routine
*
* The ISR has to read the Status Register of the PWM_TACHO to clear the
* interrupt bits and indicate the occurrence of an interrupt.
*
* You can use any of the 3 methods covered before but remember to make it as
* short as possible.
*/
/* TODO: Write your ISR */

CY_ISR(PWM_TACHO_InterruptHandler){
    PWM_TACHO_ReadStatusRegister();
    compare_occured = 1;
}


int main(void) {
/* Variable to store the period of the PWM_TACHO */
static uint16 pwm_window_period = 0;
/* Variable to store the count value after capture */
static uint32 tacho_count = 0;
/* Variable to store the measured frequency */
volatile uint32 input_freq = 0;
/* Variable to store the revolutions per minute */
volatile uint32 rpm = 0;

char buffer [32];

/* Enable global interrupts. */
CyGlobalIntEnable;
/* Place your initialization code here */
/* TODO: Initialize the components */
    
IRQ_TACHO_StartEx(PWM_TACHO_InterruptHandler);
PWM_MOTOR_Start();
PWM_TACHO_Start();
Counter_TACHO_Start();
UART_1_Start();
PWM_MOTOR_WriteCompare(50);


/* Obtain the time window during which the counter will count. Remember to
* update this value according to PWM_FREQ.
*/
/* TODO: Compute pwm_window_period */
pwm_window_period = 0;
pwm_window_period = PWM_TACHO_ReadPeriod() / PWM_FREQ;
for(;;) {
/* Check if the PWM interrupt has occurred
*
* As defined in the settings, the PWM_TACHO raises an interrupt in the
* Compare event. This interrupt occurs every 100 ms. When an interrupt
* occurs, the program performs the frequency computation.
*/
if (compare_occured == 1) {
/* Read the COUNTER_TACHO capture register */
/* TODO: Read the counter */
tacho_count = Counter_TACHO_ReadCapture();
/* Convert the counts to frequency.
*

* The frequency is the number of counts in seconds. In this case,
* the number of counts within one "PWM_TACHO time window" (100 ms),
* hence you need to find it for 1000 milliseconds.
*/
/* TODO: Compute the measured frequency */
input_freq = ((tacho_count *NO_OF_MSEC) / pwm_window_period);

/* Convert the frequency into rpm
*
* Use Equation 1 to compute the revolutions per minute
*/
/* TODO: Compute the rpm */
rpm = (60 * input_freq);

itoa(rpm,buffer,10);
UART_1_PutString(buffer);
UART_1_PutString("  ");
/* Clear the interrupt flag */
/* TODO: Lower the interrupt occurrence flag. */
compare_occured = 0;

}
}
}

/* [] END OF FILE */
