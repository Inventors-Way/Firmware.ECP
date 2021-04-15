/*
 * CodeProfiler.c
 *
 * Created: 14-04-2021 13:06:01
 *  Author: KristianHennings
 */ 
 
#include <sys/DebugSignal.h>
#include <sys/Timer.h>
#include <sys/System.h>
#include <tools/Stream.h>
#include <sys/SystemConfig.h>

#include "CodeProfiler.h"

#ifdef DEBUG

/******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

#define POLLING_MAX_TIME       1000
	
inline void CodeProfiler_Update(CodeProfiler * self, const uint32_t time)
{
	++self->count;
	self->time += time;
	self->max = time > self->max ? time : self->max;
	self->min = time < self->min ? time : self->min;	
}
	
void CodeProfiler_SendTimingViolation(CodeProfiler * self, const enum DebugSignal signal, const uint32_t time);

/******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

void CodeProfiler_Initialize(CodeProfiler * self)
{
	self->timeLimit = POLLING_MAX_TIME;
	CodeProfiler_Reset(self);
}

void CodeProfiler_Toc(CodeProfiler * self, const enum DebugSignal signal)
{
	const uint32_t time = Stopwatch_Toc(&self->watch);
		
	if (time > self->timeLimit)
	{
		CodeProfiler_SendTimingViolation(self, signal, time);
	}
		
	CodeProfiler_Update(self, time);
}

void CodeProfiler_SendProfilerMessage(CodeProfiler * self, const enum DebugSignal signal)
{
   static uint8_t data[20];

   Stream_InsertUint32(data, 0, signal);
   Stream_InsertUint32(data, 4, self->time);
   Stream_InsertUint32(data, 8, self->count);
   Stream_InsertUint32(data, 12, self->max);
   Stream_InsertUint32(data, 16, self->min);

   System_TransmitMessage(TIMER_RUN_TIME_MSG, 20, data);
}


/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

void CodeProfiler_SendTimingViolation(CodeProfiler * self, const enum DebugSignal signal, const uint32_t time)
{
   static uint8_t data[12];

   Stream_InsertUint32(data, 0, signal);
   Stream_InsertUint32(data, 4, self->timeLimit);
   Stream_InsertUint32(data, 8, time);

   System_TransmitMessage(TIMER_STATISTICS_MSG, 12, data);
}

#endif