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
void make_sensors_data(void)
{
    Sensors[FIRST_lvl] = CapSense_BUTTON0_SNS0_RAW0_VALUE;
    Sensors[SECOND_lvl] = CapSense_BUTTON1_SNS0_RAW0_VALUE;
    Sensors[THIRD_lvl]= CapSense_BUTTON2_SNS0_RAW0_VALUE;
    Sensors[FOURTH_lvl]= CapSense_BUTTON3_SNS0_RAW0_VALUE;
    Sensors[FIFTH_lvl]= CapSense_BUTTON4_SNS0_RAW0_VALUE;
    Sensors[SIXTH_lvl]= CapSense_BUTTON5_SNS0_RAW0_VALUE;
    Sensors[SEVENTH_lvl]= CapSense_BUTTON6_SNS0_RAW0_VALUE;
    Sensors[EIGHTH_lvl]= CapSense_BUTTON7_SNS0_RAW0_VALUE;
    Sensors[NINETH_lvl]= CapSense_BUTTON8_SNS0_RAW0_VALUE;
    Sensors[TENTH_lvl]= CapSense_BUTTON9_SNS0_RAW0_VALUE;
}
uint32_t Find_Liquid_Level(uint32_t* data, uint32_t ADDR)
{
    uint32_t Level = ZERO;
    uint32_t DIFF[MAX_SENSOR_VALUE];
    uint32_t* array = (uint32_t*)ADDR;
    uint8 idx;
    for(idx = ZERO; idx<MAX_SENSOR_VALUE; idx++)
    {
       DIFF[idx] = data[idx]-array[idx];
      
       if((DIFF[idx] > TRESHOLD)|| (DIFF[idx] == TRESHOLD))
    {
        Level = idx * 25u;
        continue;
    }
    else
    {
        break;
    }
    
    }
    free(array);
    return Level;
}
/* [] END OF FILE */
