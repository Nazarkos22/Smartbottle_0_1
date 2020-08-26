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
#include "ble_application.h"
#include "timers_counters.h"
#include <stdlib.h>
#include <string.h>

/* Initialization of structure with all sensor and baseline data */
U_csd_data_t CSD_data; 
/* initialization of structure with all flash data */
U_flash_data_t FLASH_data; 
/* Initialisation of structure with timer flags */
Timer_parametr_t Timers_data[TIMER_MAX_NUMBER];


/* Set some flags for start scan */
void Set_Flags(void)
{
    
    CSD_data.ReadyForNewScan_flag = true ;
    
    CSD_data.TimerIntFlag = true;
    
}



/*  */
void Timers_Interrupts_Init(void)
{
    
    Tmr_Int_1_Init();
    
    Tmr_Int_2_Init();

    Tmr_Int_3_Init();

    Tmr_Int_4_Init();

    Tmr_Int_5_Init();
   
}
void Tmr_Int_1_Handler(void)
{
    
    /* Set timer flag */
    //CSD_data.TimerIntFlag = true;
    Timers_data[0u].Timer_Status = Timer_free;
    Timers_data[0u].Timer_Status_Changed_to_free = true;
    /* Clear timer interrupt */
    Timer_1_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_2_Handler(void)
{
    
    /* Set timer flag */
    //CSD_data.TimerIntFlag = true;
    Timers_data[1u].Timer_Status = Timer_free;
    Timers_data[1u].Timer_Status_Changed_to_free = true;
    /* Clear timer interrupt */
    Timer_2_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_3_Handler(void)
{
    
    /* Set timer flag */
    //CSD_data.TimerIntFlag = true;
    Timers_data[2u].Timer_Status = Timer_free;
    Timers_data[2u].Timer_Status_Changed_to_free = true;
    /* Clear timer interrupt */
    Timer_3_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_4_Handler(void)
{
    
    /* Set timer flag */
    //CSD_data.TimerIntFlag = true;
    Timers_data[3u].Timer_Status = Timer_free;
    Timers_data[3u].Timer_Status_Changed_to_free = true;
    /* Clear timer interrupt */
    Timer_4_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_5_Handler(void)
{
    
    /* Set timer flag */
    //CSD_data.TimerIntFlag = true;
    Timers_data[4u].Timer_Status = Timer_free;
    Timers_data[4u].Timer_Status_Changed_to_free = true;
    /* Clear timer interrupt */
    Timer_5_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}
/***************************************************************************
Function: void CapSense_Processing(void)
Execution: 1. Scan sensors
           2. Send result of scan to array of data
           3. Find differance between each sensor data and its baseline data
           4. Find what sensors are active and as a result find liquid level
****************************************************************************/
void CapSense_Processing(uint8_t scan_times)
{
    if((CSD_data.ReadyForNewScan_flag == true) && (CSD_data.TimerIntFlag == true))
    {
        
        /* Start next scan */
        CapSense_ScanAllWidgets();
        /* Reset flag */
        CSD_data.ReadyForNewScan_flag = false;
        /* Reset flag */
        CSD_data.TimerIntFlag = false;
        /* Reset flag */
        CSD_data.HaveScanResult = false;
        /* Reset counter */
        CSD_data.counter = ZERO;
        /* Write ZERO in Raw data */
        clean_data(CSD_data.Raws, sizeof(CSD_data.Raws),  MAX_SENSOR_VALUE);
        
    }
    /* Do only if we do not have scan result */
    if(CSD_data.HaveScanResult == false)
    {
        
        /* Do this only when a scan is done */
        if(CapSense_NOT_BUSY == CapSense_IsBusy()) 
        {
            /* Create variable flag */
            bool Create_RAW_data_Status = false;
            /* Process all widgets */
            CapSense_ProcessAllWidgets();
            /* Form average sensor data in real time and return flag */
            Create_RAW_data_Status = Create_RAW_data(CSD_data.Raws, MAX_SENSOR_VALUE, scan_times);
            /* Do only if Raw data is formed*/
            if(Create_RAW_data_Status == true)
            {
                
                /* Count scan times */
                CSD_data.counter++;
                
            }
            /*Do only if last scan is in process*/
            if(CSD_data.counter == scan_times)
            {   
                
                /* Status variable */
                bool Diff_Status = false;
                /* Find differance between RAWs and Baseline and return status */
                Diff_Status = Find_Diff(CSD_data.Diff, CSD_data.Baseline, CSD_data.Raws, MAX_SENSOR_VALUE);
                /* Do only if any diff data is not ZERO */
                if(Diff_Status == true)
                {
                    
                    /* Find level of active sensors */
                    CSD_data.Level = Find_liquid_Level(CSD_data.Diff, MAX_SENSOR_VALUE, TRESHOLD);
                    /* Allow to start next cycle of scans(will reset from timer/counter in next iterations) */
                    CSD_data.ReadyForNewScan_flag = true;
                    /* Set flag */
                    CSD_data.HaveScanResult = true;
                    /* Write ZERO in Temporary Baseline */
                    clean_data(CSD_data.Raws, sizeof(CSD_data.Raws),  MAX_SENSOR_VALUE);
                    /* Start timer */
                    Start_Free_Timer(Which_Timer_Free(TIMER_MAX_NUMBER,Timers_data), PERIOD, Timers_data);
                        
                }
                
            }
            /* Do not start next scan if last scan is done */
            if(CSD_data.counter < scan_times)
            {
                
                /* Start next scan */
                CapSense_ScanAllWidgets();
                
            }
            
        }
        
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
void Flash_Scan(void)
{  
    
    /* Scan Flah memory data and return status flag */
    FLASH_data.Baseline_Read_Status = Read_Flash_Baseline(FLASH_ADDR, CSD_data.Baseline, MAX_SENSOR_VALUE, sizeof(U_cfg_t)); 
    /* Do only if scanned Flash data is invalid */
    if(FLASH_data.Baseline_Read_Status == false)
    {
        
        /* Form baseline by scanning some amount of times with delay */
        Create_Baseline_data(CSD_data.Baseline, MAX_SENSOR_VALUE, BASELINE_SCAN_TIMES); 
        /* Form array data with Baseline data and checksum */
        make_data_for_flash(FLASH_data.flash_data, CSD_data.Baseline, MAX_SENSOR_VALUE);
        /* Eraze Flash memory size of Baseline data plus checksum */
        eraze_flash_data(FLASH_ADDR, sizeof(U_cfg_t));
        /* Write on Flash memory Baseline and checksum */
        Cy_Flash_WriteRow(FLASH_ADDR, FLASH_data.flash_data); 
        /* RESET function*/
        __NVIC_SystemReset() ;   
        
    }
    
}


/*******************************************************************************
* Function Name: proximity_data_t* proximity_data_t* GetProximityData(void)
********************************************************************************
* Summary:
*  Function that scans CapSense proximity sensor, processes information and then
*  returns the data
*
* Parameters:
*  None
*
* Return:
*  proximity_data_t*  : address of the data-structure that stores proximity 
*                       information
*
*******************************************************************************/
proximity_data_t* GetProximityData(void)
{
    
    /* Structure that stores the current CapSense proximity information */
    proximity_data_t  static currentProximityData = 
    {    
        
        /* Initialize the flag that track updates to proximity information */
        .proximityDataUpdated = false,
        /* Initialize the proximity information */
        .proximityData = 0u,
        
    };
        
    /* Variables used to store the instantaneous proximity information */
    uint8_t  static proximity;
    /**/
    proximity = CSD_data.Level;
                        
    /* Check if the proximity data has changed */
    if (proximity != currentProximityData.proximityData)
    {
        
        /* Proximity proximity position */
        currentProximityData.proximityData = proximity;
        /* Proximity data updated */
        currentProximityData.proximityDataUpdated = true;
        
    }
    else
    { 
        
       /* Proximity data not updated */
       currentProximityData.proximityDataUpdated = false; 
        
    }
        
    /* return the proximity information */
    return &currentProximityData;
    
}
