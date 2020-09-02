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

/* Function to process al CSD block */
void CapSense_Processing(uint8_t scan_times);

void Timers_Interrupts_Init(void);

/* Function to set some flags for start scan */
void Set_Flags(void);

/* Function to process flash block */
void Flash_Scan(void);

/*  */
void Switch_Statement(void);

void BLE_CONNECTED_FUNC(void (*eventClbk)());

void BLE_CONNECTED_ERROR_FUNC(void);

void BLE_ADVERTISE_FUNC(void);

void BLE_ADVERTISE_ERROR_FUNC(void);

void BLE_DISCONNECTED_FUNC(void);

void BLE_DISCONNECTED_ERROR_FUNC(void);

void CSD_START_SCAN_FUNC(void);

void CSD_START_SCAN_ERROR_FUNC(void);

void CSD_FINISH_SCAN_FUNC(void);

void CSD_FINISH_SCAN_ERROR_FUNC(void);

void CSD_LEVEL_COUNTED_FUNC(void);

void CSD_LEVEL_COUNTED_ERROR_FUNC(void);

void DEVICE_DO_NOTHING_FUNC(void (*eventClbk)());

void DoNothingClbk(void);



/* [] END OF FILE */
 #endif