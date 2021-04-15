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

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void Stopwatch_Tic(uint32_t* timestamp)
{
    *timestamp = TimerTick_GetMicroTicks();
}

uint32_t Stopwatch_Toc(uint32_t* timestamp)
{
   const uint32_t maximum = TimerTick_MicroTickMaximum();
   const uint32_t currentTime = TimerTick_GetMicroTicks();
   const uint32_t time = *timestamp <= currentTime ? 
                  currentTime - *timestamp : 
                  (maximum - *timestamp) + currentTime;

   return time;
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/
