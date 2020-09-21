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

/* Declaration Flash data structures */
U_flash_data_t FLASH_Data;
U_Flash_Exchange_t Flash_Exchange;
U_Flash_State_t Flash_State;



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
uint32_t get_checksum(uint32_t* msg, uint8_t len, uint32_t variable)
{
    
  uint8_t idx;
  uint32_t checksum = variable;
    
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
    
    flash_data[len] = get_checksum(baseline, len, FLASH_CHECKSUM_VARIABLE);
    
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
        if(get_checksum(buffer, len, FLASH_CHECKSUM_VARIABLE) == buffer[len]) 
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
/****************************************************/
/********//* Definition of Flash callback *//********/
static void Flash_Callback_to(void (*eventHandler)())
{
    eventHandler();
}
/****************************************************/
/****************************************************/

/* Handler which indicates flash finish scan */
static void flash_FlashFinishScan(void)
{
    FLASH_Data.flash_finish_scan = true;
}


static void flash_ValidExchangeData(void)
{
    memcpy(FLASH_Data.Baseline, Flash_Exchange.Exchange_data, sizeof(U_config_t));
    Flash_State.Current_State = FLASH_READY_FOR_WRITING;
}

/*  */
void flash_ReadySendData(void)
{
    Flash_State.Current_State = FLASH_SEND_DATA;
}

void flash_CsdFinishSendData(void)
{
    if((Flash_Exchange.Checksum == get_checksum(Flash_Exchange.Exchange_data,MAX_SENSOR_VALUE,CSD_CHECKSUM_VARIABLE))&&
    (Flash_Exchange.Exchange_data[MAX_SENSOR_VALUE] == get_checksum(Flash_Exchange.Exchange_data,MAX_SENSOR_VALUE,CSD_CHECKSUM_VARIABLE)))
    {
        Flash_Callback_to(flash_ValidExchangeData);
    }
    else
    {
        Flash_Callback_to(flash_InvalidExchangeData);
    }
}

/*  */
static void flash_AllowScan(void)
{
    FLASH_Data.flash_ready_for_scan = true;
}

/*  */
static void flash_NotScan(void)
{
    FLASH_Data.flash_ready_for_scan = false;
}

/*  */
static void flash_AllowWriteData(void)
{
    FLASH_Data.is_data_redy_for_writing = true;
}

/*  */
static void flash_NeedCsdScan(void)
{
    Flash_State.Current_State = FLASH_NEED_CSD_SCAN;
}
/*  */
static void flash_PrepareExchangeData(void)
{
    Flash_Exchange.Checksum = get_checksum(FLASH_Data.Baseline, MAX_SENSOR_VALUE, FLASH_CHECKSUM_VARIABLE);
    /* Copy Baseline data to exchange data */
    memcpy(Flash_Exchange.Exchange_data, FLASH_Data.Baseline, sizeof(U_cfg_t));
    /*  */
    Flash_Exchange.Exchange_data[MAX_SENSOR_VALUE] = Flash_Exchange.Checksum;
}
/* Handler which indicates input timer interrupt */
void flash_Tmr_FlashScanFinish(void)
{
    FLASH_Data.get_tmr_interrupt = true;
    
}
void Switch_Flash_State(uint8_t currstate)
{
    switch(currstate)
    {
        case NEED_FLASH_SCAN:
            Flash_Callback_to(flash_AllowScan);
            break;
        case FLASH_SEND_DATA:
            Flash_Callback_to(flash_PrepareExchangeData);
            Flash_Callback_to(flash_SendExchangeData);
            break;
        case FLASH_NEED_CSD_SCAN:
            Flash_Callback_to(flash_CallCsdScanForFlash);
            break;
        case FLASH_READY_FOR_WRITING:
            Flash_Callback_to(flash_AllowWriteData);
            break;
        case FLASH_DO_NOTHING:
            Flash_Callback_to(flash_CoreTmrStart);
            break;
        default:
            break;
    }
}


void Flash_Processing(void)
{
    /* Do only when device have just turned ON or device need scan */
    if(FLASH_Data.flash_ready_for_scan == true)
    {
        /* Set flag */
        FLASH_Data.flash_finish_scan = false;
        /* Callback to indicate start scan and asking for starting timer*/
        Flash_Callback_to(flash_CoreTmrStart);
        /* Scan Flah memory data and return status flag */
        FLASH_Data.Baseline_Read_Status = Read_Flash_Baseline(
            FLASH_ADDR, FLASH_Data.Baseline, MAX_SENSOR_VALUE, sizeof(U_cfg_t)
        ); 
        /* Callback to indicate finish scan */
        Flash_Callback_to(flash_FlashFinishScan);
        /* Callbac to avoid scanning in next iteration */
        Flash_Callback_to(flash_NotScan);
        /* Do only if scanned data is invalid */
        if(FLASH_Data.Baseline_Read_Status == false)
        {
            Flash_Callback_to(flash_NeedCsdScan);
        }
        /* If scanned data is valid */
        else if(FLASH_Data.Baseline_Read_Status == true)
        {
            /* Callback to start copy data to CSD app */
            Flash_Callback_to(flash_ReadySendData);
        }
    }
    
    /* Do only if when all flash data is ready for writing */
    if(FLASH_Data.is_data_redy_for_writing == true)
    {
        /* Reset flag */
        FLASH_Data.is_data_redy_for_writing = false;
        /* Form array data with Baseline data and checksum */
        make_data_for_flash(FLASH_Data.flash_data, FLASH_Data.Baseline, MAX_SENSOR_VALUE);
        /* Eraze Flash memory size of Baseline data plus checksum */
        eraze_flash_data(FLASH_ADDR, sizeof(U_cfg_t));
        /* Write on Flash memory Baseline and checksum */
        Cy_Flash_WriteRow(FLASH_ADDR, FLASH_Data.flash_data); 
    }
    
}
/* [] END OF FILE */
