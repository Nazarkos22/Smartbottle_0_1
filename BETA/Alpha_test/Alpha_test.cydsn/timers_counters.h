/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _TIMERS_COUNTERS_H_   
#define _TIMERS_COUNTERS_H_ 
#include "project.h"
    
#define TIMER_MAX_NUMBER (5u)
#define NO_TIMER_FREE    (11u)
#define PERIOD           (150u)
    
typedef enum  {
    Timer_busy, Timer_free
}State_Timer;

typedef struct {
    uint8_t Timer_Status;

    bool Timer_Status_Changed_to_free;
} Timer_parametr_t;


void Tmr_Int_1_Handler(void);

void Tmr_Int_1_Init(void);

void Tmr_Int_2_Handler(void);

void Tmr_Int_2_Init(void);

void Tmr_Int_3_Handler(void);

void Tmr_Int_3_Init(void);

void Tmr_Int_4_Handler(void);

void Tmr_Int_4_Init(void);

void Tmr_Int_5_Handler(void);

void Tmr_Int_5_Init(void);

void Start_Free_Timer(uint8_t free_timer_nmb, uint32_t period, Timer_parametr_t* timer_data );

uint8_t Which_Timer_Free(uint8_t timer_number, Timer_parametr_t* timer_data)
    
  #endif    
/* [] END OF FILE */
