/*
 * Packet.h
 *
 * Created: 14-04-2021 16:11:03
 *  Author: KristianHennings
 */ 


#ifndef PACKET_H_
#define PACKET_H_


#include <sys/SystemConfig.h>
#include <tools/Stream.h>
#include <stdint.h>

/** 
 * \addtogroup Packet
 *  @{
 */

/** \addtogroup Packet
 *  @{
 */

#include <stdint.h>
#include <sys/SystemConfig.h>


enum LengthEncoding
{
   LENGTH_UINT8  = 0x00,
   LENGTH_UINT16 = 0x01,
   LENGTH_UINT32 = 0x02
};

enum ChecksumType
{
   CHKSUM_NONE     = 0x00,
   CHKSUM_ADDITIVE = 0x04,
   CHKSUM_CRC8CCIT = 0x08
};

typedef struct
{
   // FRAME FORMAT
   uint8_t extended;                     //< 0: Standard Frame, 1: Extended Frame
   enum LengthEncoding lengthEncoding;
   enum ChecksumType checksumType;
   uint8_t addressEnabled;

   // FRAME LAYOUT FOR EXTENDED FRAMES
   uint8_t lengthBuffer[2];

   uint8_t code;
   uint8_t address;
   uint16_t length;
   uint8_t checksum;
   uint8_t data[MAX_PACKET_SIZE];
   
   // Private variables
   uint8_t state;
   uint16_t count;
} Packet; 

void Packet_Initialize(Packet* self);

/**
 * \brief Add a newly received byte to the packet
 * This function adds a newly received byte to the packet. This involves
 * destuffing and inserting it into the correct place in the packet.
 *
 * \param[in] self a reference to self
 * \param[in] data the received byte from the master to process
 * \return 1 if a packet has been received, otherwise 0
 */
uint8_t Packet_Add(Packet* self, const uint8_t data);

void Packet_Start(const uint8_t code, const uint32_t length);

void Packet_SendData(const uint8_t size, const void * const vdata);

inline void Packet_SendUint8(const uint8_t data) { Packet_SendData(sizeof(uint8_t), &data); }
inline void Packet_SendInt8(const int8_t data) { Packet_SendData(sizeof(int8_t), &data); }
inline void Packet_SendUint16(const uint16_t data) { Packet_SendData(sizeof(uint16_t), &data); }
inline void Packet_SendInt16(const int16_t data) { Packet_SendData(sizeof(int16_t), &data); }
inline void Packet_SendUint32(const uint32_t data) { Packet_SendData(sizeof(uint32_t), &data); }
inline void Packet_SendInt32(const int32_t data) { Packet_SendData(sizeof(int32_t), &data); }
void Packet_SendString(const uint8_t size, char * str);

void Packet_End(void);

inline uint8_t Packet_GetUint8(Packet* self, uint8_t pos) { return pos < self->length ? self->data[pos] : 0U; }
inline int8_t Packet_GetInt8(Packet* self, uint8_t pos) { return pos < self->length ? *((int8_t *) &self->data[pos]) : 0; }
inline uint16_t Packet_GetUint16(Packet* self, uint8_t pos) { return pos < self->length ? *((uint16_t *) &self->data[pos]) : 0U; }
inline int16_t Packet_GetInt16(Packet* self, uint8_t pos) { 	return pos < self->length ? *((int16_t *) &self->data[pos]) : 0; }
inline uint32_t Packet_GetUint32(Packet* self, uint8_t pos) { return pos < self->length ? *((uint32_t *) &self->data[pos]) : 0U; }
inline int32_t Packet_GetInt32(Packet* self, uint8_t pos) { return pos < self->length ? *((int32_t *) &self->data[pos]) : 0; }

void Packet_SendNotAcknowledge(Packet* self, const uint8_t errorCode);

void Packet_Acknowledge(Packet* self);

/** @}*/

/** @} */




#endif /* PACKET_H_ */