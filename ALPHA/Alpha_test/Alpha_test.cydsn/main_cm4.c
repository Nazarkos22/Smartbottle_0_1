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
//     CapSense_ScanAllWidgets();
     Flash_Processing();//
    
 /* Start  scan */
    for(;;)
    {
              
                       
                      if(CapSense_NOT_BUSY == CapSense_IsBusy()) /* Do this only when a scan is done */
                       {
                         CapSense_ProcessAllWidgets(); /* Process all widgets */
//                        result = make_sensors_data(ptr, len);
//                        if(result == GOOD)
//                        {
//                            uint8 arr;
//                            for(arr = ZERO; arr < len; arr++)
//                            {
//                               Average[arr]+= (ptr[arr]/len); 
//                            }
////                             ret = false;
//                        }
                        CapSense_ScanAllWidgets(); /* Start  scan */   
                        
                       }

    }
}

/* [] END OF FILE */
