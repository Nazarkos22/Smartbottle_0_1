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

int main(void)
{
    /* Enable global interrupts */
    __enable_irq();
    
    /* Start the Controller portion of BLE. Host runs on the CM4 */
    if(Cy_BLE_Start(NULL) == CY_BLE_SUCCESS)
    {
        /* Enable CM4 only if BLE Controller started successfully. 
           CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout 
           is changed. */
        Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR); 
    }
    else
    {
        /* Halt the CPU if the BLE initialization failed */
        CY_ASSERT(0u != 0u);
    }
    
    for (;;)
    {
        /* Cy_Ble_ProcessEvents() allows the BLE stack to process pending events */
        Cy_BLE_ProcessEvents();
        
        /* Put CM0p to Deep-Sleep mode. The BLE Controller automatically wakes up 
           the CPU if processing is required */
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
