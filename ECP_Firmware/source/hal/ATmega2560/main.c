/*
* ECP_Firmware.c
*
* Created: 14-04-2021 12:31:48
* Author : KristianHennings
*/

#include <hal/HAL.h>
#include <sys/System.h>

int main(void)
{
   HAL_Initialize();
   System_Initialize();

   while (1)
   {
      HAL_Run();
      System_Run();
   }
}

