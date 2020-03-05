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

#ifndef __FLASH_PROCESS_H_   
#define __FLASH_PROCESS_H_    
#include "project.h"
#include "Flash_Process.h"
#include "Config_u.h"
#include <stdlib.h>
#include <string.h>
    
    
#define FLASH_ADDR CY_EM_EEPROM_BASE //FLASH memory address for config
#define FLASH_DATA (11u)// Amount of array data, which will be written to FLASH memory 
#define ARR_CHECKSUM (10u)// Number of array data, in which will be stored checksum 
    
    
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


  uint32_t flash[FLASH_DATA];// data, which will be prepared for write on flash


bool Read_Flash_Baseline(uint32_t ADDR, uint32_t* data, uint8 len);


bool is_writen_data_empty(uint32_t addr);//function checks, is calibration data memory(return true) or not (return false)


bool is_writen_config(void);//function check if data is on FLASH memory  ( all is good - function = true, not = false)


void eraze_flash_data(uint32_t ADDR);// function write on FLASH "0" sise of "U_cfg_t"


void make_data_for_flash(uint32_t* flash_data,uint32_t* baseline, uint8_t len);// prepare data from sensors and checksum for write on FLASH memory


 bool is_memory_empty(uint32_t addr);// function check, is FLASH memory  with address "addr" sise of "U_cfg_t" is empty (true if empty)
/* [] END OF FILE */
  #endif 