/*
 * TimerTick.h
 *
 * Created: 14-04-2021 13:00:24
 *  Author: KristianHennings
 */ 

#include <stdint.h>

#ifndef TIMERTICK_H_
#define TIMERTICK_H_

uint32_t TimerTick_GetTicks(void);

uint32_t TimerTick_GetMicroTicks(void);

uint32_t TimerTick_MicroTickMaximum(void);

#endif /* TIMERTICK_H_ */