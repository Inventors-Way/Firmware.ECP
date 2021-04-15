/*
 * CodeProfiler.h
 *
 * Created: 14-04-2021 13:01:58
 *  Author: KristianHennings
 */ 


#ifndef CODEPROFILER_H_
#define CODEPROFILER_H_

#include <stdint.h>
#include <sys/Stopwatch.h>
#include <sys/DebugSignal.h>	
	
/** \addtogroup CodeProfiler
 *  @{
 */

typedef struct
{
   uint32_t count;
   uint32_t timeLimit;
   
   uint32_t time;
   uint32_t max;
   uint32_t min;
   
   uint32_t watch;
} CodeProfiler;

void CodeProfiler_Initialize(CodeProfiler * self);
	
inline void CodeProfiler_Reset(CodeProfiler * self)
{
   self->count = 0;
   self->time = 0;
   self->max = 0;
   self->min = UINT32_MAX;
}

inline void CodeProfiler_Tic(CodeProfiler * self)
{
   Stopwatch_Tic(&self->watch);
}

uint32_t CodeProfiler_Toc(CodeProfiler * self, const enum DebugSignal signal);

void CodeProfiler_SendProfilerMessage(CodeProfiler * self, const enum DebugSignal signal);

/** @}*/


#endif /* CODEPROFILER_H_ */