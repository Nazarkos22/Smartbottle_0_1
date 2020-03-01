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





bool is_calibration_data_empty(uint32_t addr)
{
   bool ret = true;
     uint32_t* data =(uint32_t*) addr;
    uint8 idx;
    for (idx = ZERO; idx < (sizeof(U_config_t)); idx++)
    {
     if(data[idx] !=0)
    {
        ret = false;
    }
    }
    return ret;
}


uint32_t get_checksum(uint32_t* msg)
{
  uint32_t idx;
  uint32_t checksum = 15u;
    for(idx = ZERO; idx < MAX_SENSOR_VALUE; idx++)
    {
     checksum |= msg[idx];   
    }
  return checksum;
}


bool is_writen_config(void)
{
    bool result, ret = false;
    if(is_calibration_data_empty(FLASH_ADDR) == false)
    {
    result = is_memory_empty(FLASH_ADDR);
   
    uint32_t* ptr = (uint32_t*) malloc(sizeof(U_cfg_t));
    
    memcpy(ptr,(uint32_t*) FLASH_ADDR, sizeof(U_cfg_t));
    
    uint32_t data = get_checksum(ptr);
    if((data == ptr[ARR_CHECKSUM])&&(result == false))
    {
        ret = true;
    }

    else
    {
        ret = false;
    }
    free(ptr);
    }
    
    return ret;
}


void make_data_for_flash(uint32_t* data)
{
  uint8 idx;

    for(idx=ZERO; idx<MAX_SENSOR_VALUE; idx++)
    {
      flash[idx] = data[idx];
    }
      flash[ARR_CHECKSUM] = get_checksum(data);
    
}


void eraze_flash_data(void)
{
  uint32_t* ptr = (uint32_t*) malloc(sizeof(U_cfg_t));    
    memset(ptr, ZERO, sizeof(U_cfg_t));
    Cy_Flash_WriteRow(FLASH_ADDR, ptr);
    free(ptr);
}
/* [] END OF FILE */
