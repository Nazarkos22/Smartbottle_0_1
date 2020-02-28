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
    
typedef struct
{
    uint32_t Data[MAX_SENSOR_VALUE];
}U_config_t;
    uint32_t Sensors[MAX_SENSOR_VALUE];// array from sensors data
    uint32_t Level;
  #endif 
/* [] END OF FILE */
