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

void CodeProfiler_Create(void);	
	
void CodeProfiler_Initialize(void);

void CodeProfiler_Suspend(void);

void CodeProfiler_Reset(void);

void CodeProfiler_Tic(const enum DebugSignal signal);

void CodeProfiler_Toc(const enum DebugSignal signal);

void CodeProfiler_SetContext(const enum DebugSignal signal, const uint32_t context);

/** @}*/


#endif /* CODEPROFILER_H_ */