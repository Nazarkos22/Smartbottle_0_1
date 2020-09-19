/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#ifndef __CORE_H_
    #define __CORE_H_
#include "project.h"
#include "Config_u.h"

    
    typedef struct 
    {
        uint32_t Raws;
    }Middle_used_data_t;
    
    /* Statement data */
typedef struct
{
    uint8_t Next_State;
    uint8_t Current_State;
    uint8_t Previous_State;
    bool StateUpdated;
    
}Current_state_t;

//typedef enum
//{
//   BLE_CONNECTED,
//   BLE_CONNECTED_ERROR,
//   FLASH_NEED_CSD_SCAN,
//   BLE_ADVERTISE,
//   BLE_ADVERTISE_ERROR,
//   BLE_DISCONNECTED,
//   BLE_DISCONNECTED_ERROR,
//   CSD_START_SCAN,
//   CSD_START_SCAN_ERROR,
//   CSD_FINISH_SCAN,
//   CSD_FINISH_SCAN_ERROR,
//   CSD_LEVEL_COUNTED,
//   CSD_LEVEL_COUNTED_ERROR,
//   DEVICE_DO_NOTHING
//}Current_state;


/* Function to process al CSD block */
void CapSense_Processing(uint8_t scan_times);

void Timers_Interrupts_Init(void);

/* Function to set some flags for start scan */
void Set_Flags(void);

/* Function to process flash block */
void Flash_Scan(void);

/*  */
void Switch_Statement(void);



void DEVICE_DO_NOTHING_FUNC(void (*eventClbk)());

void DoNothingClbk(void);



/* [] END OF FILE */
 #endif