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
#include "APP.h"


int main(void)
{
   __enable_irq(); /* Enable global interrupts. */

   Read_Flash();

  CapSense_Start();
 
    for(;;)
    {

    }
}

/* [] END OF FILE */
