/*
* ECP_Firmware.c
*
* Created: 14-04-2021 12:31:48
* Author : KristianHennings
*/

#include <hal/HAL.h>
#include <sys/System.h>
#include <sys/DebugSignal.h>
#include <sys/SystemConfig.h>

int main(void)
{
   HAL_Initialize();
   System_Initialize();

   while (1)
   {      
      DEBUG_SIGNAL_SET(DEBUG_SIGNAL_POLLING_LOOP)   
      HAL_Run();
      System_Run();
      DEBUG_SIGNAL_CLEAR(DEBUG_SIGNAL_POLLING_LOOP)
   }
}

