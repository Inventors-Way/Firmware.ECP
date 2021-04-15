/*
 * Timer.h
 *
 * Created: 14-04-2021 13:01:08
 *  Author: KristianHennings
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <sys/DebugSignal.h>
	
/** \addtogroup Timer
 *  @{
 */

/**
 * @brief 
 * 
 */
enum TimerType
{
    TIMER_PERIODIC = 0, ///< The timer elapses periodically
    TIMER_ONESHOT       ///< The timer elapses only once, after which it is stopped and must be started again
};

/**
 * \brief Create a timer
 * This functions creates a new timer and returns a pointer to the newly created
 * timer object. 
 *
 * This will create a timer with a default time limit of 
 * 
 * \param[in] owner the owner of the timer
 * \param[in] func the function that should be called on the owner when the timer elapsed.
 * \param[in] name the name of the timer
 * \return a pointer to the created timer object
 */
uint8_t Timer_Create(void* owner, void (*func)(void* owner), const enum DebugSignal signal);

/**
 * \brief Set the time limit of a timer
 *
 * \param[in] self a pointer to the timer that should be started
 * \param[in] timeLimit the maximal time a timer is allowed to run
 */
//void Timer_SetTimeLimit(struct Timer* self, const uint32_t timeLimit);

/**
 * \brief Get the number of instantiated timers
 * 
 * \return the number of instantiated timers.
 */
uint32_t Timer_GetNumberOfTimers(void);

/**
 * \brief Start a timer
 * This function starts the timer, if the timer is allready started this will stop
 * the current run of the timer.
 * 
 * \param[in] self a pointer to the timer that should be started
 * \param[in] type the type of the timer (TIMER_PERIODIC or TIMER_ONESHOT)
 * \param[in] period the period of the timer.
 */
void Timer_Start(const uint8_t id, enum TimerType type, uint32_t period);

/**
 * \brief Stops a currently running timer
 * This stops a currently running timer. If the timer is allready stopped this
 * function has no effect.
 * 
 * \param[in] self a pointer to the timer that should be stopped
 */
void Timer_Stop(const uint8_t id);

void Timer_Print(void);

/** @}*/



#endif /* TIMER_H_ */