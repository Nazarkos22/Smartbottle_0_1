/* ========================================
 *
     Code is written by:
           Kotliar Nazarii (NKOT)     
 *
 * ========================================
*/
#ifndef _CONFIG_U_H_   
#define _CONFIG_U_H_
#include "project.h"

#define MAX_SENSOR_VALUE (10u)
#define ZERO (0u)
#define GOOD (1u) 
#define ONE  (1u)
#define RAW_SCAN_TIMES (3u)
#define BASELINE_DELAY (1000u)
#define RAW_DELAY (10u)   
#define BASELINE_SCAN_TIMES (20u)
#define CHECKSUM_VARIABLE   (1u)
#define EXCHANGE_DATA_NUMBER  (11u)

    
/* Config data structure */    
typedef struct
{
    
    uint32_t Data[MAX_SENSOR_VALUE];
    
}U_config_t;





  #endif 
/* [] END OF FILE */
