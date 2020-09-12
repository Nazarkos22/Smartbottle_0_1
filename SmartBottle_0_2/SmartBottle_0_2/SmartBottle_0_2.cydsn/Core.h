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