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
#include <hal/SerialPort.h>
#include <hal/TimerTick.h>

#include "HalInternal.h"

void HAL_Initialize(void)
{
   DIO_Initialize();
   TimerTick_Initialize();
   SerialPort_Initialize();

   sei();
}

void HAL_Run(void)
{
   TimerTick_Run();
}