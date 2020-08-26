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






/* Initialization of timer inetrrupts */
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





/* Initialization of timer inetrrupts */
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





/* Initialization of timer inetrrupts */
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





/* Initialization of timer inetrrupts */
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





/* Initialization of timer inetrrupts */
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

uint8_t Which_Timer_Free(uint8_t timer_number, Timer_parametr_t* timer_data)
{
    uint8_t idx;
    for(idx = ZERO; idx < timer_number; idx++)
    {
        if(timer_data[idx].Timer_Status == Timer_free)
        {
            return (idx+1);
        }
    }
    return NO_TIMER_FREE;
}

void Start_Free_Timer(uint8_t free_timer_nmb, uint32_t period, Timer_parametr_t* timer_data )
{
    /* Change timer status */
    timer_data[free_timer_nmb].Timer_Status = Timer_busy;
    timer_data[free_timer_nmb].Timer_Status_Changed_to_free = false;
    /* Use free timer */
    switch(free_timer_nmb)
    {
        case 1u: 
            Timer_1_SetPeriod(period);
            Timer_1_Start();
            break;
        case 2u: 
            Timer_2_SetPeriod(period);
            Timer_2_Start();
            break;
        case 3u: 
            Timer_3_SetPeriod(period);
            Timer_3_Start();
            break;
        case 4u: 
            Timer_4_SetPeriod(period);
            Timer_4_Start();
            break;
        case 5u: 
            Timer_5_SetPeriod(period);
            Timer_5_Start();
            break;
        default:
            break;

    }
    
}
    


/* [] END OF FILE */
