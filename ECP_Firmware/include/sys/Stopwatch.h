/*
 * Stopwatch.h
 *
 * Created: 14-04-2021 14:46:34
 *  Author: KristianHennings
 */ 


#ifndef STOPWATCH_H_
#define STOPWATCH_H_


#include <stdint.h>

/** \addtogroup Stopwatch
 *  @{
 */

/**
 * @brief 
 * 
 */

/**
 * @brief 
 * 
 */
void Stopwatch_Initialize(void);

/**
 * @brief 
 * 
 */
void Stopwatch_Suspend(void);

/**
 * @brief 
 * 
 * @param self 
 */
void Stopwatch_Tic(uint32_t* timestamp);

/**
 * @brief 
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t Stopwatch_Toc(uint32_t* timestamp);

/** @}*/

#endif /* STOPWATCH_H_ */