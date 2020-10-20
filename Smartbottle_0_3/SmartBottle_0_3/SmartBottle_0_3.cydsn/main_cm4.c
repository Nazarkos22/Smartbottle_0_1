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
#include "project.h"
#include "Config_u.h"
#include "Core.h"
#include "CSD_APP.h"
#include "Flash_APP.h"
#include "led.h"
#include "ble_application.h"
#include "timers_counters.h"
#include "low_power.h"


int main(void)
{
    /* Timers` elements initialization */
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

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        Timer_Handler();
        ProcessBleEvents();
        Switch_Statement();
        Timer_Handler();
    }
}

/* [] END OF FILE */