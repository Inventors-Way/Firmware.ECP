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
typedef struct
{
    uint32_t timestamp;
} Stopwatch;

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
void Stopwatch_Tic(Stopwatch* self);

/**
 * @brief 
 * 
 * @param self 
 * @return uint32_t 
 */
uint32_t Stopwatch_Toc(Stopwatch* self);

/** @}*/

#endif /* STOPWATCH_H_ */