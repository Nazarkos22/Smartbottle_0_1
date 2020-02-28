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

#ifndef _FLASH_CONFIG_U_H_   
#define _FLASH_CONFIG_U_H_    
#include "project.h"
#include "Config_u.h"
#include <stdlib.h>
#include <string.h>
#define FLASH_ADDR CY_EM_EEPROM_BASE
#define FLASH_DATA (11u)
#define ARR_CHECKSUM (10u)    
typedef struct
{
    U_config_t Flash_Data;
    uint32_t checksum;
    
}U_cfg_t;
uint32_t flash[FLASH_DATA];
bool is_writen_config(void);
void eraze_flash_data(void);
uint32_t* free_data(uint32_t data[MAX_SENSOR_VALUE]);
 uint32_t* make_data_for_flash(uint32_t* data);
uint32_t* write_flash_data_u(uint32_t addr, uint32_t* data);
static bool is_memory_empty(uint32_t addr);
/* [] END OF FILE */
  #endif 