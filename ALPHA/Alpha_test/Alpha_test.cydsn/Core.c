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
#include "CapSense_Process.h"
#include "Flash_Process.h"
#include <stdlib.h>
#include <string.h>

U_flash_flag_t flag;
U_csd_data_t CSD_data;
U_flash_data_t FLASH_data;


void Flash_Processing(void)
{  
    
   
     flag.Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, CSD_data.Baseline, MAX_SENSOR_VALUE);
     if(flag.Baseline_Read_Status == false)
    {    
      Craete_Baseline_data_from_Sensors(CSD_data.Baseline, MAX_SENSOR_VALUE);
      make_data_for_flash(FLASH_data.flash_data, CSD_data.Baseline, MAX_SENSOR_VALUE);
      eraze_flash_data(FLASH_ADDR);
      Cy_Flash_WriteRow(FLASH_ADDR, FLASH_data.flash_data);
     // Cy_SysResetCM4();
    }
}

/* [] END OF FILE */