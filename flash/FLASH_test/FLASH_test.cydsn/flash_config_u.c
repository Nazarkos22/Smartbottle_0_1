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
static bool is_memory_empty(uint32_t addr)
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


uint32_t* make_data_for_flash(uint32_t* data, uint8 len)
{
  uint32_t idx;
  
for(idx=ZERO; idx<len; idx++)
{
 data[idx]=0x2b * idx;

}
return data;
}
uint32_t* write_flash_data_u(uint32_t addr,uint32_t* data)
{
     Cy_Flash_WriteRow(addr, data);
     return data;
}
uint32_t* write_flash_data(uint32_t* Data)
{
    uint8 idx;
    for(idx=0;idx<10u;idx++)
    {
       Data[idx]=0x2b;
    }
  
     Cy_Flash_WriteRow(FLASH_ADDR, Data);
    return Data;
}
uint32_t get_checksum(uint32_t* msg)
{
  uint32_t idx;
  uint32_t checksum = 1;
    for(idx = ZERO; idx < CY_FLASH_SIZEOF_ROW; idx++)
    {
     checksum ^= msg[idx];   
    }
  return checksum;
}
void eraze_flash_data(void)
{
  uint32_t* ptr = (uint32_t*) malloc(sizeof(U_cfg_t));    
    memset(ptr, ZERO, sizeof(U_cfg_t));
    Cy_Flash_WriteRow(FLASH_ADDR, ptr);
    free(ptr);
}
/* [] END OF FILE */
