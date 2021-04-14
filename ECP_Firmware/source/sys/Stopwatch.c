/*
 * Stopwatch.c
 *
 * Created: 14-04-2021 14:47:11
 *  Author: KristianHennings
 */ 

 #include <sys/Stopwatch.h>
 #include <hal/TimerTick.h>
 
/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

/**
 * @addtogroup PStopwatch
 * @{
 */

#define STOPWATCH_PERIOD    UINT32_MAX

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void Stopwatch_Tic(Stopwatch* self)
{
    self->timestamp = TimerTick_GetTicks();
}

uint32_t Stopwatch_Toc(Stopwatch* self)
{
   const uint32_t currentTime = TimerTick_GetTicks();
   const uint32_t time = self->timestamp <= currentTime ? 
                  currentTime - self->timestamp : 
                  (STOPWATCH_PERIOD - self->timestamp) + currentTime;

   return time;
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/
