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
#include "timer.h"
#include "low_power.h"


int main(void)
{

    /* Enable global interrupts. */
    __enable_irq(); 

    /* Initialization of CSD components */
    CSD_Init();
    CapSense_Start();
    TX_Start();
    
    /* Initialization of BLE components */
    InitBle();
    /* Initialization of low power components */
    InitLowPower();
    /* Timers` elements initialization */
    Init_Global_Timer();
    /* */
    Flash_Init();
    /* Read or form Baseline */
    Flash_Scan();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Use for debug only */
//        csd_SwitchState();
        ProcessBleEvents();
        Switch_Statement();
        
    }
}

/* [] END OF FILE */
