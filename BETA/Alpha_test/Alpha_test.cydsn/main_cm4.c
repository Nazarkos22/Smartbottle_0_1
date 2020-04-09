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
    InitBle();
    InitLowPower();

     Flash_Processing();//
     CapSense_ScanAllWidgets(); /* Start  scan */

 /* Start  scan */
    for(;;)
    {
        CapSense_Processing();
        ProcessBleEvents();     
    }
}

/* [] END OF FILE */
