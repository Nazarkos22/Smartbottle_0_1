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

/* Initialization of timer inetrrupts*/
void Timer_Int_Init(void);

/* Function to do after timer interrupt is set */
void TimerInterruptHandler(void);

/* Function to set some flags for start scan */
void Set_Flags(void);

/* Function to process flash block */
void Flash_Scan(void);

/* [] END OF FILE */
 #endif