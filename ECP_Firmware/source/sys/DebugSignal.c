/*
 * DebugSignal.c
 *
 * Created: 15-04-2021 16:10:11
 *  Author: KristianHennings
 */ 
#include <sys/DebugSignal.h>
#include <sys/Timer.h>
#include <sys/System.h>
#include <hal/DIO.h>
#include "PDebugSignal.h"
#include "CodeProfiler.h"

/******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

/**
 * @addtogroup PDebugSignal
 * @{
 */

typedef struct {
   enum DebugSignal signal;
   enum Pin pin;
   CodeProfiler profiler;
} TDebugSignal;

TDebugSignal signals[NUMBER_OF_DEBUG_SIGNALS];
uint8_t debugTimer;

uint8_t DebugSignal_GetIndex(const enum DebugSignal signal);

void DebugSignal_OnTimer(void* vself);

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void DebugSignal_SetActive(const enum DebugSignal* signal)
{
   for (uint8_t n = 0; n < NUMBER_OF_DEBUG_SIGNALS; ++n)
   {
      TDebugSignal* self = &signals[n];

      self->signal = signal[n];
      CodeProfiler_Reset(&self->profiler);
      DIO_SetPin(self->pin, 0);

      System_Printf("DS: %u [ %u ]", self->signal, self->pin);
   }
}

void DebugSignal_Set(const enum DebugSignal signal)
{
   const uint8_t index = DebugSignal_GetIndex(signal);

   if (index < UINT8_MAX)
   {
      TDebugSignal* self = &signals[index];
      DIO_SetPin(self->pin, 1);
      CodeProfiler_Tic(&self->profiler);
   }
}

void DebugSignal_Clear(const enum DebugSignal signal)
{
   const uint8_t index = DebugSignal_GetIndex(signal);

   if (index < UINT8_MAX)
   {
      TDebugSignal* self= &signals[index];
      DIO_SetPin(self->pin, 0);
      CodeProfiler_Toc(&self->profiler, signal);
   }
}

/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

void DebugSignal_Initialize(void)
{   
   for (uint8_t n = 0; n < NUMBER_OF_DEBUG_SIGNALS; ++n)
   {
      signals[n].signal = DEBUG_SIGNAL_NONE;
      signals[n].pin = DIO_GetDebugPin(n);
      CodeProfiler_Initialize(&signals[n].profiler);
      DIO_SetPin(signals[n].pin, 0);
   }

   debugTimer = Timer_Create(0, DebugSignal_OnTimer, DEBUG_SIGNAL_TIMER_DEBUG_SIGNAL);
   Timer_Start(debugTimer, TIMER_PERIODIC, PROFILER_PERIOD);
}

uint8_t DebugSignal_GetIndex(const enum DebugSignal signal)
{
   uint8_t retValue = UINT8_MAX;

   for (uint8_t n = 0; n < NUMBER_OF_DEBUG_SIGNALS; ++n)
   {
      if (signals[n].signal == signal)
      {
         retValue = n;
         break;
      }
   }

   return retValue;
};

void DebugSignal_OnTimer(void* vself)
{
   for (uint8_t n = 0; n < NUMBER_OF_DEBUG_SIGNALS; ++n)
   {
      if (signals[n].signal != DEBUG_SIGNAL_NONE)
      {
         CodeProfiler_SendProfilerMessage(&signals[n].profiler, signals[n].signal);
         CodeProfiler_Reset(&signals[n].profiler);
      }
   }
}