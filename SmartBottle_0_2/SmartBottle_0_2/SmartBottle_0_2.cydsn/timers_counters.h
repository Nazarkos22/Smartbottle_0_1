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
    
#define TIMER_MAX_NUMBER (5u)        /* Number of initialised timers */
#define PERIOD           (150u)      /* Value, which is used to set up a timer`s period */ 

/* Timer`s State */
typedef enum  
{
    Timer_busy, 
    Timer_free,
    No_timer_free = 11u
}State_Timer;

/* Structure with timer`s status. Used to uderstand what any of timers is doing in any moment of program executing */
typedef struct 
{
    /* Flag takes "busy" or "free" values */
    uint8_t Timer_Status;
    /* Flag becomes "true" when timer has just ended counting */
    bool Timer_Status_Changed_to_free;
} Timer_parametr_t;

/* Initialisation Timer interrupts and its handlers */
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
/****************************************************/

/* Function start timer with number you put in function input parametr */
void Start_Free_Timer(uint8_t free_timer_nmb, uint32_t period, Timer_parametr_t* timer_data );

/* Function check all timers untill find not busy */
uint8_t Which_Timer_Free(uint8_t timer_number, Timer_parametr_t* timer_data);

/* Declaration Timers Callbacks */
void tmr_StartForFlashScan(void);
void tmr_FinishForFlashScan(void);
void tmr_StartForFlashWrite(void);
void tmr_FinishForFlashWrite(void);
void tmr_StartForCapSense(void);
void tmr_FinishForCapSense(void);
void tmr_CoreTmrStoped(uint8_t timer_number);
/************************************************/
    
  #endif    
/* [] END OF FILE */
