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



int loop_counter = 0;
int testidkwhatever = 2;
signed int test2 = -1;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    int *p;
    p = &loop_counter;
    
    for(;;)
    {        
        BuiltInLed_Write(1);
        CyDelay(500);
        BuiltInLed_Write(0);
        CyDelay(500);
        
        *p = *p + 1;        
    
        if(Led_Slow_Blink_Read() == 0) {
            uint8 staticBits = ((* (reg8 *) 0x40005120u) & (uint8)(~0x40u));
            (* (reg8 *) 0x40005120u) = staticBits | ((uint8)(1 << 6u) & 0x40u);
        } else {
            uint8 staticBits = ((* (reg8 *) 0x40005120u) & (uint8)(~0x40u));
            (* (reg8 *) 0x40005120u) = staticBits | ((uint8)(0 << 6u) & 0x40u);
        }
        
        
    }
}

/* [] END OF FILE */
