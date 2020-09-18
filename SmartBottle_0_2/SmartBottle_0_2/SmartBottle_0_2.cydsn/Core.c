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
#include "ble_application.h"
#include "timers_counters.h"
#include <stdlib.h>
#include <string.h>

/* Declaration of structure with State data */
Current_state_t static CurrentState;

/* Extern Csd and Flash data for exchanging */
extern U_csd_data_t CSD_Data;
extern U_flash_data_t FLASH_Data;


/****************************************************************/
/* Definition of Core Callbeck to call handlers from other apps */

static void Core_Callback_to(void(*eventHandler)())
{
    eventHandler();
}

/***************************************************************/
/***************************************************************/


/* Switch current statement if this handler is called by flash app */
void flash_NeedCsdScan(void)
{
    CurrentState.Current_State = FLASH_NEED_CSD_SCAN;
}


/*  */
void DoNothingClbk(void)
{
    
}



/*  */
void DEVICE_DO_NOTHING_FUNC(void (*eventClbk)())
{
     eventClbk();
}

/* Callback from BLE when State is connected  */
void ble_is_connected(void)
{
    CurrentState.Current_State = BLE_CONNECTED;
}
/*  */
void Switch_Statement(void)
{
    switch(CurrentState.Current_State)
    {
        case BLE_CONNECTED:
            Core_Callback_to(core_CsdAllowScan);
            Core_Callback_to(core_TmrStart);
            break;
        case BLE_CONNECTED_ERROR:
            BLE_CONNECTED_ERROR_FUNC(bleConnErrorClbk);
            break;
        case FLASH_NEED_CSD_SCAN:
            Core_Callback_to(csd_ScanForFlash);
            break;
        case BLE_ADVERTISE_ERROR:
            BLE_ADVERTISE_ERROR_FUNC(bleAdvertErrorClbk);
            break;
        case BLE_DISCONNECTED:
            BLE_DISCONNECTED_FUNC(bleDisconnClbk);
            break;
        case BLE_DISCONNECTED_ERROR:
            BLE_DISCONNECTED_ERROR_FUNC(bleDisconnErrorClbk);
            break;
        case CSD_START_SCAN:
            CSD_START_SCAN_FUNC(csdStartScanClbk);
            break;
        case CSD_START_SCAN_ERROR:
            CSD_START_SCAN_ERROR_FUNC(csdStartScanErrorClbk);
            break;
        case CSD_FINISH_SCAN:
            CSD_FINISH_SCAN_FUNC(csdFinishScanClbk);
            break;
        case CSD_FINISH_SCAN_ERROR:
            CSD_FINISH_SCAN_ERROR_FUNC(csdFinishScanErrorClbk);
            break;
        case CSD_LEVEL_COUNTED:
            CSD_LEVEL_COUNTED_FUNC(csdLevelCountClbk);
            break;
        case CSD_LEVEL_COUNTED_ERROR:
            CSD_LEVEL_COUNTED_ERROR_FUNC(csdLevelCountErrorClbk);
            break;
        case DEVICE_DO_NOTHING:
            DEVICE_DO_NOTHING_FUNC(DoNothingClbk);
            break;
        default:
            break;
    }
}
/* [] END OF FILE */
