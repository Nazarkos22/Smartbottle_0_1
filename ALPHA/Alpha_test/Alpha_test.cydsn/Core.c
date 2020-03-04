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

app_t app;

void Start_Interrapts(void)
{
   __enable_irq(); /* Enable global interrupts. */


  CapSense_Start();
 
}

void CSD_Config(void)
{
    bool ret = true;
    
    do{
  CapSense_ScanAllWidgets(); /* Start next scan */
    /* Do this only when a scan is done */
 if(CapSense_NOT_BUSY == CapSense_IsBusy())
   {
     CapSense_ProcessAllWidgets(); /* Process all widgets */
    
    }
 
     }while(ret == true);
}
void Flash_Processing(void)
{  
    
   
     app.Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, app.baseline, MAX_SENSOR_VALUE);
     if(app.Baseline_Read_Status == false)
    {    
      memcpy(app.baseline, Craete_Baseline_data_from_Sensors(MAX_SENSOR_VALUE), sizeof(app.baseline));//copy
      eraze_flash_data(FLASH_ADDR);
      Cy_Flash_WriteRow(FLASH_ADDR, make_data_for_flash(app.baseline, MAX_SENSOR_VALUE));
     // Cy_SysResetCM4();
    }
}

/* [] END OF FILE */