/*
 * DebugSignal.h
 *
 * Created: 14-04-2021 14:39:54
 *  Author: KristianHennings
 */ 


#ifndef DEBUGSIGNAL_H_
#define DEBUGSIGNAL_H_

/** \addtogroup DebugSignal
 *  @{
 */

/**
 * @brief 
 * 
 */
enum DebugSignal
{
   DEBUG_SIGNAL_NONE = 0,
	DEBUG_SIGNAL_POLLING_LOOP,
	DEBUG_SIGNAL_MESSAGE_LOOP,

	// TIMERS
	DEBUG_SIGNAL_TIMER_CODE_PROFILER
};

void DebugSignal_Set(const enum DebugSignal signal);

void DebugSignal_Clear(const enum DebugSignal signal);

/** @} */	

#endif /* DEBUGSIGNAL_H_ */