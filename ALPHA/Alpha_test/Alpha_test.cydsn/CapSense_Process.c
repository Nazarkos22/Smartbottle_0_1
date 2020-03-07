/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#include "project.h"
#include "Config_u.h"
#include "CapSense_Process.h"
#include <stdlib.h>
#include <string.h>


/***********************************************************************************************
Fucntoin: is_any_data_empty
Type: Bool
Input: Poiner to array of data, lenth of array
Execution: Function checks, is your array has at least one NULL data
Return: If your array has at least one NULL data, function returns TRUE, Else - FALSE
***********************************************************************************************/
bool is_any_csd_data_empty(uint32_t* data, uint8 len)
{
    bool ret = false;
 uint8 idx;
    for(idx = ZERO; idx < len; idx++)
    {
      if(data[idx] == ZERO)
    {
        ret = true;
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
uint8_t make_sensors_data(uint32_t* data, uint8 len)
{
    uint8_t Status = ZERO;
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
        Status = GOOD;
    }
    return Status;
}
/***********************************************************************************************
Fucntoin: Find_Diff;
Type: uint8_t;
Input: Poiner to array of sensor data, poiner to array of sensor Baseline, poiner to array for 
       output data, lenth of array;
Execution: Find differance between sensor data and Baseline for each sensor and assigns result to
           array of output data
Return: 0u if any of output data is NULL, 1u if all output data has some value
***********************************************************************************************/
uint8_t Find_Diff(uint32_t* diff, uint32_t* baseline, uint32_t* sensor_data, uint8_t len)
{
 uint8 idx, Status = ZERO;
    for(idx = ZERO; idx < len; idx++)
    {
     diff[idx] = sensor_data[idx] - baseline[idx];  
    }
    if(is_any_csd_data_empty(diff, len) == false)
    {
     Status = GOOD;   
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
uint8_t Find_liquid_Level(uint32_t* Diff, uint8_t amount_of_sensors, uint8_t treshold)
{
 uint8_t Level = ZERO;//returned variable
    uint8 idx; //loop variable
    
    for(idx = ZERO; idx < amount_of_sensors; idx++)
    {
        if (Diff[idx] < treshold)
        {
         Level = (idx)*LEVEL_CHANGE_VALUE;
         break;
        }
        if((idx + ONE) == (amount_of_sensors))
        {
         Level = MAX_LEVEL_VALUE;   
        }
    }
    return Level;
}
/***********************************************************************************************
Fucntoin: Create_RAW_data_from_Sensors;
Type: void;
Input: Poiner to array of Sensor RAW data, lenth of array, scan times, delay between scans;
Execution: Assign average (10 scans with delay) RAW data from each sensor, to array of Sensor RAW data
Return: ---------
***********************************************************************************************/
void Create_RAW_data_from_Sensors(uint32_t* data, uint8_t len, uint8_t scan_times, uint16_t delay)
{
         uint8 idx; //loop variable
        /**********************************************************/
    
        uint32_t* ptr = (uint32_t*)malloc(sizeof(U_config_t));        // create data array

        /**********************************************************/
        CapSense_ScanAllWidgets(); /* Start  scan */
        for(idx = ZERO; idx < scan_times; idx++)
        {
            bool ret = true;
            uint8_t result = ZERO;
            do
                {
                      
                       
                      if(CapSense_NOT_BUSY == CapSense_IsBusy()) /* Do this only when a scan is done */
                       {
                         CapSense_ProcessAllWidgets(); /* Process all widgets */
                        result = make_sensors_data(ptr, len);
                        if(result == GOOD)
                        {
                            uint8 arr; //loop variable
                            for(arr = ZERO; arr < scan_times; arr++)
                            {
                               data[arr] += (ptr[arr]/scan_times); 
                            }
                             ret = false;
                        }
                        if(idx == (scan_times-ONE))// When the last scan is done, we do not need next scan
                        {
                            continue;
                        }
                        CapSense_ScanAllWidgets();//start next scan
                       }
                     
             }
            while(ret == true);
            
Cy_SysLib_Delay(delay);//      call delay(100ms)
            
        }
        free(ptr);
     
    }
/***********************************************************************************************
Fucntoin: Create_RAW_data_from_Sensors;
Type: void;
Input: Poiner to array of Baseline data, lenth of array, scan times, delay between scans;
Execution: Assign average (10 scans with delay) RAW data from each sensor, to array of Baseline data
Return: ---------
***********************************************************************************************/
void Create_Baseline_data_from_Sensors(uint32_t* data, uint8_t len, uint8_t scan_times, uint16_t delay)
{
 
    
        
         uint8 idx;//loop variable
        //**********************************************************
        uint32_t* ptr = (uint32_t*)malloc(sizeof(U_config_t)); // create data array

        //**********************************************************
        CapSense_ScanAllWidgets(); /* Start  scan */
        for(idx = ZERO; idx < scan_times; idx++)
        {
            bool ret = true;
            uint8_t result = ZERO;
            do
                {
                      
                       
                      if(CapSense_NOT_BUSY == CapSense_IsBusy()) /* Do this only when a scan is done */
                       {
                         CapSense_ProcessAllWidgets(); /* Process all widgets */
                        result = make_sensors_data(ptr, len);
                        if(result == GOOD)
                        {
                            uint8 arr;//loop variable
                            for(arr = ZERO; arr < scan_times; arr++)
                            {
                               data[arr] += (ptr[arr]/scan_times); // Find average of each sensor
                            }
                             ret = false;
                        }
                        if(idx == (scan_times-ONE))// When the last scan is done, we do not need next scan
                        {
                            continue;
                        }
                        CapSense_ScanAllWidgets();//start next scan
                       }
                     
             }
            while(ret == true);
            
        Cy_SysLib_Delay(delay);// call delay(1000ms)
            
        }
        free(ptr);
     
    }
/* [] END OF FILE */
