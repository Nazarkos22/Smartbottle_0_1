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
    
    /* Initialization of timer inetrrupts*/
    Timers_Interrupts_Init();
    /* Enable global interrupts. */
    __enable_irq(); 
    /* Initialization of CSD components */
     CapSense_Start();
    /* Read or form Baseline */
    Flash_Scan();
    /* Initialization of BLE components */
    InitBle();
    /* Initialization of low power components */
    InitLowPower();
    /* Set flags for start first CSD RAW scan */
    Set_Flags();

    for(;;)
    {
        CapSense_Processing(RAW_SCAN_TIMES);
        ProcessBleEvents();
        Switch_Statement();
    }
}

/* [] END OF FILE */
