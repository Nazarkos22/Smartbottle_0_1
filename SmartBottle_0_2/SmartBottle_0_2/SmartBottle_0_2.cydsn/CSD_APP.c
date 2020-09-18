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
#include <stdlib.h>
#include <string.h>

/* Initialization of structure with all sensor and baseline data */
U_csd_data_t CSD_Data; 
/* Initialisation of CSD current state data */
U_Csd_State_t CSD_State;


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
        
        diff[idx] = sensor_data[idx] - baseline[idx]; 
        
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
    /* Another variant of algorithm **************
    
    uint8 idx; //loop variable
    
    for(idx = ZERO; idx < amount_of_sensors; idx++)
    {
    
        if (Diff[idx] > treshold)
        {
    
            if(idx == TENTH_lvl)
            {
    
                Level = MAX_LEVEL_VALUE;  
    
            }
    
            continue;
    
        }
    
        else
        {
    
            Level = idx*LEVEL_CHANGE_VALUE;
    
            break;
    
        }
    
        if((idx + ONE) == (amount_of_sensors))
        {
    
            Level = MAX_LEVEL_VALUE; 
    
        }
    
    }
    **********************************************/
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

bool Create_RAW_data(uint32_t* raw_data, uint8_t len, uint8_t scan_times)
{   
    
    /*function return variable*/   
     bool Status = false;
    /*Raw success variable*/
     bool result = false;
    /*create data array*/
    uint32_t* ptr = (uint32_t*)malloc(sizeof(raw_data));  
    /*copy current sensor Raw data to ptr and return result*/
    result = make_sensors_data(ptr, len);
    
    if(result == true)/*do only if any ptr data is not empty*/
    {    
        
        /*loop variable*/
        uint8 idx;
        /*Calculate average RAW value of each sensor and copy to input data*/
        for(idx = ZERO; idx < len; idx++)
        {
            
           raw_data[idx] += (ptr[idx]/scan_times); 
        
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
                        
    /* Check if the proximity data has changed */
    if (proximity != currentProximityData.proximityData)
    {
        
        /* Proximity proximity position */
        currentProximityData.proximityData = proximity;
        /* Proximity data updated */
        currentProximityData.proximityDataUpdated = true;
        
    }
    else
    { 
        
       /* Proximity data not updated */
       currentProximityData.proximityDataUpdated = false; 
        
    }
        
    /* return the proximity information */
    return &currentProximityData;
    
}


/************************************************/
/* Initialisation of Core Callback */

static void Csd_Callback_to(void (*eventHandler)())
{
    eventHandler();
}

static uint8_t which_next_CsdState(uint8_t currstate)
{
    switch(currstate)
    {
        case 
    }
}

static void CSD_ChangeState(void)
{
    CSD_State.CurrentState = CSD_State.NextState;
}

/************************************************/
/************************************************/


void csd_ScanForFlash(void)
{
    CSD_State.CurrentState = SCAN_FOR_FLASH;
}

void core_CsdAllowScan(void)
{
    CSD_State.CurrentState = CSD_ALLOW_SCAN;
}

void CSD_Process(void)
{
    /* Goes into only if BLE is in connected state */
    if(CSD_Data.Allow_Start_Scan == true)
    {
        CapSense_ScanAllWidgets();
        /* Reset permition flag to avoid Starting new scan untill previous has not finished */
        CSD_Data.Allow_Start_Scan = false;
        /* Core Callback that scanning process has started */
        Csd_Callback_to(csd_StartScan);  
    }
    /* Goes into only if scan is finished */
    if(()&&(CapSense_NOT_BUSY == CapSense_IsBusy()))
    {
        /* Process all widgets */
        CapSense_ProcessAllWidgets();
        /* Core Callback that scanning process has finished */
        Csd_Callback_to(csd_FinishScan);
    }
}

/*  */
void Switch_CSD_State(void)
{
    switch(CSD_Data.CurrentState)
    {
        case SCAN_FOR_FLASH:
            CSD_Data.Allow_Start_Scan = false;
            /* Change state function */
            break;
        case CSD_ALLOW_SCAN:
            CSD_Data.Allow_Start_Scan = true;
            break;
        default:
            break;
    }
}



/* [] END OF FILE */
