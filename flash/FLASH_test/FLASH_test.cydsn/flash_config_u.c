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
#include "flash_config_u.h"
#include <stdlib.h>
#include <string.h>
 bool is_memory_empty(uint32_t addr)
{
    bool ret = true;
    uint32_t* data =(uint32_t*) addr;
    uint8 idx;
    for(idx = 0; idx < (sizeof(U_cfg_t));idx ++)
    {
        if (data[idx] != ZERO)
        {
            ret = false; 
            break;
        }
    }

return ret;
}
uint32_t get_checksum(uint32_t* msg)
{
  uint32_t idx;
  uint32_t checksum = 1;
    for(idx = ZERO; idx < sizeof(U_config_t); idx++)
    {
     checksum ^= msg[idx];   
    }
  return checksum;
}
bool is_writen_config(void)
{
    bool result, ret;
    result = is_memory_empty(FLASH_ADDR);
   
    uint32_t* ptr = (uint32_t*) malloc(sizeof(U_cfg_t));
    memcpy(ptr,(uint32_t*) FLASH_ADDR, sizeof(U_cfg_t));
    uint32_t data = get_checksum(ptr);
    if((data == ptr[ARR_CHECKSUM])&&(result == false))
    {
        ret = false;
    }

    else
    {
        ret = true;
    }
    free(ptr);
    return ret;
}

 uint32_t* make_data_for_flash(uint32_t* data)
{
  uint8 idx;
  uint32_t flash[FLASH_DATA];
    for(idx=ZERO; idx<MAX_SENSOR_VALUE; idx++)
    {
      flash[idx] = data[idx];
    }
      flash[ARR_CHECKSUM] = get_checksum(data);
      return flash;
    }
void write_flash_data(uint32_t* data)
{
     Cy_Flash_WriteRow(FLASH_ADDR, data);
}


void eraze_flash_data(void)
{
  uint32_t* ptr = (uint32_t*) malloc(sizeof(U_cfg_t));    
    memset(ptr, ZERO, sizeof(U_cfg_t));
    Cy_Flash_WriteRow(FLASH_ADDR, ptr);
    free(ptr);
}
/* [] END OF FILE */
