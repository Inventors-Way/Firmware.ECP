/*
* Timer.c
*
* Created: 14-04-2021 13:06:37
*  Author: KristianHennings
*/

#include <hal/TimerTick.h>
#include <sys/Timer.h>
#include <sys/System.h>
#include <sys/DebugSignal.h>
#include <sys/MemoryPool.h>

/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

/**
* @addtogroup PTimer
* @{
*/

#define MAX_NUMBER_OF_TIMERS 16

/**
* @brief
*
*/
struct Timer
{
   uint32_t period;
   enum TimerType  type;
   uint8_t  running;
   uint32_t startTime;
   enum DebugSignal signal;
   
   void* owner;
   void (*func)(void* self);
};


struct Timer timers[MAX_NUMBER_OF_TIMERS];
uint8_t noOfTimers = 0;

/**
* @brief
*
* @param time
* @return uint32_t
*/
uint32_t Timer_GetElapsedTime(const uint32_t time);

/**
* @brief
*
* @param self
* @return uint8_t
*/
uint8_t Timer_Check(const uint8_t id);

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void Timer_Initialize(void)
{
   noOfTimers = 0;
}

void Timer_Run(void)
{
   for (uint8_t n = 0; n < noOfTimers; ++n)
   {
      if (Timer_Check(n))
      {
         #ifdef DEBUG
         DebugSignal_Set(timers[n].signal);
         #endif

         timers[n].func(timers[n].owner);

         #ifdef DEBUG
         DebugSignal_Clear(timers[n].signal);
         #endif
      }
   }
}

uint8_t Timer_Check(const uint8_t id)
{
   uint8_t retValue = 0;
   
   if (timers[id].running == 1)
   {
      const uint32_t elapsedTime = Timer_GetElapsedTime(timers[id].startTime);

      if (elapsedTime > timers[id].period)
      {
         retValue = 1U;
         
         if (timers[id].type == TIMER_PERIODIC)
         {
            timers[id].startTime += timers[id].period;
         }
         else
         {
            Timer_Stop(id);
         }
      }
   }
   
   return retValue;
}

uint8_t Timer_Create(void* owner, void (*func)(void* owner), const enum DebugSignal signal)
{   
   uint8_t tid = 0;

   if (noOfTimers < MAX_NUMBER_OF_TIMERS - 1)
   {
      tid = noOfTimers;

      timers[tid].type = TIMER_ONESHOT;
      timers[tid].period = 0;
      timers[tid].running = 0;
      timers[tid].startTime = 0;
      timers[tid].owner = owner;
      timers[tid].func = func;
      timers[tid].signal = signal;

      ++noOfTimers;
   }
   else
   {
      System_HandleFatalError();
   }

   return tid;
}

void Timer_Start(const uint8_t id, enum TimerType type, uint32_t period)
{
   timers[id].type = type;
   timers[id].period = period;
   timers[id].running = 1;
   timers[id].startTime = TimerTick_GetTicks();
}

void Timer_Stop(const uint8_t id)
{
   timers[id].running = 0U;
   timers[id].startTime = 0U;
}

uint32_t Timer_GetNumberOfTimers(void)
{
   return noOfTimers;
}

void Timer_Print(void)
{
   for (uint8_t n = 0; n < noOfTimers; ++n)
   {
      System_Printf("[ %u ] sig = %u, run = %u, type =%u", n, timers[n].signal, timers[n].running, timers[n].type);
   }
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/

uint32_t Timer_GetElapsedTime(const uint32_t time)
{
   const uint32_t currentTimerTicks = TimerTick_GetTicks();
   return time <= currentTimerTicks ? currentTimerTicks - time : (UINT32_MAX - time) + currentTimerTicks;
}
