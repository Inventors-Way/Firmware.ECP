/*
 * Stream.h
 *
 * Created: 14-04-2021 14:54:58
 *  Author: KristianHennings
 */ 


#ifndef STREAM_H_
#define STREAM_H_

   
/** 
 * \addtogroup Stream
 * @{
 */

   
#include <stdint.h>

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param data 
 */
void Stream_InsertUint8(uint8_t * const self, uint32_t pos, uint8_t data);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param data 
 */
void Stream_InsertInt8(uint8_t * const self, uint32_t pos, int8_t data);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param data 
 */
void Stream_InsertUint16(uint8_t * const self, uint32_t pos, uint16_t data);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param data 
 */
void Stream_InsertInt16(uint8_t * const self, uint32_t pos, int16_t data);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param data 
 */
void Stream_InsertUint32(uint8_t * const self, uint32_t pos, uint32_t data);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param data 
 */
void Stream_InsertInt32(uint8_t * const self, uint32_t pos, int32_t data);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @param size 
 * @param str 
 */
void Stream_InsertString(uint8_t * const self, uint32_t pos, int8_t size, char* str);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @return uint8_t 
 */
uint8_t  Stream_GetUint8(const uint8_t * const self, uint32_t pos);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @return int8_t 
 */
int8_t   Stream_GetInt8(const uint8_t * const self, uint32_t pos);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @return uint16_t 
 */
uint16_t Stream_GetUint16(const uint8_t * const self, uint32_t pos);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @return int16_t 
 */
int16_t  Stream_GetInt16(const uint8_t * const self, uint32_t pos);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @return uint32_t 
 */
uint32_t Stream_GetUint32(const uint8_t * const self, uint32_t pos);

/**
 * @brief 
 * 
 * @param self 
 * @param pos 
 * @return int32_t 
 */
int32_t  Stream_GetInt32(const uint8_t * const self, uint32_t pos);

/** @} */

#endif /* STREAM_H_ */