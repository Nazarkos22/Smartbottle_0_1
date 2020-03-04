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
#include "CapSense_config_u.h"
#include <stdlib.h>
#include <string.h>

bool is_any_sensor_data_empty(uint32_t* data, uint8 len)
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
uint8_t make_sensors_data(uint32_t* data, uint8 len)
{
    uint8 Status = ZERO;
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
    if(is_any_sensor_data_empty(data, len) == false)
    {
        Status = GOOD;
    }
    return Status;
}
uint32_t* Craete_Baseline_data_from_Sensors(uint8_t len)
{
    uint8_t Status = ZERO;
    
        uint32_t Average[len];
         uint8 idx;
        //**********************************************************
        uint32_t* ptr = (uint32_t*)malloc(sizeof(U_csd_config_t)); // create data array
      
        //**********************************************************
        for(idx = ZERO; idx < len; idx++)
        {
            bool ret = true;
            uint8_t result = ZERO;
            do
                {
                      CapSense_ScanAllWidgets(); /* Start  scan */
                       
                      if(CapSense_NOT_BUSY == CapSense_IsBusy()) /* Do this only when a scan is done */
                       {
                         CapSense_ProcessAllWidgets(); /* Process all widgets */
                        result = make_sensors_data(ptr, MAX_SENSOR_VALUE);
                        if(result == GOOD)
                        {
                            uint8 arr;
                            for(arr = ZERO; arr < len; arr++)
                            {
                               Average[arr]+= (ptr[arr]/len); 
                            }
                             ret = false;
                        }
                       }
                     
             }
            while(ret == true);
            
           // call delay(1000ms)
            
        }
        
     return Average;
    }
/* [] END OF FILE */
