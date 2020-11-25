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
    
/* FLASH memory address for config */    
#define FLASH_ADDR (CY_EM_EEPROM_BASE)
    
/* Amount of array data, which will be written on FLASH memory */    
#define FLASH_DATA (11u) 

    
/* Config data structure */      
typedef struct
{
    
    U_config_t Flash_Data;
    uint32_t checksum;
    
}   U_cfg_t;


/* Flash data structure */
typedef struct
{
    
    /* Array of all flash data */
    uint32_t flash_data[FLASH_DATA]; 
    /* Set this flag when read flash */
    bool Baseline_Read_Status;
    
}   U_flash_data_t;


/* Functoin to scan flash config */
bool Read_Flash_Baseline(uint32_t ADDR, uint32_t* data, uint8 len, size_t size);

/* Function to check if any data equal NULL(true) or NOT(false) */ 
bool is_any_flash_data_empty(uint32_t* data, uint8 len);

/* Function to calculate checksum of data */
uint32_t get_checksum(uint32_t* msg, uint8_t len);

/* Function write on FLASH ZERO */
void eraze_flash_data(uint32_t ADDR, size_t size);

/* Function to prepare data from sensors and checksum for write on FLASH memory */
void make_data_for_flash(uint32_t* flash_data,uint32_t* baseline, uint8_t len);


 
/* [] END OF FILE */
  #endif 