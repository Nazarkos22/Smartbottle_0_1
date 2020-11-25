/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#include "project.h"
#include "Core.h"
#include "ble_application.h"
#include "led.h"
#include "CapSense_Process.h"
#include "low_power.h"

int main(void)
{
   __enable_irq(); /* Enable global interrupts. */
     CapSense_Start();//Initialisation of CSD components
//     Cy_BLE_Start(); //Initialisation of BLE components
     Flash_Processing();//

 /* Start  scan */
    for(;;)
    {
        CapSense_Processing();
       
    }
}

/* [] END OF FILE */
