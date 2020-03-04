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
#include "Core.h"


int main(void)
{
   __enable_irq(); /* Enable global interrupts. */
     CapSense_Start();//Initialisation of CSD block and widgets
    Flash_Processing();//
    
    
    for(;;)
    {

    }
}

/* [] END OF FILE */
