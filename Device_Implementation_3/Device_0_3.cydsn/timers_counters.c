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
#include "timers_counters.h"
#include "project.h"
#include "Config_u.h"

/*************************************************************/
/* Declaration timers`data structure */
Timer_parametr_t static Timers_Data[TIMER_MAX_NUMBER];
TimerState_t static Timer_CurrentState;

/************************************************/
/******//* Initialisation Core Callback *//******/
static void Timer_Callback_to(void (*eventClbk)())
{
    eventClbk();
}
/*************************************************/
/*************************************************/

/* Initialization of timer inetrrupt */
void Tmr_Int_1_Init(void)
{
    
     /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&Tmr_Int_1_cfg, Tmr_Int_1_Handler);
    /* Enable the core interrupt */ 
    NVIC_EnableIRQ(Tmr_Int_1_cfg.intrSrc);  
    
}




/*****************************************************************/





/* Initialization of timer inetrrupt */
void Tmr_Int_2_Init(void)
{
    
     /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&Tmr_Int_2_cfg, Tmr_Int_2_Handler);
    /* Enable the core interrupt */ 
    NVIC_EnableIRQ(Tmr_Int_2_cfg.intrSrc);  
    
}


/***********************************************************************/





/* Initialization of timer inetrrupt */
void Tmr_Int_3_Init(void)
{
    
     /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&Tmr_Int_3_cfg, Tmr_Int_3_Handler);
    /* Enable the core interrupt */ 
    NVIC_EnableIRQ(Tmr_Int_3_cfg.intrSrc);  
    
}


/*************************************************************************/





/* Initialization of timer inetrrupt */
void Tmr_Int_4_Init(void)
{
    
     /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&Tmr_Int_4_cfg, Tmr_Int_4_Handler);
    /* Enable the core interrupt */ 
    NVIC_EnableIRQ(Tmr_Int_4_cfg.intrSrc);  
    
}


/*****************************************************************************/





/* Initialization of timer inetrrupt */
void Tmr_Int_5_Init(void)
{
    
     /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&Tmr_Int_5_cfg, Tmr_Int_5_Handler);
    /* Enable the core interrupt */ 
    NVIC_EnableIRQ(Tmr_Int_5_cfg.intrSrc);  
    
}


/***********************************************************************************/

/* Function return number of free timer */
uint8_t Which_Timer_Free(uint8_t timer_number, Timer_parametr_t* timer_data)
{
    uint8_t idx;
    for(idx = ZERO; idx < timer_number; idx++)
    {
        /* Return first free timer */
        if(timer_data[idx].Timer_Status == Timer_free)
        {
            return (idx+1u);
        }
    }
    /* If there is no free timer */
    return No_timer_free;
}


/* Function start timer with input number */ 
void Start_Free_Timer(uint8_t free_timer_nmb, uint32_t period, Timer_parametr_t* timer_data, uint8_t block)
{
    /* Change timer status */
    timer_data[free_timer_nmb].Timer_Status = Timer_busy;
    /* Indicate period */
    timer_data[free_timer_nmb].Timer_Period = period;
    /* Indicate app, for which timer is called */
    timer_data[free_timer_nmb].Block = block;
    /* Use free timer */
    switch(free_timer_nmb)
    {
        case 1u:
            /* Establish timer`s period */
            Timer_1_SetPeriod(period);
            /* Start timer */
            Timer_1_Start();
            /* Set flag to indicate that program need check this timer interrupt */
            timer_data[0u].Wait_itr = true;
            break;
            
        case 2u: 
            /* Establish timer`s period */
            Timer_2_SetPeriod(period);
            /* Start timer */
            Timer_2_Start();
            /* Set flag to indicate that program need check this timer interrupt */
            timer_data[1u].Wait_itr = true;
            break;
            
        case 3u: 
            /* Establish timer`s period */
            Timer_3_SetPeriod(period);
            /* Start timer */
            Timer_3_Start();
            /* Set flag to indicate that program need check this timer interrupt */
            timer_data[2u].Wait_itr = true;
            break;
            
        case 4u: 
            /* Establish timer`s period */
            Timer_4_SetPeriod(period);
            /* Start timer */
            Timer_4_Start();
            /* Set flag to indicate that program need check this timer interrupt */
            timer_data[3u].Wait_itr = true;
            break;
            
        case 5u: 
            /* Establish timer`s period */
            Timer_5_SetPeriod(period);
            /* Start timer */
            Timer_5_Start();
            /* Set flag to indicate that program need check this timer interrupt */
            timer_data[4u].Wait_itr = true;
            break;
            
        default:
            break;

    }
    
}

void Start_Timer(uint8_t block, uint16_t period)
{
    uint8_t variable;
    /* Return free timer number to variable */
    variable = Which_Timer_Free(TIMER_MAX_NUMBER, Timers_Data);
    /* Start timer */
    Start_Free_Timer(variable, period, Timers_Data, block);
}

/* Function check which App wait interrupt of timer */ 
static void Send_Interrupt(uint8_t block)
{
    switch(block)
    {
        case NO_APP:
            break;
        
        case CORE_APP:
            /* Send interrupt to Core app */
            Timer_Callback_to(core_TmrInterrupt);
            break;
            
        case CSD_APP:
            /* Send interrupt to Core app */
            Timer_Callback_to(csd_TmrInterrupt);
            break;
            
        default:
            break;
    }
}

