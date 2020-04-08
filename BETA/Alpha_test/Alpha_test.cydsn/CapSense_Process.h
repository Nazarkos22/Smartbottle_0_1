/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/

#ifndef __CAPSENSE_PROCESS_H_
#define __CAPSENSE_PROCESS_H_
#include "project.h"
#include "Config_u.h"
    
    #define FIRST_lvl (0u)
    #define SECOND_lvl (1u)
    #define THIRD_lvl (2u)
    #define FOURTH_lvl (3u)
    #define FIFTH_lvl (4u)
    #define SIXTH_lvl (5u)
    #define SEVENTH_lvl (6u)
    #define EIGHTH_lvl (7u)
    #define NINETH_lvl (8u)
    #define TENTH_lvl (9u)
    #define MAX_LEVEL_VALUE (250u)
    #define TRESHOLD (1000u)// A change of CapSense count raws, which activates sensor
    #define LEVEL_CHANGE_VALUE (25u)
    #define BASELINE_DELAY (1000u)
    #define RAW_DELAY (100u)
    #define RAW_SCAN_TIMES (7u)
    #define BASELINE_SCAN_TIMES (10u)
    
    
    typedef struct
    {
       uint32_t Raws[MAX_SENSOR_VALUE];// array of sensors data
       uint32_t Diff[MAX_SENSOR_VALUE];// array of differance between Baseline and Raws
       uint32_t Baseline[MAX_SENSOR_VALUE];// array of Baseline data
       uint8_t Level;// liquid level
    }U_csd_data_t;
    /* Data length of CapSense proximity */
#define CAPSENSE_PROXIMITY_DATA_LEN    (uint8_t) (0x01u)

/* Data-type for storing CapSense proximity information */    
typedef struct
{
    /* Flags that track changes to CapSense data */
    bool proximityDataUpdated;
    /* Proximity and button data field */
    uint8_t  proximityData;
}   proximity_data_t;

/* Function that initializes the CapSense */    
void InitCapSense(void);

/* Function that scans CapSense proximity sensor, processes information and then
   returns the data */
proximity_data_t* GetProximityData(void);

/* Function to check if CapSense is ready to enter low power mode */
bool  IsCapSenseReadyForLowPowerMode(void);


    
    

    
    void Create_Baseline_data(uint32_t* data, uint8_t len, uint8_t scan_times, uint16_t delay);
    
    uint8_t Find_Diff(uint32_t* sensor_data, uint32_t* baseline, uint32_t* receive_data, uint8_t len);
    
    bool is_any_csd_data_empty(uint32_t* data, uint8 len);//function checks is senors data equal NULL(true) or NOT(false)
    
    uint8_t make_sensors_data(uint32_t* data, uint8 len);//function save data(raw counts) from CapSense widgets to array of your data
    
    uint8_t Find_liquid_Level(uint32_t* Diff, uint8_t amount_of_sensors, uint16_t treshold);// function checks which of sensors are activated and return Level(0-250u)
 #endif
/* [] END OF FILE */
