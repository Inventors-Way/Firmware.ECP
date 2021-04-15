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
   DEBUG_SIGNAL_HAL_RUN,
   DEBUG_SIGNAL_SYSTEM_RUN,

	// TIMERS
	DEBUG_SIGNAL_TIMER_DEBUG_SIGNAL,
   DEBUG_SIGNAL_TIMER_HEARTBEAT
};

void DebugSignal_Set(const enum DebugSignal signal);

void DebugSignal_Clear(const enum DebugSignal signal);

void DebugSignal_SetActive(const enum DebugSignal* signal);

/** @} */	

#endif /* DEBUGSIGNAL_H_ */