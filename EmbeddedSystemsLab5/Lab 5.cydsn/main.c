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
/*#include "project.h"

int main(void)
{
    CyGlobalIntEnable; 

    
    UART_RX_Start();
    UART_TX_Start();
    
    char buffer;
    
    for(;;)
    {
       buffer = UART_TX_GetChar();
       UART_RX_PutChar(buffer);
    }
}*/
   
#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <u8x8.h>

#define SECONDS(i)  (CyDelay(i * 1000)) 
#define PWM_FREQ 100
#define NO_OF_MSEC 1000

uint8_t psoc_gpio_and_delay_callback(u8x8_t *u8x8, uint8_t msg,
uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg,
uint8_t arg_int, void *arg_ptr);
uint8 compare_occured = 0;

CY_ISR(PWM_TACHO_InterruptHandler){
    PWM_TACHO_ReadStatusRegister();
    compare_occured = 1;
}



void Pump(){
    DIRECTION_Write(0);
    PWM_MOTOR_SPEED_WriteCompare(8000);
    SECONDS(4);
    PWM_MOTOR_SPEED_WriteCompare(0);
    SECONDS(1);
}

void Wash(int rotateTime, int repetitions){
    
    for(int i = 0; i < repetitions; i++){
        DIRECTION_Write(0);
        PWM_MOTOR_SPEED_WriteCompare(200);
        SECONDS(rotateTime);
        PWM_MOTOR_SPEED_WriteCompare(0);
        SECONDS(1);
        DIRECTION_Write(1);
        PWM_MOTOR_SPEED_WriteCompare(200);
        SECONDS(rotateTime);
        PWM_MOTOR_SPEED_WriteCompare(0);
        SECONDS(1);
    }
}

void Spin(){
    DIRECTION_Write(0);
    PWM_MOTOR_SPEED_WriteCompare(200);
    SECONDS(3);
    PWM_MOTOR_SPEED_WriteCompare(0);
    SECONDS(1);
    PWM_MOTOR_SPEED_WriteCompare(500);
    SECONDS(3);
    PWM_MOTOR_SPEED_WriteCompare(0);
    SECONDS(1);
    DIRECTION_Write(1);
    PWM_MOTOR_SPEED_WriteCompare(1000);
    SECONDS(3);
    PWM_MOTOR_SPEED_WriteCompare(0);
    SECONDS(1);
}

void Notify(){
    PWM_MOTOR_SPEED_Stop();
    BUZZER_Start();
    BUZZER_WriteCompare(999);
    SECONDS(10);
    BUZZER_Stop();
}


int main(void) {
static uint16 pwm_window_period = 0;
static uint32 tacho_count = 0;    
volatile uint32 input_freq = 0;    
volatile uint32 rpm = 0;    
char buffer [32];
char freq [32];
    
IRQ_TACHO_StartEx(PWM_TACHO_InterruptHandler);
PWM_TACHO_Start();    
PWM_MOTOR_SPEED_Start();
Counter_TACHO_Start(); 
UART_Start();
PWM_MOTOR_SPEED_WriteCompare(50);

pwm_window_period = 0;
pwm_window_period = PWM_TACHO_ReadPeriod() / PWM_FREQ;

u8x8_t EM2Display;
CyGlobalIntEnable;
I2C_DISPLAY_Start();
u8x8_Setup(&EM2Display, u8x8_d_ssd1306_128x64_noname, u8x8_cad_ssd13xx_i2c,
u8x8_byte_hw_i2c, psoc_gpio_and_delay_callback);
u8x8_InitDisplay(&EM2Display);
u8x8_SetPowerSave(&EM2Display, 0);
u8x8_ClearDisplay(&EM2Display);
u8x8_SetFont(&EM2Display, u8x8_font_amstrad_cpc_extended_f);
//u8x8_DrawString(&EM2Display, 1, 1, "HvA HBO-ICT");
//u8x8_DrawString(&EM2Display, 1, 3, "TI EM2");
//u8x8_DrawString(&EM2Display, 1, 5, "Ready to run." );
//u8x8_DrawString(&EM2Display, 1, 1, "Washing Machine");
//u8x8_DrawString(&EM2Display, 1, 4, "      ON");


for(;;) {
    
    
    
    
    if (compare_occured == 1) {
        tacho_count = Counter_TACHO_ReadCapture();
        input_freq = ((tacho_count *NO_OF_MSEC) / pwm_window_period);
        rpm = (60 * input_freq);
        itoa(rpm,buffer,10);
        itoa(input_freq,freq,10);
        UART_PutString(buffer);
        u8x8_DrawString(&EM2Display, 1, 1, "RPM: ");
        u8x8_DrawString(&EM2Display, 1, 2, buffer);
        u8x8_DrawString(&EM2Display, 1, 3, "input freq ");
        u8x8_DrawString(&EM2Display, 1, 4, freq);
        compare_occured = 0;
        
    }
    
}

/*Pump();
    Wash(2,6);
    Spin();
    Pump();
    Wash(1,3);
    Spin();
    Notify(); */
}

uint8_t psoc_gpio_and_delay_callback(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
(void) u8x8;
(void) arg_ptr;
switch(msg) {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
        break;
    case U8X8_MSG_DELAY_MILLI:
    CyDelay(arg_int);
        break;
    case U8X8_MSG_DELAY_10MICRO:
    CyDelayUs(10);
        break;
    case U8X8_MSG_DELAY_100NANO:
    CyDelayCycles(100);
        break;
    }
    return 1;
}
/*
PSoC I2C Hardware Interface for U8X8
*/
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
uint8_t *data;
switch(msg) {
    case U8X8_MSG_BYTE_SEND:
    data = (uint8_t *)arg_ptr;
    while(arg_int > 0) {
    (void)I2C_DISPLAY_MasterWriteByte(*data);
    data++;
    arg_int--;
    }
        break;
    case U8X8_MSG_BYTE_INIT:
        break;
    case U8X8_MSG_BYTE_SET_DC:
        break;
    case U8X8_MSG_BYTE_START_TRANSFER:
    (void)I2C_DISPLAY_MasterSendStart(u8x8_GetI2CAddress(u8x8) >> 1,
    I2C_DISPLAY_WRITE_XFER_MODE);
        break;
    case U8X8_MSG_BYTE_END_TRANSFER:
    (void)I2C_DISPLAY_MasterSendStop();
        break;
    default:
    return 0;
    }
    return 1;
}


/* [] END OF FILE */
