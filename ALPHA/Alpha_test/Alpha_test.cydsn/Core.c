/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
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

U_flash_flag_t flag; //initialization of structure with Baseline_Read_Status flag
U_csd_data_t CSD_data;  //initialization of structure with all sensor and baseline data
U_flash_data_t FLASH_data; //initialization of structure with data, which will be write on flash

/***************************************************************************
Function: void CapSense_Processing(void)
Execution: 1. Scan sensors
           2. Send result of scan to array of data
           3. Find differance between each sensor data and its baseline data
           4. Find what sensors are active and as a result find liquid level
****************************************************************************/
void CapSense_Processing(void)
{
   Create_RAW_data_from_Sensors(CSD_data.Raws, MAX_SENSOR_VALUE, RAW_SCAN_TIMES, RAW_DELAY);  // Form average sensor data in real time
   if(Find_Diff(CSD_data.Raws, CSD_data.Baseline, CSD_data.Diff, MAX_SENSOR_VALUE) == GOOD)// Do only if there is not any NULL Diff
{
    CSD_data.Level = Find_liquid_Level(CSD_data.Diff, MAX_SENSOR_VALUE, TRESHOLD); // Find level of active sensors
}
   
}


/***************************************************************************
Function: void Flash_Processing(void)
Execution: 1. Check Flash Memory with some address, is it "empty" or not
              ("empty" means that it can be not only NULL data, it can be some
              data, in which checksum does not verify)
************************!!!IF DATA IS NOT "EMPTY"!!!************************
           2. Copy data to Baseline array

************************!!!IF DATA IS "EMPTY"!!!****************************
           2. Form Baseline data from sensors, by scanning 10 times with some
              delay and average data from all sensors
           3. Get checksum 
           4. Eraze Flash memory with some address sizeof Baseline data plus checksum
           5. Write Baseline data and checksum on Flash memory with that address
           6. Reset
****************************************************************************/
void Flash_Processing(void)
{  
    
   
     flag.Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, CSD_data.Baseline, MAX_SENSOR_VALUE);// Scan Flah memory data
     if(flag.Baseline_Read_Status == false) // When scanned Flash memory is "empty"
    {    
      Create_Baseline_data_from_Sensors(CSD_data.Baseline, MAX_SENSOR_VALUE, BASELINE_SCAN_TIMES, BASELINE_DELAY); // Form baseline by scanning 10 times with delay
      make_data_for_flash(FLASH_data.flash_data, CSD_data.Baseline, MAX_SENSOR_VALUE);// Form array data with Baseline data and checksum
      eraze_flash_data(FLASH_ADDR); //Eraze Flash memory sizeof Baseline data plus checksum
      Cy_Flash_WriteRow(FLASH_ADDR, FLASH_data.flash_data); //Write on Flash memory Baseline and checksum
       //Cy_SysResetCM4();   //Reset(does not work yet)
    }
}

/* [] END OF FILE */