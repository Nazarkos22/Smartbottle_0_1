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

//  uint32_t* make_data_for_flash(uint32_t Data[0x40],uint8 len );
//void eraze_flash_data(void);
int main(void)
{
     const uint32_t* Flash = (uint32_t *)CY_EM_EEPROM_BASE;
 uint32_t Data[CY_FLASH_SIZEOF_ROW] = {ZERO};
 uint8 lenth=0x40;
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CapSense_Start();
            void eraze_flash_data(uint32_t Data);
            uint32_t* make_data_for_flash(uint32_t Data[0x40], uint8 lenth );
            uint32_t* write_flash_data_u(uint32_t Flash, uint32_t* Data);
            uint32_t* free_data(uint32_t Data[0x40]);
//      uint32_t* ptr = (uint32_t*) malloc(0x40);    
//    memset(ptr, ZERO, 0x40);
//    Cy_Flash_WriteRow(FLASH_ADDR, ptr);
//    free(ptr);
//           Cy_Flash_WriteRow(FLASH_ADDR ,ptr);
    for(;;)
    {

        
            /* Process all widgets */
            
           
            /* To sync with Tuner application */
            
            
            /* Start next scan */
            
        
 /* Place your application code here. */
    }
}

/* [] END OF FILE */