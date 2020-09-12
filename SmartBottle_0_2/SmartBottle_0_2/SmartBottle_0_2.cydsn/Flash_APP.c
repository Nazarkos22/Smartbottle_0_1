/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#include "project.h"
#include "Config_u.h"
#include "Flash_APP.h"
#include <stdlib.h>
#include <string.h>


U_flash_data_t FLASH_Data;
/* Core Callback */
static void FlashCore_Clbk(void (*eventClbk)())
{
    eventClbk();
}

/***********************************************************************************************
Fucntoin: is_any_flash_data_empty
Type: Bool
Input: Poiner to array of data, lenth of array
Execution: Function checks, is your array has at least one NULL data
Return: If your array has at least one NULL data, function returns TRUE, else - FALSE
***********************************************************************************************/
 bool is_any_flash_data_empty(uint32_t* data, uint8 len)
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

/***********************************************************************************************
Fucntoin: get_checksum
Type: uint32_t
Input: Poiner to array of data, lenth of array
Execution: Function counts checksum of input data
Return: Checksum
***********************************************************************************************/
uint32_t get_checksum(uint32_t* msg, uint8_t len)
{
    
  uint8_t idx;
  uint32_t checksum = CHECKSUM_VARIABLE;
    
    for(idx = ZERO; idx < len; idx++)
    {
        
        checksum ^= msg[idx]; 
        
    }
    
  return checksum;
    
}



/***********************************************************************************************
Fucntoin: eraze_flash_data
Type: void
Input: Flash memory address, size of data
Execution: Function write NULL on Flash memory 
Return: -----------
***********************************************************************************************/

void eraze_flash_data(uint32_t ADDR, size_t size)
{
    
    /* Create memory space with pointer on it */
    uint32_t* ptr = (uint32_t*) malloc(size);   
    /* Write ZERO in each byte of memory space */
    memset(ptr, ZERO, size);
    /* Write array of ZERO on FLASH */
    Cy_Flash_WriteRow(ADDR, ptr);
    /* Free memory space */
    free(ptr);
    
}
/***********************************************************************************************
Fucntoin: make_data_for_flash
Type: void
Input: Poiner to array of flash data, pointer to array of Baseline data, lenth of Baseline array
Execution: Function copies data from Baseline to flash data array and assign checksum of baseline to the 
           last element of flash data
Return: -----------
***********************************************************************************************/

void make_data_for_flash(uint32_t* flash_data,uint32_t* baseline, uint8_t len)
{
    
    uint8 idx;
    
    for(idx = ZERO; idx < len; idx ++)
    {
        
        flash_data[idx] = baseline[idx]; 
        
    }
    
    flash_data[len] = get_checksum(baseline, len);
    
}

/***********************************************************************************************
Fucntoin: Read_Flash_Baseline
Type: bool
Input: Flash memory address, pointer to array of Baseline data, size of 
       flash data array
Execution: Function read Flash memory and copies baseline data to Baseline array
Return: If Baseline data array has not any NULL data, returns TRUE, else - FALSE
***********************************************************************************************/

bool Read_Flash_Baseline(uint32_t ADDR, uint32_t* baseline, uint8 len, size_t size)
{
    
    /*Function status flag*/
    bool ret = false ;
    /*Create buffer*/
    uint32_t* buffer = (uint32_t*) malloc(size);
    /*Copy flash data to buffer*/
    memcpy(buffer,(uint32_t*) ADDR, size);
    /*Do only if all data is not NULL*/
    if(is_any_flash_data_empty(buffer, len)==false) 
    {
        
        /*Do only if data is verified by checksum*/
        if(get_checksum(buffer, len) == buffer[len]) 
        {   
            
            /*Status variable*/
            bool result = true;
            /*Copy buffer to baseline*/
            memcpy(baseline, buffer, size);
            /*Check for NULL data and return to status variable*/
            result = is_any_flash_data_empty(baseline, len);
            /*Do only if baseline data has not any NULL data*/
            if(result == false) 
            {
                
                /*Set function status variable*/
                ret = true;
                
            }
            
        }
        
    }
    /*Free buffer*/
    free(buffer);
    /*Return function status*/
    return ret;
}



void Flash_Processing(void)
{
    /* Do only when device have just turned ON */
    if(FLASH_Data.flash_is_scanned != true)
    {
        /* Scan Flah memory data and return status flag */
        FLASH_Data.Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, FLASH_Data.Baseline, MAX_SENSOR_VALUE, sizeof(U_cfg_t)); 
        /* Do only if scanned data is invalid */
        if(FLASH_Data.Baseline_Read_Status == false)
        {
            FlashCore_Clbk(flash_CoreFlashNeedCsdScan);
        }
        /* Set flag that flash memory was scanned */
        FLASH_Data.flash_is_scanned = true;
    }
    
    /* Do only if when all flash data is ready for writing */
    if(FLASH_Data.is_data_redy_for_writing == true)
    {
        /* Form array data with Baseline data and checksum */
        make_data_for_flash(FLASH_Data.flash_data, FLASH_Data.Baseline, MAX_SENSOR_VALUE);
        /* Eraze Flash memory size of Baseline data plus checksum */
        eraze_flash_data(FLASH_ADDR, sizeof(U_cfg_t));
        /* Write on Flash memory Baseline and checksum */
        Cy_Flash_WriteRow(FLASH_ADDR, FLASH_Data.flash_data); 
    }
    
}
/* [] END OF FILE */
