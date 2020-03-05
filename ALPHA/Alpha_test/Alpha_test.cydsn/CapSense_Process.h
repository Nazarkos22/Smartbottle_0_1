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

#ifndef __CAPSENSE_PROCESS_H_
#define __CAPSENSE_PROCESS_H_
#include "project.h"
#include "Config_u.h"
    
    #define FIRST_lvl (0u)
    #define SECOND_lvl (1u)
    #define THIRD_lvl (2u)
    #define FOURTH_lvl (3u)
    #define FIFTH_lvl (4u)
    #define SIXTH_lvl (5u)
    #define SEVENTH_lvl (6u)
    #define EIGHTH_lvl (7u)
    #define NINETH_lvl (8u)
    #define TENTH_lvl (9u)
    #define MAX_LEVEL (11u)
    #define TRESHOLD (4000u)// A change of CapSense count raws, which activates sensor
    
    typedef struct
    {
       uint32_t Raws[MAX_SENSOR_VALUE];// array of sensors data
       uint32_t Diff[MAX_SENSOR_VALUE];// array of differance between Baseline and Raws
       uint32_t Baseline[MAX_SENSOR_VALUE];// array of Baseline data
       uint8_t Level;// liquid level
    }U_csd_data_t;
    
    void Craete_Baseline_data_from_Sensors(uint32_t* data, uint8_t len);
    bool is_any_sensor_data_empty(uint32_t* data, uint8 len);//function checks is senors data equal NULL(true) or NOT(false)
    uint8_t make_sensors_data(uint32_t* data, uint8 len);//function save data(raw counts) from CapSense widgets to array "Sensors"
    uint32_t Find_Liquid_Level(uint32_t* data, uint32_t ADDR);// function checks which of sensors are activated and return Level(0-250u)
 #endif
/* [] END OF FILE */
