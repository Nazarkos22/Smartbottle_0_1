/*
 * Copyright (2017): Weles Technologies. 
 * Owner           : Oleksiy Savitskyy
 */

#include <project.h>
#include "stdbool.h"
#include "timer.h"

timers_t timers[MAX_TIMER_NUMB];

void reset_all_timers()
{
    memset(timers, 0, sizeof(timers));
}

bool is_tmr_busy(uint8_t timer_id)
{
     uint8_t tmr_idx = 0;
    
    /* go throught all timers */
    for (tmr_idx = 0; tmr_idx < MAX_TIMER_NUMB; tmr_idx++)
    {
        if ((timers[tmr_idx].timer_id == timer_id) && (timers[tmr_idx].is_active == true))
        {
            return true;
        }
    }
    
    return false;
}

bool timer_start(uint8_t timer_id, uint32_t timer_period_ms, tmr_cbk cbk)
{
    uint8_t tmr_idx = 0;
    
    timer_stop(timer_id);
    
    /* go throught all timers */
    for (tmr_idx = 0; tmr_idx < MAX_TIMER_NUMB; tmr_idx++)
    {
        if (timers[tmr_idx].is_active != true)
        {
            timers[tmr_idx].is_active = true;
            timers[tmr_idx].curr_time = timer_period_ms;
            timers[tmr_idx].timer_id = timer_id;
            if (cbk != NULL)
            {
                timers[tmr_idx].cbk = cbk;
            }
            return true;
        }
    }
        
    return false;
}

void timer_stop(uint8_t timer_id)
{
    uint8_t tmr_idx = 0;
    
    /* go throught all timers */
    for (tmr_idx = 0; tmr_idx < MAX_TIMER_NUMB; tmr_idx++)
    {
        if (timers[tmr_idx].timer_id == timer_id)
        {
            memset(&(timers[tmr_idx]), 0, sizeof(timers_t));
        }
    }
}

uint32_t timer_get_time(uint8_t timer_id)
{
    uint8_t tmr_idx;
    uint32_t ret_time = 0u;
    
    /* go throught all timers */
    for (tmr_idx = 0; tmr_idx < MAX_TIMER_NUMB; tmr_idx++)
    {
        if (timers[tmr_idx].timer_id == timer_id)
        {
            ret_time = timers[tmr_idx].curr_time;
        }
    }
    
    return ret_time;
}

void Global_Timer_Itr_Handler(void) //TODO find out about interrupts disable
{
        
    uint8_t tmr_idx;
    timers_t* curr_tmr = NULL;

    /* go throught all timers */
    for (tmr_idx = 0u; tmr_idx < MAX_TIMER_NUMB; tmr_idx++)
    {
        curr_tmr = &(timers[tmr_idx]);
        if (curr_tmr->is_active != false)
        {
            curr_tmr->curr_time--;
            if (curr_tmr->curr_time <= 0u)
            {
                if (curr_tmr->cbk != NULL)
                {
                    /* Run callback function */
                    curr_tmr->cbk();
                }
                /* Check if timer was modified */
                if (curr_tmr->curr_time == 0u)
                    memset(curr_tmr, 0u, sizeof(timers_t));
            }
        }
    }
        
    Global_Timer_ClearInterrupt(CY_TCPWM_INT_ON_TC);
    Global_Timer_Start();
}

void Global_Timer_Itr_Init(void)
{
    
     /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority.
     */
    Cy_SysInt_Init(&Global_Timer_Itr_cfg, Global_Timer_Itr_Handler);
    /* Enable the core interrupt */ 
    NVIC_EnableIRQ(Global_Timer_Itr_cfg.intrSrc);  
    
}
void Init_Global_Timer(void)
{
    Global_Timer_Itr_Init(); 
    reset_all_timers();
    Global_Timer_Start();
}

/* [] END OF FILE */
