/*
* Timer.c
*
* Created: 14-04-2021 13:06:37
*  Author: KristianHennings
*/

#include <hal/TimerTick.h>
#include <sys/Timer.h>
#include <sys/System.h>
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

struct TimerItem;

/**
* @brief
*
*/
struct Timer
{
   struct TimerItem* id;
   
   uint32_t period;
   enum TimerType  type;
   uint8_t  running;
   uint32_t startTime;
   
   void* owner;
   void (*func)(void* self);
};

/**
* @brief
*
*/
struct TimerItem
{
   struct TimerItem* next;
   enum DebugSignal signal;

   struct Timer* timer;
};

struct TimerItem* timers;

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
uint8_t Timer_Check(struct Timer* const self);

/**
* @brief
*
* @param self
* @param id
*/
void Timer_Add(struct Timer* const self, const enum DebugSignal signal);

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void Timer_Initialize(void)
{
   timers = 0;
}

void Timer_Run(void)
{
   struct TimerItem* iterator = timers;

   while (iterator != 0)
   {
      if (Timer_Check(iterator->timer))
      {
         #ifdef DEBUG
         System_DebugOut(iterator->signal, 1);
         #endif

         iterator->timer->func(iterator->timer->owner);

         #ifdef DEBUG
         System_DebugOut(iterator->signal, 0);
         #endif
      }
      
      iterator = iterator->next;
   }
}

uint8_t Timer_Check(struct Timer* const self)
{
   uint8_t retValue = 0;
   
   if (self->running)
   {
      if (Timer_GetElapsedTime(self->startTime) > self->period)
      {
         retValue = 1U;
         
         if (self->type == TIMER_PERIODIC)
         {
            self->startTime += self->period;
         }
         else
         {
            Timer_Stop(self);
         }
      }
   }
   
   return retValue;
}

struct Timer* Timer_Create(void* owner, void (*func)(void* owner), const enum DebugSignal signal)
{
   struct Timer* retValue = (struct Timer*) MemoryPool_Allocate(sizeof(struct Timer));
   retValue->type = TIMER_ONESHOT;
   retValue->period = 0;
   retValue->running = 0;
   retValue->startTime = 0;
   retValue->owner = owner;
   retValue->func = func;
   retValue->id = 0;
   
   Timer_Add(retValue, signal);
   
   return retValue;
}

void Timer_Start(struct Timer* self, enum TimerType type, uint32_t period)
{
   self->type = type;
   self->period = period;
   self->running = 1;
   self->startTime = TimerTick_GetTicks();
}

void Timer_Stop(struct Timer* self)
{
   self->running = 0U;
   self->startTime = 0U;
}

uint32_t Timer_GetNumberOfTimers(void)
{
   uint32_t retValue = 0;
   struct TimerItem* iterator = timers;

   while (iterator != 0)
   {
      ++retValue;
      iterator = iterator->next;
   }

   return retValue;
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

void Timer_Add(struct Timer* const self, const enum DebugSignal signal)
{
   struct TimerItem* item = (struct TimerItem*) MemoryPool_Allocate(sizeof(struct TimerItem));
   item->timer = self;
   item->next = 0;
   item->signal = signal;
   
   if (timers != 0)
   {
      item->next = timers;
      timers = item;
   }
   else
   {
      timers = item;
   }
}
