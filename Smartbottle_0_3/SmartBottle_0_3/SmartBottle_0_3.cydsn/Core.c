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
#include "Core.h"
#include "CSD_APP.h"
#include "Flash_APP.h"
#include "led.h"
#include "ble_application.h"
#include "timers_counters.h"
#include <stdlib.h>
#include <string.h>

/* Declaration of structure with State data */
static Current_state_t  CurrentState;
U_flash_data_t FLASH_Data;
/* Temporary */
extern U_csd_data_t CSD_Data;




/****************************************************************/
/* Definition of Core Callbeck to call handlers from other apps */

static void Core_Callback_to(void(*eventHandler)())
{
    eventHandler();
}

static void core_ChangeState(void)
{
    CurrentState.Current_State ++;
}

static void core_ReturnState(void)
{
    CurrentState.Current_State --;
}

static void core_DoNothing(void)
{
    Start_Timer(CORE_APP, 500u);
   Core_Callback_to(core_ChangeState); 
}

static void core_FinishDoNothing(void)
{
    if(CurrentState.Timer_Interrupt == true)
    {
        CurrentState.Timer_Interrupt = false;
        Core_Callback_to(core_ReturnState);  
    }
}
/***************************************************************/
/***************************************************************/


void core_TmrInterrupt(void)
{
    CurrentState.Timer_Interrupt = true;
}




/* Callback from BLE when State is connected  */
void core_BleConnected(void)
{
    CurrentState.Current_State = BLE_CONNECTED;
}

void core_BleAdvertise(void)
{
    CurrentState.Current_State = BLE_ADVERTISE;
}

void core_BleDisconnected(void)
{
    CurrentState.Current_State = BLE_DISCONNECTED;
}

/* Main Device Statement */
void Switch_Statement(void)
{
    switch(CurrentState.Current_State)
    {
        case BLE_CONNECTED:
            Core_Callback_to(csd_SwitchState);
            Core_Callback_to(led_BleConnected);
            Core_Callback_to(Timer_Handler);
            break;
            
        case BLE_ADVERTISE:
            Core_Callback_to(led_BleAdvertise);
            Core_Callback_to(Timer_Handler);
            break;
            
        case BLE_DISCONNECTED:
            Core_Callback_to(led_BleDisonnected);
            Core_Callback_to(Timer_Handler);
            break;
            
        case DEVICE_DO_NOTHING:
            Core_Callback_to(core_DoNothing);
            Core_Callback_to(Timer_Handler);
            break;
            
        case DEVICE_FINISH_DO_NOTHING:
            Core_Callback_to(core_FinishDoNothing);
            Core_Callback_to(Timer_Handler);
            break;
            
        default:
            CurrentState.Current_State = DEVICE_DO_NOTHING;
            break;
    }
}

/***************************************************************************
Function: void Flash_Processing(void)
Execution: 1. Check Flash Memory with some address, is it "empty" or not
              ("empty" means that it can be not only NULL data, it can be some
              data, in which checksum does not verify)
************************!!!IF DATA IS NOT "EMPTY"!!!************************
           2. Copy data to Baseline array

************************!!!IF DATA IS "EMPTY"!!!****************************
           2. Form Baseline data from sensors, by scanning 10 times with some
              delay and average data from all sensors
           3. Get checksum 
           4. Eraze Flash memory with some address sizeof Baseline data plus checksum
           5. Write Baseline data and checksum on Flash memory with that address
           6. Reset
****************************************************************************/
void Flash_Scan(void)
{  
    
    /* Scan Flah memory data and return status flag */
    FLASH_Data.Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, CSD_Data.Baseline, MAX_SENSOR_VALUE, sizeof(U_cfg_t)); 
    /* Do only if scanned Flash data is invalid */
    if(FLASH_Data.Baseline_Read_Status == false)
    {
        
        /* Form baseline by scanning some amount of times with delay */
        Create_Baseline_data(CSD_Data.Baseline, MAX_SENSOR_VALUE, BASELINE_SCAN_TIMES); 
        /* Form array data with Baseline data and checksum */
        make_data_for_flash(FLASH_Data.flash_data, CSD_Data.Baseline, MAX_SENSOR_VALUE);
        /* Eraze Flash memory size of Baseline data plus checksum */
        eraze_flash_data(FLASH_ADDR, sizeof(U_cfg_t));
        /* Write on Flash memory Baseline and checksum */
        Cy_Flash_WriteRow(FLASH_ADDR, FLASH_Data.flash_data); 
        /* RESET function*/
        __NVIC_SystemReset() ;   
        
    }
    
}

void core_RestartSystem(void)
{
    __NVIC_SystemReset() ;   
}


/* [] END OF FILE */
