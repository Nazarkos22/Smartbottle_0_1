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
#ifndef __CORE_H_
    #define __CORE_H_
#include "project.h"
#include "Config_u.h"
    
    
typedef struct
{
    uint32_t raw[MAX_SENSOR_VALUE];
    uint32_t baseline[MAX_SENSOR_VALUE];
    uint32_t diff[MAX_SENSOR_VALUE];
    uint8_t err_flag;
    
}app_t;
    
    void READ_FLASH(void);
    void Start_Interrapts(void);
    void CSD_Config(void);// make all processes with CapSense
    void FLASH_Config(void);
/* [] END OF FILE */
 #endif