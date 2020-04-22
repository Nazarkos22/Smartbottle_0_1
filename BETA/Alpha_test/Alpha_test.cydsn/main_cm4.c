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
    Timer_Int_Init();
   __enable_irq(); /* Enable global interrupts. */

     CapSense_Start();//Initialisation of CSD components
    Flash_Scan();

    InitBle();
    InitLowPower();


//     CapSense_ScanAllWidgets(); /* Start  scan */
    Set_Flags();
 /* Start  scan */
    for(;;)
    {
        CapSense_Processing(RAW_SCAN_TIMES);
        ProcessBleEvents();     
    }
}

/* [] END OF FILE */
