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
      #ifdef DEBUG
      DebugSignal_Set(DEBUG_SIGNAL_POLLING_LOOP);
      #endif
      
      HAL_Run();
      System_Run();
      
      #ifdef DEBUG
      DebugSignal_Clear(DEBUG_SIGNAL_POLLING_LOOP);
      #endif
   }
}

