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

#define SECONDS(i)  (CyDelay(i * 1000)) 

 /*int main(void)
{
    CyGlobalIntEnable; 

  
    PWM_MOTOR_SPEED_Start();

    for(;;)
    {
        PWM_MOTOR_SPEED_WriteCompare(1000);
        SECONDS(2);
        PWM_MOTOR_SPEED_WriteCompare(500);
        SECONDS(2);
        PWM_MOTOR_SPEED_WriteCompare(200);
        SECONDS(2);
        PWM_MOTOR_SPEED_WriteCompare(0);
        SECONDS(2);    
    }
}  */


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
int main(void)
{
    CyGlobalIntEnable; 

  
    PWM_MOTOR_SPEED_Start();

    Pump();
    Wash(2,6);
    Spin();
    Pump();
    Wash(1,3);
    Spin();
    Notify(); 
} 




/* [] END OF FILE */
