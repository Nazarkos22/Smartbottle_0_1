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
#include "Config_u.h"
#include <stdlib.h>
#define FLASH_ADDR CY_EM_EEPROM_BASE

typedef struct
{
    U_config_t Flash_Data;
    uint32_t checksum;
}U_cfg_t;
  
/* [] END OF FILE */
