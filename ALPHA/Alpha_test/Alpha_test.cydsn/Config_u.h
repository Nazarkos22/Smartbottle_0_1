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
#ifndef _CONFIG_U_H_   
#define _CONFIG_U_H_
#include "project.h"

#define MAX_SENSOR_VALUE (10u)
#define ZERO (0u)
#define GOOD (1u)    
typedef struct
{
    uint32_t Data[MAX_SENSOR_VALUE];
}U_config_t;
    bool Baseline_Read_Status;
    
    uint32_t Baseline[MAX_SENSOR_VALUE];//array of baseline data
    uint32_t Level;// variable, which recieves returned data from fuction "uint32_t Find_Liquid_Level(uint32_t* data, uint32_t ADDR)"
  #endif 
/* [] END OF FILE */
