/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#ifndef _CONFIG_U_H_   
#define _CONFIG_U_H_
#include "project.h"

#define MAX_SENSOR_VALUE (10u)
#define ZERO (0u)
#define GOOD (1u) 
#define ONE  (1u)
#define RAW_SCAN_TIMES (3u)
#define BASELINE_DELAY (1000u)
#define RAW_DELAY (10u)   
#define BASELINE_SCAN_TIMES (20u)
#define CHECKSUM_VARIABLE   (1u)
#define EXCHANGE_DATA_NUMBER  (11u)

    
/* Config data structure */    
typedef struct
{
    
    uint32_t Data[MAX_SENSOR_VALUE];
    
}U_config_t;

/* Statement data */
typedef struct
{
    uint8_t Next_State;
    uint8_t Current_State;
    uint8_t Previous_State;
    bool StateUpdated;
    
}Current_state_t;

typedef enum
{
   BLE_CONNECTED,
   BLE_CONNECTED_ERROR,
   FLASH_NEED_CSD_SCAN,
   BLE_ADVERTISE,
   BLE_ADVERTISE_ERROR,
   BLE_DISCONNECTED,
   BLE_DISCONNECTED_ERROR,
   CSD_START_SCAN,
   CSD_START_SCAN_ERROR,
   CSD_FINISH_SCAN,
   CSD_FINISH_SCAN_ERROR,
   CSD_LEVEL_COUNTED,
   CSD_LEVEL_COUNTED_ERROR,
   DEVICE_DO_NOTHING
}Current_state;

  #endif 
/* [] END OF FILE */
