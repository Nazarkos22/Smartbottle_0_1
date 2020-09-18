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
    
#define MAX_LEVEL_VALUE (255u)
#define LEVEL_CHANGE_VALUE (25u)
    
#define TRESHOLD (1000u)

    
/* Structure of all CapSense data */
typedef struct
{
    
    /* Array of sensors data */ 
    uint32_t Raws[MAX_SENSOR_VALUE];
    /* Array of differance between Baseline and Raws */
    uint32_t Diff[MAX_SENSOR_VALUE];
    /* Array of Baseline data */
    uint32_t Baseline[MAX_SENSOR_VALUE];
    /* Data for exchange with Flash */
    uint32_t Exchange_data[EXCHANGE_DATA_NUMBER];
    /* Checksum for validating exchanged data */
    uint32_t Checksum;
    /* Liquid level */
    uint8_t Level;
    /* Store number of scans */
    uint8_t counter;
    /* Set this flag when cycle of scans is done */
    bool ReadyForNewScan_flag;
    /* Set this flag when timer send inerrupt*/
    bool TimerIntFlag;
    /* Set this flag when Level calculated */
    bool HaveScanResult;
    /* (NOT DONE YET!) Set this flag when BLE starts advertisment */
    bool StartAdvert;
    /* Register change of StartAdvert flag */
    bool SetFlagsForStartScan_Status;
    /* Flag, which becomes true when BLE device is connected */
    bool Allow_Start_Scan;
  
}   U_csd_data_t;

typedef struct
{
    /* Current CSD State */
    uint8_t CurrentState;
    uint8_t NextState;
    uint8_t PreviousState;
}U_Csd_State_t;

/*  */
typedef enum
{
    SCAN_FOR_FLASH,
    VALIDATE_DATA,
    CSD_ALLOW_SCAN,
    CSD_START_SCAN,
    CSD_FINISH_SCAN,
    LEVEL_START_COUNT,
    LEVEL_FINISH_COUNT,
    CSD_DO_NOTHING
    
}CSD_States_t;
   
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


/* Function that processes information and then
   returns the data */
proximity_data_t* GetProximityData(void);

/* Function to check if CapSense is ready to enter low power mode */
bool  IsCapSenseReadyForLowPowerMode(void);
   
/* Function to write ZERO in data */
bool clean_data(uint32_t* data, size_t size, uint8 len);

/* Function to process sensor data after scanning */
bool Create_RAW_data(uint32_t* raw_data, uint8_t len, uint8_t scan_times);

/* Function to create baseline of sensor data by calculating average of some 
 * amount of scans before write on flash */
void Create_Baseline_data(uint32_t* data, uint8_t len, uint8_t scan_times);

/* Function to calculate differance between sensor data and baseline */
bool Find_Diff(uint32_t* diff, uint32_t* baseline, uint32_t* sensor_data, uint8_t len);

/* Function to check if any data equal NULL(true) or NOT(false) */
bool is_any_csd_data_empty(uint32_t* data, uint8 len);

/* Function save data(raw counts) from CapSense widgets to array of your data */
bool make_sensors_data(uint32_t* data, uint8 len);

/* Function checks which of sensors are activated and return Level(0-255u) */
uint8_t Find_liquid_Level(uint32_t* Diff, uint8_t amount_of_sensors, uint16_t treshold);
/* Declaration callbacks */
void core_CsdAllowScan(void);
void csd_ScanForFlash(void);
void csd_StartScan(void);
void csd_CoreStartScan(void);
void csd_CoreFinishScan(void);
void csd_CoreStartLevelCount(void);
void csd_CoreFinishLevelCount(void);
void csd_CoreTmrStart(void);
/***************************/



 #endif
/* [] END OF FILE */
