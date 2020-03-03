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
#include "APP.h"
#include "CapSense_config_u.h"
#include "flash_config_u.h"
#include <stdlib.h>
#include <string.h>
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
void READ_FLASH(void)
{  
   
    Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, Baseline, MAX_SENSOR_VALUE);
  
}

/* [] END OF FILE */