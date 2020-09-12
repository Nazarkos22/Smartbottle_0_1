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

Current_state_t CurrentState;
Middle_used_data_t Middle_data;



/*  */
void DoNothingClbk(void)
{
    
}

/* Initialisation CSD Callback */
static void CoreCsd_Clbk(void (*eventClbk)())
{
    eventClbk();
}

/* Initialisation Flash Callback */
static void CoreFlash_Clbk(void (*eventClbk)())
{
    eventClbk();
}

/* Initialisation BLE Callback */
static void CoreBle_Clbk(void (*eventClbk)())
{
    eventClbk();
}

/* Initialisation Timer Callback */
static void CoreTmr_Clbk(void (*eventClbk)())
{
    eventClbk();
}
/*  */
void DEVICE_DO_NOTHING_FUNC(void (*eventClbk)())
{
     eventClbk();
}

/* Callback from BLE when State is connected  */
void bleConnCoreClbk(void)
{
    CurrentState.Current_State = BLE_CONNECTED;
}
/*  */
void Switch_Statement(void)
{
    switch(CurrentState.Current_State)
    {
        case BLE_CONNECTED:
            CoreCsd_Clbk(core_CsdAllowScan);
            CoreTmr_Clbk(core_TmrStart);
            break;
        case BLE_CONNECTED_ERROR:
            BLE_CONNECTED_ERROR_FUNC(bleConnErrorClbk);
            break;
        case BLE_ADVERTISE:
            BLE_ADVERTISE_FUNC(bleAdvertClbk);
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
