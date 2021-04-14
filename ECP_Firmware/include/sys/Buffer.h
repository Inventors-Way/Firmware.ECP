/*
 * Buffer.h
 *
 * Created: 14-04-2021 13:01:20
 *  Author: KristianHennings
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_


/** \addtogroup Buffer 
 *  @{
 * \brief Implements a circular buffer.
 */

#include <stdint.h>

/**
 * @brief 
 * 
 */
typedef struct 
{
   uint32_t size;        ///< number of elements in the circular buffer
   uint32_t elementSize; ///< size of each element in the circular buffer
   uint32_t start;       ///< start index to the first data byte in the buffer
   uint32_t end;         ///< end index to the last data byte in the buffer
   uint32_t count;       ///< keeps track of how many data bytes that are currently in the buffer
   
   void* data;           ///< Pointer to the memory that holds the circular buffer.
}  Buffer;

/**
 * \brief Create the buffer
 * \details
 * This creates creates a buffer by initializing the Buffer structure, and allocate
 * the required memory on the heap.
 * 
 * \param self pointer to self
 * \param size number of elements in the circular buffer
 * \param elementSize size of each element in the circular buffer
 * \return 1 if successfull, 0U if not
 */
uint8_t Buffer_Create(Buffer* const self, const uint32_t size, const uint32_t elementSize);

/**
 * \brief Initialize the buffer
 * \details
 * This will reset the buffer, which will clear any pending elements.
 * 
 * \param self pointer to self
 * \param size the size of the buffer
 */
void Buffer_Initialize(Buffer* const self);

/**
 * \brief Check if the buffer is empty
 * 
 * \param self pointer to self
 * \return uint8_t 1U if the buffer is empty, otherwise 0U
 */
uint8_t Buffer_IsEmpty(const Buffer* const self);

/**
 * \brief Check if the buffer is full
 * 
 * \param self pointer to self
 * \return uint8_t 1U if the buffer is full, otherwise 0U
 */
uint8_t Buffer_IsFull(const Buffer* const self);

/**
 * \brief Write a byte to the buffer
 * \details
 * This will attempt to write a byte to the buffer. If the buffer is 
 * full then the byte is discarded and the function call will have 
 * no effect.
 *
 * \param self pointer to self
 * \return a pointer to the data that should be inserted into the buffer, or 0U if the buffer is full
 */
void* Buffer_Write(Buffer* const self);

/**
 * \brief Read a byte from the buffer
 * \details
 * This will read and remove a byte from the buffer. 
 * Consequently, after this call the number of bytes in the buffer will be decremented by one.
 *
 * \param self pointer to self
 * \return a pointer to the data to be read from the buffer, or 0U if the buffer is empty
 */
void* Buffer_Read(Buffer* const self);

/** @}*/

#endif /* BUFFER_H_ */