/*
* ECP_Firmware.c
*
* Created: 14-04-2021 12:31:48
* Author : KristianHennings
*/

#include <hal/HAL.h>
#include <sys/System.h>
#include <sys/SystemConfig.h>

int main(void)
{
   HAL_Initialize();
   System_Initialize();

   System_Printf("ECP Firmware, Rev. %d.%d.%d.%d", MAJOR_REVISION, MINOR_REVISION, PATCH_REVISION, ENGINEERING_REVISION);

   while (1)
   {
      HAL_Run();
      System_Run();
   }
}

