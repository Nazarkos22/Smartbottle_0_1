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
     make_sensors_data();
     Level = Find_Liquid_Level(Sensors, FLASH_ADDR);
     ret = false;
    }
 
     }while(ret == true);
}
void FLASH_Config(void)
{  
   
    bool Status_u;
    Status_u = is_writen_config();
   if(Status_u == false)
{
    eraze_flash_data();
    make_data_for_flash(Sensors);
    Cy_Flash_WriteRow(FLASH_ADDR, flash);
   
}
else
{
    
}

}
/* [] END OF FILE */