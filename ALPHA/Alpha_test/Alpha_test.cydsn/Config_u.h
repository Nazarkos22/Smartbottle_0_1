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
    
typedef struct
{
    uint32_t Data[MAX_SENSOR_VALUE];
}U_config_t;
   
    

  #endif 
/* [] END OF FILE */
