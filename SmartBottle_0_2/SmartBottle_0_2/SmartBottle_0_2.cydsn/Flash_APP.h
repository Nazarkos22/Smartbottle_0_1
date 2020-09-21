/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/

#ifndef __FLASH_APP_H_   
#define __FLASH_APP_H_    
#include "project.h"
#include "Flash_APP.h"
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
    /* Array of Baseline data */
    uint32_t Baseline[MAX_SENSOR_VALUE];
    /* Set this flag when read flash */
    bool Baseline_Read_Status;
    /* Flag to check if flash is scanned */
    bool flash_ready_for_scan;
    /* Flag to check is ready data to write on flash memory or not */
    bool is_data_redy_for_writing;
    /* Flag to indicate timer interrupt */
    bool get_tmr_interrupt;
    /* Variable to count input timer interrupts */
    uint32_t interrupt_counter;
    /* Flag to indicate finish scan */
    bool flash_finish_scan;
    /* Flag to indicate finish write */
    bool flash_finish_write;
    
}   U_flash_data_t;

typedef struct
{
    /* Data for exchange with Csd */
    uint32_t Exchange_data[EXCHANGE_DATA_NUMBER];
    /* Checksum for validating exchanged data */
    uint32_t Checksum;
}U_Flash_Exchange_t;

typedef enum
{
    NEED_FLASH_SCAN,
    FLASH_SEND_DATA,
    FLASH_NEED_CSD_SCAN,
    FLASH_RECEIVE_CSD_SCAN_DATA,
    FLASH_READY_FOR_WRITING,
    FLASH_DO_NOTHING
    
}U_Flash_State;

typedef struct
{
    uint8_t Previous_State;
    uint8_t Current_State;
    uint8_t Next_State;
}U_Flash_State_t;


/* Functoin to scan flash config */
bool Read_Flash_Baseline(uint32_t ADDR, uint32_t* data, uint8 len, size_t size);

/* Function to check if any data equal NULL(true) or NOT(false) */ 
bool is_any_flash_data_empty(uint32_t* data, uint8 len);



/* Function write on FLASH ZERO */
void eraze_flash_data(uint32_t ADDR, size_t size);

/* Function to prepare data from sensors and checksum for write on FLASH memory */
void make_data_for_flash(uint32_t* flash_data,uint32_t* baseline, uint8_t len);

/* Declaration Callbacks */

void flash_CallCsdScanForFlash(void);
void flash_CsdFinishSendData(void);
void flash_CoreStartScanClbk(void);
void flash_SendExchangeData(void);
void flash_ReadySendData(void);
void flash_CoreFlashGoodDataClbk(void);
void flash_CoreFlashBadDataClbk(void);
void flash_CoreTmrStart(void);
void flash_Tmr_FlashScanFinish(void);
void flash_InvalidExchangeData(void);
/*************************************/


 
/* [] END OF FILE */
  #endif 