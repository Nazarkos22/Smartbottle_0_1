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
   
    

  #endif 
/* [] END OF FILE */
