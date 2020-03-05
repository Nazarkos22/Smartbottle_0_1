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
#include "Flash_Process.h"
#include <stdlib.h>
#include <string.h>

 bool is_any_data_empty(uint32_t* data, uint8 len)
{
    bool ret = false;
    
    uint8 idx;
    for(idx = 0; idx < len ;idx ++)
    {
        if (data[idx] == ZERO)
        {
            ret = true; 
            break;
        }
    }
return ret;
}






uint32_t get_checksum(uint32_t* msg, uint8_t len)
{
  uint32_t idx;
  uint32_t checksum = 15u;
    for(idx = ZERO; idx < len; idx++)
    {
     checksum |= msg[idx];   
    }
  return checksum;
}






uint8_t make_Baseline_Data(uint32_t* buffer, uint32_t* data, uint8 len)
{
 uint8 idx, status = ZERO;
    for(idx = ZERO; idx < len; idx ++)
    {
      data[idx] = buffer[idx];  
    }
    if(is_any_data_empty(data, len) == false)
    {
     status = GOOD;   
    }
    return status;
}

void eraze_flash_data(uint32_t ADDR)
{
   uint32_t* ptr = (uint32_t*) malloc(sizeof(U_cfg_t));    
    memset(ptr, ZERO, sizeof(U_cfg_t));
    Cy_Flash_WriteRow(ADDR, ptr);
    free(ptr);
}
void make_data_for_flash(uint32_t* flash_data,uint32_t* baseline, uint8_t len)
{
    
    uint8 idx;
    for(idx = ZERO; idx < len; idx ++)
    {
       flash_data[idx] = baseline[idx]; 
    }
    flash_data[len] = get_checksum(baseline, len);
    
}

//Function read sensor baseline data from flash memory(true if success)
bool Read_Flash_Baseline(uint32_t ADDR, uint32_t* data, uint8 len)
{
 bool ret = false ;
    uint32_t* buffer = (uint32_t*) malloc(sizeof(U_cfg_t));
    //copy flash data to buffer
    memcpy(buffer,(uint32_t*) ADDR, sizeof(U_cfg_t));
    if(is_any_data_empty(buffer, len)==false)
    {
        if(get_checksum(buffer, len) == buffer[ARR_CHECKSUM])
        {   
            uint8 result = ZERO;
            result = make_Baseline_Data( buffer, data, len);
            if(result == GOOD)
            {
             ret = true;   
            }
        }
    }
    free(buffer);
    return ret;
}
/* [] END OF FILE */
