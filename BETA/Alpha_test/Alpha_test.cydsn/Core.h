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
     
void CapSense_Processing(uint8_t scan_times);
void Timer_Int_Init(void);
void TimerInterruptHandler(void);
void Set_Flags(void);

void Flash_Scan(void);

/* [] END OF FILE */
 #endif