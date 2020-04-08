/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/

#ifndef __FLASH_PROCESS_H_   
#define __FLASH_PROCESS_H_    
#include "project.h"
#include "Flash_Process.h"
#include "Config_u.h"
#include <stdlib.h>
#include <string.h>
    
    
#define FLASH_ADDR CY_EM_EEPROM_BASE //FLASH memory address for config
#define FLASH_DATA (11u)// Amount of array data, which will be written to FLASH memory 

    
    
typedef struct
{
    U_config_t Flash_Data;
    uint32_t checksum;
    
}U_cfg_t;

typedef struct
{
 bool Baseline_Read_Status;   
}U_flash_flag_t;

typedef struct
{
   uint32_t flash_data[FLASH_DATA]; 
}U_flash_data_t;



bool Read_Flash_Baseline(uint32_t ADDR, uint32_t* data, uint8 len, size_t size);


bool is_any_flash_data_empty(uint32_t* data, uint8 len);//function checks is senors data equal NULL(true) or NOT(false)


uint32_t get_checksum(uint32_t* msg, uint8_t len);//

uint8_t make_Baseline_Data(uint32_t* buffer, uint32_t* data, uint8 len);//


void eraze_flash_data(uint32_t ADDR, size_t size);// function write on FLASH "0" sise of "U_cfg_t"


void make_data_for_flash(uint32_t* flash_data,uint32_t* baseline, uint8_t len);// prepare data from sensors and checksum for write on FLASH memory


 
/* [] END OF FILE */
  #endif 