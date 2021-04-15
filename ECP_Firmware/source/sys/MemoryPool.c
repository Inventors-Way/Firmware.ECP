/*
 * MemoryPool.c
 *
 * Created: 15-04-2021 08:59:12
 *  Author: KristianHennings
 */ 
 #include <sys/MemoryPool.h>
 #include <sys/SystemConfig.h>
 
/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

/**
 * @addtogroup PMemoryPool
 * @{
 */

typedef struct
{
	uint8_t memory[MEMORY_POOL_SIZE];
	uint32_t size;
	uint32_t allocated;
} MemoryPool; 

static MemoryPool pool;

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void MemoryPool_Create()
{
	pool.allocated = 0;
}

uint8_t* MemoryPool_Allocate(uint32_t size)
{
   if(size > (MEMORY_POOL_SIZE - pool.allocated))
   {
      return 0;
   }
        
   pool.allocated += size;
   return &pool.memory[pool.allocated];
}

uint32_t MemoryPool_AllocatedMemory(void)
{
	return pool.allocated;
}

uint32_t MemoryPool_AvailableMemory(void)
{
	return MEMORY_POOL_SIZE - pool.allocated;	
}

uint32_t MemoryPool_Size(void)
{
	return MEMORY_POOL_SIZE;
}

/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

