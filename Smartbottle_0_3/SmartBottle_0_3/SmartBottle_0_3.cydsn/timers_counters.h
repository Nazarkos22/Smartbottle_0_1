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
#include "Config_u.h"
    
#define TIMER_MAX_NUMBER (5u)        /* Number of initialised timers */
#define PERIOD           (150u)      /* Value, which is used to set up a timer`s period */ 

/* Timer`s State */
typedef enum  
{
    Timer_busy, 
    Timer_free,
    No_timer_free = 11u
}Status_Timer;

typedef enum
{
    TMR_CHECK_1_TIMER,
    TMR_CHECK_2_TIMER,
    TMR_CHECK_3_TIMER,
    TMR_CHECK_4_TIMER,
    TMR_CHECK_5_TIMER
}State_Timer;

/* Structure with timer`s status. Used to uderstand what any of timers is doing in any moment of program executing */
typedef struct 
{
    /* Flag takes "busy" or "free" values */
    uint8_t Timer_Status;
    /* Indicate timer`s period */
    uint16_t Timer_Period;
    /* Indicate what app is waiting this timer interrupt */
    uint8_t Block;
    /* Flag to indicate of permittance to check timer interrupt */
    bool Wait_itr;
    /* Flag which indicate interrupt */
    bool Interrupt;
} Timer_parametr_t;

typedef struct
{
    uint8_t Timer_State;
    
}TimerState_t;


/* Declaration Timer start function */
void Start_Timer(uint8_t block, uint16_t period);
/* Declaration of main timer handler */
void Timer_Handler(void);
/************************************************/
void core_TmrInterrupt(void);
void csd_TmrInterrupt(void);


/******************************************************/
void Tmr_Int_1_Handler(void);

void Tmr_Int_2_Handler(void);

void Tmr_Int_3_Handler(void);

void Tmr_Int_4_Handler(void);

void Tmr_Int_5_Handler(void);
    
  #endif    
/* [] END OF FILE */
