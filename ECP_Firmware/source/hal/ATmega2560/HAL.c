/*
 * HAL.c
 *
 * Created: 14-04-2021 13:46:18
 *  Author: KristianHennings
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <hal/HAL.h>
#include <hal/DIO.h>
#include <hal/SPI.h>
#include <hal/SerialPort.h>
#include <hal/TimerTick.h>
#include <sys/DebugSignal.h>
#include <sys/System.h>

#include "HalInternal.h"

void HAL_Initialize(void)
{
   DIO_Initialize();
   TimerTick_Initialize();
   SerialPort_Initialize();
   
   if (!SPI_Initialize(DORD_LSB, CPOL0, CPOL0, CLKDIV_02))
   {
	   System_HandleFatalError();
   }

   sei();
}

void HAL_Run(void)
{
   #ifdef DEBUG
   DebugSignal_Set(DEBUG_SIGNAL_HAL_RUN);
   #endif

   TimerTick_Run();

   #ifdef DEBUG
   DebugSignal_Clear(DEBUG_SIGNAL_HAL_RUN);
   #endif
}