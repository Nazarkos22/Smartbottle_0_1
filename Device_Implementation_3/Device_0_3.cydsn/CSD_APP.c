/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#include "project.h"
#include "Config_u.h"
#include "CSD_APP.h"
#include "timer.h"
#include <stdlib.h>
#include <string.h>

/* Initialization of structure with all sensor and baseline data */
U_csd_data_t CSD_Data; 
//U_Csd_Exchange_t CSD_Exchange;
/* Initialisation of CSD current state data */
U_Csd_State_t CSD_State;

uint8 header[] = {0x0Du, 0x0Au};
uint8 tail[] = {0x00u, 0xFFu, 0xFFu};

/***********************************************************************************************
Fucntoin: is_any_csd_data_empty
Type: Bool
Input: Poiner to array of data, lenth of array
Execution: Function checks, is your array has at least one NULL data
Return: If your array has at least one NULL data, function returns TRUE, else - FALSE
***********************************************************************************************/
bool is_any_csd_data_empty(uint32_t* data, uint8 len)
{ 
    
    bool ret = false;
    uint8 idx;
    
    for(idx = ZERO; idx < len; idx++)
    {
        
        if(data[idx] == ZERO)
        {
            
            return true;
            
        }
        
    }
    
    return ret;
    
}


bool clean_data(uint32_t* data, size_t size, uint8 len)
{
    bool ret = true;
    uint8 idx;
    /* Write ZERO in each byte of data */
    memset(data, ZERO, size);
    
    for(idx = ZERO; idx < len; idx++)
    {
        
        if(data[idx] != ZERO)
        {
            
            return false;
            
        }
        
    }
    
    return ret; 
    
}
/***********************************************************************************************
Fucntoin: make_sensors_data
Type: uint8_t
Input: Poiner to array of data, lenth of array
Execution: Assigns sensor raw counts to array data
Return: 0u if any of sensor data is NULL, 1u if all sensor data has some value
***********************************************************************************************/
bool make_sensors_data(uint32_t* data, uint8 len)
{ 
    
    bool Status = false;
    
    data[FIRST_lvl] = CapSense_BUTTON0_SNS0_RAW0_VALUE;
    data[SECOND_lvl] = CapSense_BUTTON1_SNS0_RAW0_VALUE;
    data[THIRD_lvl] = CapSense_BUTTON2_SNS0_RAW0_VALUE;
    data[FOURTH_lvl] = CapSense_BUTTON3_SNS0_RAW0_VALUE;
    data[FIFTH_lvl] = CapSense_BUTTON4_SNS0_RAW0_VALUE;
    data[SIXTH_lvl] = CapSense_BUTTON5_SNS0_RAW0_VALUE;
    data[SEVENTH_lvl] = CapSense_BUTTON6_SNS0_RAW0_VALUE;
    data[EIGHTH_lvl] = CapSense_BUTTON7_SNS0_RAW0_VALUE;
    data[NINETH_lvl] = CapSense_BUTTON8_SNS0_RAW0_VALUE;
    data[TENTH_lvl] = CapSense_BUTTON9_SNS0_RAW0_VALUE;
    
    if(is_any_csd_data_empty(data, len) == false)
    {
        
        return true;
        
    }
    
    return Status;
    
}
/***********************************************************************************************
Fucntoin: Find_Diff;
Type: bool;
Input: Poiner to array of sensor data, poiner to array of sensor Baseline, poiner to array for 
       output data, lenth of array;
Execution: Find differance between sensor data and Baseline for each sensor and assigns result to
           array of output data
Return: 0u if any of output data is NULL, 1u if all output data has some value
***********************************************************************************************/
bool Find_Diff(uint32_t* diff, uint32_t* baseline, uint32_t* sensor_data, uint8_t len)
{
    
    uint8 idx;
    bool Status = false;
    
    for(idx = ZERO; idx < len; idx++)
    {
        if(sensor_data[idx] >= baseline[idx])
        {
            diff[idx] = sensor_data[idx] - baseline[idx]; 
        }
        else
        {
            diff[idx] = ZERO;
        }
        
        
    }
    
    if(is_any_csd_data_empty(diff, len) == false)
    {
        
        return true; 
        
    }
    
   return Status;  
    
}
/***********************************************************************************************
Fucntoin: Find_liquid_Level;
Type: uint8_t;
Input: Poiner to array of Differance data, amount of sensors, treshold;
Execution: Find activated sensors and as a result find liquid level
Return: Liquid Level
***********************************************************************************************/
uint8_t Find_liquid_Level(uint32_t* Diff, uint8_t amount_of_sensors, uint16_t treshold)
{
    
    /* Returned variable */
    uint8_t Level = ZERO;
    
    if(Diff[FIRST_lvl] > treshold)
    {
        
        Level = 26u;
        
        if(Diff[SECOND_lvl] > treshold)
        {
            
            Level = 51u;
            
            if(Diff[THIRD_lvl] > treshold)
            {
                
                Level = 77u;
                
                if(Diff[FOURTH_lvl] > treshold)
                {
                    
                    Level = 102u;
                    
                    if(Diff[FIFTH_lvl] > treshold)
                    {
                        
                        Level = 128u;
                        
                        if(Diff[SIXTH_lvl] > treshold)
                        {
                            
                            Level = 153u;
                            
                            if(Diff[SEVENTH_lvl] > treshold)
                            {
                                
                                Level = 179u;
                                
                                if(Diff[EIGHTH_lvl] > treshold)
                                {
                                    
                                    Level = 204u;
                                    
                                    if(Diff[NINETH_lvl] > treshold)
                                    {
                                        
                                        Level = 230u;
                                        
                                        if(Diff[TENTH_lvl] > treshold)
                                        {
                                            
                                            Level = 255u;
                                            
                                        }
                                        
                                    }
                                    
                                }
                                
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    /* Another variant of algorithm **************/
    
//    uint8 idx; //loop variable
//    
//    for(idx = ZERO; idx < amount_of_sensors; idx++)
//    {
//    
//        if (Diff[idx] > treshold)
//        {
//    
//            if(idx == TENTH_lvl)
//            {
//    
//                Level = MAX_LEVEL_VALUE;  
//    
//            }
//    
//            continue;
//    
//        }
//    
//        else
//        {
//    
//            Level = idx*LEVEL_CHANGE_VALUE;
//    
//            break;
//    
//        }
//    
//        if((idx + ONE) == (amount_of_sensors))
//        {
//    
//            Level = MAX_LEVEL_VALUE; 
//    
//        }
//    
//    }
    /**********************************************/
    return Level;
    
}

/***********************************************************************************************
Fucntoin: Create_Baseline_data;
Type: void;
Input: Poiner to array of Baseline data, lenth of array, scan times, delay between scans(ms);
Execution: Assign average (10 scans with delay) RAW data from each sensor, to array of Baseline data
Return: ---------
***********************************************************************************************/

void Create_Baseline_data(uint32_t* data, uint8_t len, uint8_t scan_times)
{
    
    /*loop variable*/
    uint8 idx;
    /* Start  scan */
    CapSense_ScanAllWidgets();
    /*Start loop with "scan_times" execution*/
    for(idx = ZERO; idx < scan_times; idx++)
    {   
        
        /*"do-while" loop variable*/
        bool ret = true;
        /*Status variable*/
        bool result = false;
        /*Do untill scanning will be finished*/
        do
            {
                  
                /* Do this only when a scan is done */   
                if(CapSense_NOT_BUSY == CapSense_IsBusy()) 
                {
                    
                    /*create data array, sizeof input data array*/
                    uint32_t* ptr = (uint32_t*)malloc(sizeof(data)); // create data array
                    /* Process all widgets */
                    CapSense_ProcessAllWidgets();
                    /*Copy sensor data to created array and returns success status to variable*/
                    result = make_sensors_data(ptr, len);
                    /*Do only if sensor data is not empty*/
                    if(result == true)
                    {
                        
                        /*loop variable*/
                        uint8 arr;
                        /*Copy average sensor data to input data*/
                        for(arr = ZERO; arr < len; arr++)
                        {
                            
                            /*Find average of each sensor*/
                            data[arr] += (ptr[arr]/scan_times); 
                            
                        }
                        /*Reset "do-while" loop variable to permiss for exit from loop*/
                         ret = false;
                        /*free created array*/
                         free(ptr);
                        
                    }
                    /*When the last scan is done, we do not need next scan*/
                    if(idx == (scan_times-ONE)) 
                    {
                        
                        continue;
                        
                    }
                    /*start next scan*/
                    CapSense_ScanAllWidgets();
                    
                }
                 
            }
        while(ret == true);
          
    }
            
}

/***********************************************************************************************
Fucntoin: Create_RAW_data;
Type: bool;
Input: Poiner to array of Baseline data, lenth of array, scan times, delay between scans(ms);
Execution: Assign average  RAW data from each sensor, to array of Baseline data
Return: ---------
***********************************************************************************************/

bool Create_RAW_data(uint32_t* raw_data, uint8_t len)
{   
    
    /*function return variable*/   
     bool Status = false;
    
    /*create data array*/
    uint32_t* ptr = (uint32_t*)malloc(sizeof(raw_data));  
    
    /*copy current sensor Raw data to ptr and return result*/  
    if(true == make_sensors_data(ptr, len))/*do only if any ptr data is not empty*/
    {    
        
        /*loop variable*/
        uint8 idx;
        /*Calculate average RAW value of each sensor and copy to input data*/
        for(idx = ZERO; idx < len; idx++)
        {
            
           raw_data[idx] = ptr[idx]; 
        
        }
        Status = true;
        
    }
    /*free memory*/
    free(ptr);                                  
    return Status;
    
    }

/*******************************************************************************
* Function Name: bool IsCapSenseReadyForLowPowerMode(void)
********************************************************************************
*
* Summary:
*  Function to check if CapSense is ready to enter low power mode
*
* Parameters:
*  None
*
* Return:
*  bool     : true if ready to enter low power mode, false otherwise
*
* Side Effects:
*  None
*
*******************************************************************************/
bool  IsCapSenseReadyForLowPowerMode(void)
{
    /* Variable that stores the return flag */
    bool lowPowerModeReady;
    
    /* Don't enter low power mode if CapSense is busy with a scan */
    if(CapSense_IsBusy() != CapSense_NOT_BUSY)
    {
        
        lowPowerModeReady=false;
        
    }
    
    else
    {
        
        lowPowerModeReady=false;
        
    }
    
    /* Return  the low power mode entry readiness */
    return lowPowerModeReady;
    
}

/*******************************************************************************
* Function Name: proximity_data_t* proximity_data_t* GetProximityData(void)
********************************************************************************
* Summary:
*  Function that scans CapSense proximity sensor, processes information and then
*  returns the data
*
* Parameters:
*  None
*
* Return:
*  proximity_data_t*  : address of the data-structure that stores proximity 
*                       information
*
*******************************************************************************/
proximity_data_t* GetProximityData(void)
{
    
    /* Structure that stores the current CapSense proximity information */
    proximity_data_t  static currentProximityData = 
    {    
        
        /* Initialize the flag that track updates to proximity information */
        .proximityDataUpdated = false,
        /* Initialize the proximity information */
        .proximityData = 0u,
        
    };
        
    /* Variables used to store the instantaneous proximity information */
    uint8_t  static proximity;
    /**/
    proximity = CSD_Data.Level;
                        
//    /* Check if the proximity data has changed */
//    if (proximity != currentProximityData.proximityData)
//    {
//        
//        /* Proximity proximity position */
        currentProximityData.proximityData = proximity;
//        /* Proximity data updated */
        currentProximityData.proximityDataUpdated = true;
//        
//    }
//    else
//    { 
//        
//       /* Proximity data not updated */
//       currentProximityData.proximityDataUpdated = false; 
//        
//    }
        
    /* return the proximity information */
    return &currentProximityData;
    
}


/************************************************/
/* Initialisation of Core Callback */

static void Csd_Callback_to(void (*eventHandler)())
{
    eventHandler();
}

/* Handler which is called when timer send interrupt */
void csd_TmrInterrupt(void)
{
    /* Set timer flag */
    CSD_Data.Timer_Interrupt = true;
}


/* Handler count number of repeated states */
static void csd_StateFailedNumber(void)
{
    CSD_State.StateFailsNumber ++;
}

/* Handler reset number of repeated states */
static void csd_StateFailedReset(void)
{
    CSD_State.StateFailsNumber = ZERO;
}

/* Handler which try to avoid error if it is happend*/
static void Csd_Error(uint8_t previous_state)
{
    /* Do only if timer have sent interrupt */
    if(CSD_Data.Timer_Interrupt == true)
    {
        /* Reset timer flag */
        CSD_Data.Timer_Interrupt = false;
        /* Do only if state have repeated less then four times */
        if(CSD_State.StateFailsNumber < 4)
        {
            /* Return previous state */
            CSD_State.CurrentState = previous_state;
        }
        /* If state have repeated four times or more */
        else 
        {
            /* Reset flag */
            Csd_Callback_to(csd_StateFailedReset);
            /* Start waiting in DO_NOTHING state */
            CSD_State.CurrentState = CSD_DO_NOTHING;
        }
    }
}

/**************************************************************/
/* State handlers */
static void csd_StartScan(void)
{
    CSD_State.CurrentState = CSD_START_SCAN;
}

static void csd_CheckFinishScan(void)
{
    CSD_State.CurrentState = CSD_CHECK_FINISH_SCAN;
}



/* Handler which is called when scan is finished */
static void csd_FinishScan(void)
{
  CSD_State.CurrentState = CSD_FINISH_SCAN;
}

/* Create RAW data handler */
static void csd_CreateRawData(void)
{
    CSD_State.CurrentState = CSD_CREATE_RAW_DATA;
}



/* Handler count differance betw RAW data and BASELINE data */
static void csd_MakeDiff(void)
{
   CSD_State.CurrentState = CSD_MAKE_DIFF;
}



/* Function count liquid level */
static void csd_CountLevel(void)
{
    CSD_State.CurrentState = CSD_COUNT_LEVEL;
}

/* Handler is called to reset RAW data */
static void csd_CleanRaws(void)
{
    
    CSD_State.CurrentState = CSD_CLEAN_RAWS;
}

/* DO_NOTHING state handler */
static void csd_DoNothing(void)
{
    CSD_State.CurrentState = CSD_DO_NOTHING;
}




/* Main State Csd function */
void csd_SwitchState(void)
{
    switch(CSD_State.CurrentState)
    {
        case CSD_STATE_PAUSE:
            break;
        case CSD_START_SCAN:
            /* Reset faile flag */
            csd_StateFailedReset();
            /* Start Scan */
            CapSense_ScanAllWidgets();
            /* Change state */
            CSD_State.CurrentState = CSD_STATE_PAUSE;  
            /* Start timeout */
            timer_start(CSD_APP_CSD_START_SCAN_TIMEOUT_TMR, CSD_APP_CSD_START_SCAN_TIMEOUT_TMR_PERIOD, csd_CheckFinishScan);
            break;
            
        case CSD_CHECK_FINISH_SCAN:
            /* Do only if scan is finished */
            if(CapSense_NOT_BUSY == CapSense_IsBusy())
            {
                /* Reset faile flag */
                csd_StateFailedReset();
                /* Change state */
                CSD_State.CurrentState = CSD_STATE_PAUSE;
                /* Start timeout */
                timer_start(CSD_APP_CSD_CHECK_FINISH_SCAN_TIMEOUT_TMR, CSD_APP_CSD_CHECK_FINISH_SCAN_TIMEOUT_TMR_PERIOD, csd_FinishScan);
                
            }
            /* If scan is not finished */
            else
            {
                /* Count fail number */
                Csd_Callback_to(csd_StateFailedNumber);
                /* Start timer for CSD app with period 250ms */
                timer_start(CSD_APP, 250u, csd_TmrInterrupt);
                /* Change state to error state */
                CSD_State.CurrentState = CSD_CHECK_FINISH_SCAN_ERROR;
            }
            break;
            
        case CSD_CHECK_FINISH_SCAN_ERROR:   
            Csd_Error(CSD_CHECK_FINISH_SCAN);
            break;
            
        case CSD_FINISH_SCAN:
            /* Reset faile flag */
            csd_StateFailedReset();
            /* Process all widgets */
            CapSense_ProcessAllWidgets();
            /* Send packet header */
            TX_PutArrayBlocking((uint8 *)(&header), sizeof(header));
             /* Send packet with CapSense data */
            TX_PutArrayBlocking((uint8 *)(&CapSense_dsRam), sizeof(CapSense_dsRam));
             /* Send packet tail */
            TX_PutArrayBlocking((uint8 *)(&tail), sizeof(tail));
            /* Change state */
            CSD_State.CurrentState = CSD_STATE_PAUSE;
            /* Start timeout */
            timer_start(CSD_APP_CSD_FINISH_SCAN_TIMEOUT_TMR, CSD_APP_CSD_CHECK_FINISH_SCAN_TIMEOUT_TMR_PERIOD, csd_CreateRawData);
            
            break;
            
        case CSD_CREATE_RAW_DATA:
            if(true == Create_RAW_data(CSD_Data.Raws, MAX_SENSOR_VALUE))
            {
                /* Reset faile flag */
                csd_StateFailedReset();
                /* Change state */
                CSD_State.CurrentState = CSD_STATE_PAUSE;
                /* Start timeout */
                timer_start(CSD_APP_CSD_CREATE_RAW_DATA_TIMEOUT_TMR, CSD_APP_CSD_CREATE_RAW_DATA_TIMEOUT_TMR_PERIOD, csd_MakeDiff);
            }
            else
            {
                /* Count fail number */
                csd_StateFailedNumber();
                /* Start timer for CSD app with period 250ms */
                timer_start(CSD_APP, 100u, csd_TmrInterrupt);
                /* Change state to error state */
                CSD_State.CurrentState = CSD_CREATE_RAW_DATA_ERROR;
            }
            break;
            
        case CSD_CREATE_RAW_DATA_ERROR:
            Csd_Error(CSD_CREATE_RAW_DATA);
            break;
            
        case CSD_MAKE_DIFF:
            /* Do only if DIFF data is valid */
            Find_Diff(CSD_Data.Diff, CSD_Data.Baseline, CSD_Data.Raws, MAX_SENSOR_VALUE);
            
            /* Reset fail flag */
            csd_StateFailedReset();
            /* Change state */
            CSD_State.CurrentState = CSD_STATE_PAUSE;
            /* Start timeout */
            timer_start(CSD_APP_CSD_MAKE_DIFF_TIMEOUT_TMR, CSD_APP_CSD_MAKE_DIFF_TIMEOUT_TMR_PERIOD, csd_CountLevel);
            
//            /* If DIFF data is not valid */
//             else
//            {
//                /* Count state fail number */
//                csd_StateFailedNumber();
//                /* Start timer for CSD app and period 50 ms */
//                timer_start(CSD_APP, 100u, csd_TmrInterrupt);
//                /* Change state to error state */
//                CSD_State.CurrentState = CSD_MAKE_DIFF_ERROR;
//            }
            break;
            
        case CSD_MAKE_DIFF_ERROR:
            Csd_Error(CSD_MAKE_DIFF);
            break;
            
        case CSD_COUNT_LEVEL:
            /* Reset fail flag */
            csd_StateFailedReset();
            /* Count level */
            CSD_Data.Level = Find_liquid_Level(CSD_Data.Diff, MAX_SENSOR_VALUE, TRESHOLD);
            /* Change state */
            CSD_State.CurrentState = CSD_STATE_PAUSE;
            /* Start timeout */
            timer_start(CSD_APP_CSD_COUNT_LEVEL_TIMEOUT_TMR, CSD_APP_CSD_COUNT_LEVEL_TIMEOUT_TMR_PERIOD, csd_CleanRaws);
            break;
            
        case CSD_CLEAN_RAWS:
            /* Reset fail flag */
            csd_StateFailedReset();
            /* Write ZERO to RAW data */
            clean_data(CSD_Data.Raws, sizeof(CSD_Data.Raws),  MAX_SENSOR_VALUE);
            /* Change state */
            CSD_State.CurrentState = CSD_STATE_PAUSE;
            /* Start timeout */
            timer_start(CSD_APP_CSD_CLEAN_RAWS_TIMEOUT_TMR, CSD_APP_CSD_CLEAN_RAWS_TIMEOUT_TMR_PERIOD, csd_DoNothing);
            
            break;
            
        case CSD_DO_NOTHING:
            /* Reset fail flag */
            csd_StateFailedReset();
            /* Start timer for CSD app and period 50 ms */
            timer_start(CSD_APP, 50u, csd_TmrInterrupt);
            /* Change state on FINISH_DO_NOTHING */
            CSD_State.CurrentState = CSD_FINISH_DO_NOTHING;
            
            break;
            
        case CSD_FINISH_DO_NOTHING:
              /* Do only if timer have sent interrupt */
            if(CSD_Data.Timer_Interrupt == true)
            {
                /* Count DO_NOTHING state times */
                CSD_State.DoNothingTimes ++;
                /* Reset timer interrupt */
                CSD_Data.Timer_Interrupt = false;
                /* Do only if CSD app do nothing too long */
                if(CSD_State.DoNothingTimes > DO_NOTHING_TIMES)
                {
                    /* Do only if device is not scanning */
                    if(CapSense_NOT_BUSY == CapSense_IsBusy())
                    {
                        /* Set new state */
                        csd_StartScan();
                        CSD_State.DoNothingTimes = ZERO;
                        break;
                    }
                    /* If device still scanning */
                    else
                    {
                        /* Call restart system */
                        core_RestartSystem();
                        break;
                    } 
                }
                /* If CSD app do nothing too short */
                else
                {
                    /* Return to DO_NOTHING state */
                    CSD_State.CurrentState = CSD_DO_NOTHING;
                    break;
                }
            }
            else
            {
                break;
            }
            
            
        default:
            CSD_State.CurrentState = CSD_DO_NOTHING;
            break;
    }
}



/* [] END OF FILE */
