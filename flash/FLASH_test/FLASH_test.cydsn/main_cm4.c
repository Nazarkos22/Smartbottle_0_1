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


  CapSense_Start();
  CapSense_ScanAllWidgets();   
        

        
    for(;;)
    {
      CSD_Config();
      FLASH_Config();

    }
}

/* [] END OF FILE */
