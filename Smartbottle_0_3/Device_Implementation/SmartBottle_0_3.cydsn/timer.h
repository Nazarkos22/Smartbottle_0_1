/*
 * Copyright (2018): Weles Technologies. 
 * Owner           : Oleksiy Savitskyy
 */

#if !defined(TIMER_H)   
#define TIMER_H
   
#include <project.h>
#include "stdbool.h"
    
#define MAX_TIMER_NUMB                               (5u)    

/* Sensor update related Timers */	
#define SENSOR_CHANGE_SLAVE_TIMEOUT_TMR               (0u)
#define SENSOR_CHANGE_SLAVE_TIMEOUT_PERIOD_MS         (5000u) //TODO set as config param
#define SENSOR_CHANGE_SLAVE_BUSY_PERIOD_MS            (50u) //TODO set as config param    
#define SENSOR_GET_INFO_TIMEOUT_TMR                   (1u)
#define SENSOR_GET_INFO_TIMEOUT_PERIOD_MS             (1000u)
#define SENSOR_LORA_INIT_TIMEOUT_TMR                  (2u)
#define SENSOR_LORA_INIT_TIMEOUT_TMR_PERIOD_MS        (3000u)    
#define SENSOR_UPDT_TMR                               (3u)
#define SENSOR_UPDT_TMR_PERIOD_MS                     (3000u)       
        
/* GSM module related Timers */	 
#define GSM_BUSY_TMR                                  (10u)
#define GSM_BUSY_PERIOD_MS                            (70u) 
#define GSM_RESET_TMR_PERIOD_MS                       (200u) 
#define UART_FAILURE_TMR                              (11u)  
#define GSM_STATUS_TMR                                (12u)
#define GSM_STATUS_TMR_PERIOD                         (30000u)
#define GSM_STATUS_REG_PERIOD_THRESHOLD               (2300u)
#define GSM_STATUS_NOT_REG_PERIOD_THRESHOLD           (1500u)
#define GSM_INIT_FAIL_TMR                             (13u)
#define GSM_INIT_FAIL_TMR_PERIOD                      (300000u)
    
/* Alarm related Timers */	 
#define ALARM_TMR                                     (20u)
#define ALARM_TMR_PERIOD_MS                           (700u) 

/* RTC related Timers */	 
#define RTC_GET_TIME_TMR                              (30u)
#define RTC_GET_TIME_TMR_PERIOD_MS                    (5000u)  
#define RTC_BUSY_TMR                                  (31u)
#define RTC_BUSY_TMR_PERIOD_MS                        (100u)
      
/* Lora related Timers */
#define LORA_BUSY_TMR                                 (40u)
#define LORA_BUSY_TMR_PERIOD_MS                       (100u)
#define LORA_REC_BUSY_TMR_PERIOD_MS                   (10u)
#define LORA_SEND_TIMEOUT_TMR                         (41u)
#define LORA_SEND_TIMEOUT_TMR_PERIOD_MS               (1000u)
#define LORA_REC_TIMEOUT_TMR                          (42u)
#define LORA_REC_TIMEOUT_TMR_PERIOD_MS                (300u)   
    
/* SPI related Timers */	
#define SPI_FAILURE_TMR_ID                            (50u)
#define SPI_FAILURE_TMR_PERIOD                        (5u)   
    
/* Slave PE related Timers */	
#define SLAVE_PE_NO_HOST_CONN_TIMEOUT_TMR             (60u)
#define SLAVE_PE_NO_HOST_CONN_TIMEOUT_TMR_PERIOD      (600000u) // 10 min timeout  
  
/* BLE related Timers */	
#define BLE_NTF_RETRY_TMR_ID                          (70u) 
#define BLE_NTF_RETRY_TMR_PERIOD                      (150u) //TODO set to 20 in release
    
/* Power detection related Timer */	
#define PWR_DETECTION_SCAN_TMR_ID                     (80u) 
#define PWR_DETECTION_SCAN_TMR_PERIOD                 (1000u) 
    
typedef void (*tmr_cbk)(void);    
    
typedef struct
{
    uint8_t timer_id;
    bool is_active;
    uint32_t curr_time;
    tmr_cbk cbk;
    
} timers_t;
   
bool is_tmr_busy(uint8_t timer_id);
bool timer_start(uint8_t timer_id, uint32_t timer_period_ms, tmr_cbk cbk);
void reset_all_timers(void);
void init_global_timer(void);
void timer_stop(uint8_t timer_id);
uint32_t timer_get_time(uint8_t timer_id);

#endif    

/* [] END OF FILE */
