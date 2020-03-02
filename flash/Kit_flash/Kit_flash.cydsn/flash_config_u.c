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
uint32_t* write_flash_data(uint32_t Data[10u])
{
    uint8 idx;
    for(idx=0;idx<10u;idx++)
    {
        Data[idx]=0x2b;
    }
    uint32_t* ptr = Data;
     Cy_Flash_WriteRow(FLASH_ADDR, ptr);
    return ptr;
}
uint32_t get_checksum(uint32_t* msg, uint32_t len)
{
  uint8_t idx;
  uint32_t checksum = 1;
    for(idx = ZERO; idx < len; idx++)
    {
     checksum ^= msg[idx];   
    }
  return checksum;
}
void eraze_flash_data(void)
{
  uint32_t* ptr = (uint32_t*) malloc(0x40);    
  memset(ptr, ZERO, 0x40);
    Cy_Flash_WriteRow(FLASH_ADDR, ptr);
    free(ptr);
}
/* [] END OF FILE */
