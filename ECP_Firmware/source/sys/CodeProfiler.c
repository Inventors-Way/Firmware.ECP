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

#define PROFILER_MAX_ID_LENGTH 8	

#define POLLING_TIME_MAX_COUNT 2000
#define POLLING_MAX_TIME       1000
	
typedef struct
{
	uint32_t count;
	uint32_t maxCount;
	uint32_t timeLimit;
	
	uint32_t time;
	uint32_t max;
	uint32_t min;
	uint32_t context;
	
	Stopwatch watch;
	
	uint8_t data[16 + 36];
	char id[PROFILER_MAX_ID_LENGTH];
	struct Timer* timer;
} CodeProfiler;

CodeProfiler profiler;

inline uint8_t CodeProfiler_Update(const uint32_t time)
{
	++profiler.count;
	profiler.time += time;
	profiler.max = time > profiler.max ? time : profiler.max;
	profiler.min = time < profiler.min ? time : profiler.min;
	
	return profiler.count == profiler.maxCount;
}
	
void CodeProfiler_SendTimingViolation(const uint32_t time);

void CodeProfiler_SendProfilerMessage(void* vself);

/******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

void CodeProfiler_Create(void)
{
	profiler.timer = Timer_Create(&profiler, CodeProfiler_SendProfilerMessage, DEBUG_SIGNAL_TIMER_CODE_PROFILER);
}

void CodeProfiler_Initialize(void)
{
	profiler.maxCount = POLLING_TIME_MAX_COUNT;
	profiler.timeLimit = POLLING_MAX_TIME;
	CodeProfiler_Reset();
	Timer_Start(profiler.timer, TIMER_PERIODIC, 2000);
}

void CodeProfiler_Suspend(void)
{
	Timer_Stop(profiler.timer);	
}

void CodeProfiler_Reset()
{
	profiler.count = 0;
	profiler.time = 0;
	profiler.max = 0;
	profiler.min = UINT32_MAX;
}

void CodeProfiler_Tic(const enum DebugSignal signal)
{
	profiler.context = 0;
	Stopwatch_Tic(&profiler.watch);
}

void CodeProfiler_Toc(const enum DebugSignal signal)
{
	if (System_GetActiveDebugSignal() == signal)
	{
		const uint32_t time = Stopwatch_Toc(&profiler.watch);
		
		if (time > profiler.timeLimit)
		{
			CodeProfiler_SendTimingViolation(time);
		}
		
		CodeProfiler_Update(time);
	}
	
	System_DebugOut(signal, 0);	
}

void CodeProfiler_SetContext(const enum DebugSignal signal, const uint32_t context)
{
	if (signal == System_GetActiveDebugSignal())
	{
		profiler.context = context;
	}
}


/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

uint8_t CodeProfiler_CreateID(void)
{
	const enum DebugSignal signal = System_GetActiveDebugSignal();
    snprintf(profiler.id, PROFILER_MAX_ID_LENGTH, "%d", signal);
	
	uint8_t length = strlen(profiler.id);
	length = length > 32 ? 32 : length;	
	
	return length;
}

void CodeProfiler_SendTimingViolation(const uint32_t time)
{
	const uint8_t length = CodeProfiler_CreateID();
	
	Stream_InsertUint32(profiler.data, 0, profiler.timeLimit);
	Stream_InsertUint32(profiler.data, 4, time);
	Stream_InsertUint32(profiler.data, 12, profiler.context);	
	Stream_InsertString(profiler.data, 16, length, profiler.id);
	System_TransmitMessage(TIMER_STATISTICS_MSG, length + 16, profiler.data);
}

void CodeProfiler_SendProfilerMessage(void* vself)
{
	if (System_GetActiveDebugSignal() != DEBUG_SIGNAL_NONE)
	{
		const uint8_t length = CodeProfiler_CreateID();

		Stream_InsertUint32(profiler.data, 0, profiler.time);
		Stream_InsertUint32(profiler.data, 4, profiler.count);
		Stream_InsertUint32(profiler.data, 8, profiler.max);
		Stream_InsertUint32(profiler.data, 12, profiler.min);
		Stream_InsertString(profiler.data, 16, length, profiler.id);
		System_TransmitMessage(TIMER_RUN_TIME_MSG, length + 16, profiler.data);		
	}
	
	CodeProfiler_Reset();
}

#endif