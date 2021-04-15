/*
* System.c
*
* Created: 14-04-2021 13:06:11
*  Author: KristianHennings
*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/System.h>
#include <sys/DebugSignal.h>
#include <sys/Stopwatch.h>
#include <sys/SystemConfig.h>
#include <sys/Timer.h>
#include <hal/DIO.h>
#include <hal/TimerTick.h>
#include <srv/comm/ecp/PeripheralHandler.h>

/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

/**
* @addtogroup PSystem
* @{
*/


void System_OnHeartbeat(void* vself)
{
   System_Printf("Beat");
}

struct Timer* heartbeatTimer;

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void System_Initialize(void)
{
   PeripheralHandler_Initialize();
   heartbeatTimer = Timer_Create(0, System_OnHeartbeat, DEBUG_SIGNAL_TIMER_HEARTBEAT);
   Timer_Start(heartbeatTimer, TIMER_PERIODIC, 1000);
}

void System_Run(void)
{
   PeripheralHandler_Run();
}

void System_Printf(const char* format, ...)
{
   static char str[MAX_STRING_LENGTH];
   memset(str, 0, sizeof(str));

	va_list arguments;
	va_start(arguments, format);
	vsnprintf(str, MAX_STRING_LENGTH, format, arguments);
	va_end(arguments);
	    
   PeripheralHandler_Printf(str);
}

void System_TransmitMessage(const uint8_t code,
                            const uint8_t length,
                            const uint8_t * const data)
{
   PeripheralHandler_TransmitMessage(code, length, data);
}

void System_HandleFatalError(void)
{
   while (1)
   {
      // Halt the processor, and send out SOS
      DIO_SetPin(PIN_DEBUG_OUT02, 1);
      DIO_SetPin(PIN_DEBUG_OUT02, 0);

      // S (Morse Code)
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);

      // SPACE
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);

      // O (Morse Code)
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);

      // SPACE
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);

      // S (Morse Code)
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 1);

      // SPACE
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);

      // SPACE
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);

      // SPACE
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
      DIO_SetPin(PIN_DEBUG_OUT01, 0);
   }
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/

