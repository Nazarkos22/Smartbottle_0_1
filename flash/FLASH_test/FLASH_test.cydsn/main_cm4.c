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
#include <stdlib.h>
#include <string.h>
#include "flash_config_u.h"
#include "Config_u.h"


int main(void)
{
    U_cfg_t* Flash_data = (U_cfg_t*) CY_EM_EEPROM_BASE;
     uint8 lenth=0x40;
    uint32_t Data[CY_FLASH_SIZEOF_ROW] = {ZERO};
    const uint32_t* Flash = (uint32_t *)CY_EM_EEPROM_BASE;
    bool mem;
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CapSense_Start();
         mem =  is_memory_empty(FLASH_ADDR);
            //void eraze_flash_data(uint32_t Data);
        if(mem == true)
        {
           TIM = make_data_for_flash( Data,  lenth );
            write_flash_data_u( FLASH_ADDR, TIM);
           // TIM = free_data( Data);
        }
    for(;;)
    {

        
            /* Process all widgets */
            
           
            /* To sync with Tuner application */
            
            
            /* Start next scan */
            
        
 /* Place your application code here. */
    }
}

/* [] END OF FILE */