/* Function reset flags and status data of input timer */
static void Reset_TimerStatus(Timer_parametr_t* timer_data, uint8_t tmr_num)
{
    /* No app wait this timer interrupt */
    timer_data[tmr_num].Block = NO_APP;
    /* Set flag that current timer is free */
    timer_data[tmr_num].Timer_Status = Timer_free;
    /* Indicate programm that it do not have to check this timer interrupt */
    timer_data[tmr_num].Wait_itr = false;
    /* Reset interrupt */
    timer_data[tmr_num].Interrupt = false;
}

/* Function Change timer state to next state */
static void tmr_ChangeState(void)
{
    /* Do only if current timer state is NOT the last timer state */
    if(Timer_CurrentState.Timer_State != TMR_CHECK_5_TIMER)
    {
        Timer_CurrentState.Timer_State =+1;
    }
    else
    {
        Timer_CurrentState.Timer_State = TMR_CHECK_1_TIMER;
    }
    
}

/* Function check interrupt of input timer */
static bool Check_Interrupt(Timer_parametr_t* timer_data, uint8_t tmr_num)
{
    /* Return interrupt flag */
    return (timer_data[tmr_num].Interrupt);
}

/* Timer main function */
void Timer_Handler(void)
{
    switch(Timer_CurrentState.Timer_State)
    {
        case TMR_CHECK_1_TIMER:
            /* Do only if programm is waiting this timer interrupt and this timer have sent interrupt */
            if((Timers_Data[0u].Wait_itr == true) && (true == Check_Interrupt(Timers_Data, 0u)))
            {
                /* Sand interrupt to waiting app */
                Send_Interrupt(Timers_Data[0u].Block);
                /* Reset timer */
                Reset_TimerStatus(Timers_Data, 0u);
            }
            /* Call change state function */
            Timer_Callback_to(tmr_ChangeState);
            break;
            
        case TMR_CHECK_2_TIMER:
            /* Do only if programm is waiting this timer interrupt and this timer have sent interrupt */
            if((Timers_Data[1u].Wait_itr == true) && (true == Check_Interrupt(Timers_Data, 1u)))
            {
                /* Sand interrupt to waiting app */
                Send_Interrupt(Timers_Data[1u].Block);
                /* Reset timer */
                Reset_TimerStatus(Timers_Data, 1u);
            }
            /* Call change state function */
            Timer_Callback_to(tmr_ChangeState);
            break;
            
        case TMR_CHECK_3_TIMER:
            /* Do only if programm is waiting this timer interrupt and this timer have sent interrupt */
            if((Timers_Data[2u].Wait_itr == true) && (true == Check_Interrupt(Timers_Data, 2u)))
            {
                /* Sand interrupt to waiting app */
                Send_Interrupt(Timers_Data[2u].Block);
                /* Reset timer */
                Reset_TimerStatus(Timers_Data, 2u);
            }
            /* Call change state function */
            Timer_Callback_to(tmr_ChangeState);
            break;
            
        case TMR_CHECK_4_TIMER:
            /* Do only if programm is waiting this timer interrupt and this timer have sent interrupt */
            if((Timers_Data[3u].Wait_itr == true) && (true == Check_Interrupt(Timers_Data, 3u)))
            {
                /* Sand interrupt to waiting app */
                Send_Interrupt(Timers_Data[3u].Block);
                /* Reset timer */
                Reset_TimerStatus(Timers_Data, 3u);
            }
            /* Call change state function */
            Timer_Callback_to(tmr_ChangeState);
            break;
            
        case TMR_CHECK_5_TIMER:
            /* Do only if programm is waiting this timer interrupt and this timer have sent interrupt */
            if((Timers_Data[4u].Wait_itr == true) && (true == Check_Interrupt(Timers_Data, 4u)))
            {
                /* Sand interrupt to waiting app */
                Send_Interrupt(Timers_Data[4u].Block);
                /* Reset timer */
                Reset_TimerStatus(Timers_Data, 4u);
            }
            /* Call change state function */
            Timer_Callback_to(tmr_ChangeState);
            break;
            
        default:
            Timer_CurrentState.Timer_State = TMR_CHECK_1_TIMER;
            break;
            
    }
}
/* Initialization of timers` interrupts */
void Timers_Interrupts_Init(void)
{
    
    Tmr_Int_1_Init();
    
    Tmr_Int_2_Init();

    Tmr_Int_3_Init();

    Tmr_Int_4_Init();

    Tmr_Int_5_Init();
   
}

void Tmr_Int_1_Handler(void)
{ 
    /* Set timer flag */
    Timers_Data[0u].Interrupt = true;
    /* Clear timer interrupt */
    Timer_1_ClearInterrupt(CY_TCPWM_INT_ON_TC); 
}

void Tmr_Int_2_Handler(void)
{
    
    /* Set timer flag */
    Timers_Data[1u].Interrupt = true;
    /* Clear timer interrupt */
    Timer_2_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_3_Handler(void)
{
    
    /* Set timer flag */
    Timers_Data[2u].Interrupt = true;
    /* Clear timer interrupt */
    Timer_3_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_4_Handler(void)
{
    
    /* Set timer flag */
    Timers_Data[3u].Interrupt = true;
    /* Clear timer interrupt */
    Timer_4_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    
}

void Tmr_Int_5_Handler(void)
{
    
    /* Set timer flag */
    Timers_Data[4u].Interrupt = true;
    /* Clear timer interrupt */
    Timer_5_ClearInterrupt(CY_TCPWM_INT_ON_TC);
}


/* [] END OF FILE */
