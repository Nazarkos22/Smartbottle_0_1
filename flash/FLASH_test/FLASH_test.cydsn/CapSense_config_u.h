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

#ifndef __CAPSENSE_CONFIG_U_H_
#define __CAPSENSE_CONFIG_U_H_
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
    void make_sensors_data(void);//function save data(raw counts) from CapSense widgets to array "Sensors"
    uint32_t Find_Liquid_Level(uint32_t* data, uint32_t ADDR);// function checks which of sensors are activated and return Level(0-250u)
 #endif
/* [] END OF FILE */
