/*
 * MemoryPool.h
 *
 * Created: 15-04-2021 08:58:56
 *  Author: KristianHennings
 */ 
#include <stdint.h>

#ifndef MEMORYPOOL_H_
#define MEMORYPOOL_H_


/** \addtogroup MemoryPool 
 *  @{
 */

void MemoryPool_Create();

uint8_t* MemoryPool_Allocate(uint32_t size);

uint32_t MemoryPool_AllocatedMemory(void);

uint32_t MemoryPool_AvailableMemory(void);

uint32_t MemoryPool_Size(void);

/** @}*/

#endif /* MEMORYPOOL_H_ */