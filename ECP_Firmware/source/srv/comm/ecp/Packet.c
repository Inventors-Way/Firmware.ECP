/*
 * Packet.c
 *
 * Created: 14-04-2021 16:11:13
 *  Author: KristianHennings
 */ 
 #include "Packet.h"
 #include <hal/SerialPort.h>
 #include <string.h>
 #include <sys/System.h>

 /******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

 #define DLE 0xFF
 #define STX 0xF1
 #define ETX 0xF2

 #define WAITING_FOR_DLE   0x01
 #define WAITING_FOR_STX   0x02
 #define RECEIVING_DATA    0x03
 #define WAITING_FOR_ETX   0x04

 void Packet_HandleWaitingForDLE(Packet* self, uint8_t data);
 void Packet_HandleWaitingForSTX(Packet* self, uint8_t data);
 void Packet_HandleReceivingData(Packet* self, uint8_t data);
 uint8_t Packet_HandleWaitingForETX(Packet* self, uint8_t data);
 void Packet_HandleAddData(Packet* self, uint8_t data);

 void Packet_SendDataByte(uint8_t data);

 /******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

 void Packet_Initialize(Packet* self)
 {
    self->count = 0;
    self->state = WAITING_FOR_DLE;
 }

 uint8_t Packet_Add(Packet* self, const uint8_t data)
 {
    uint8_t retValue = 0;
    
    switch (self->state)
    {
       case WAITING_FOR_DLE:
       Packet_HandleWaitingForDLE(self, data);
       break;

       case WAITING_FOR_STX:
       Packet_HandleWaitingForSTX(self, data);
       break;

       case RECEIVING_DATA:
       Packet_HandleReceivingData(self, data);
       break;

       case WAITING_FOR_ETX:
       retValue = Packet_HandleWaitingForETX(self, data);
       break;
    }
    
    return retValue;
 }

 void Packet_Start(const uint8_t code, const uint32_t length)
 {
    SerialPort_Write(DLE);
    SerialPort_Write(STX);
    
    Packet_SendDataByte(code);
    Packet_SendDataByte(length);
 }

 void Packet_SendData(const uint16_t size, const void * const vdata)
 {
    const uint8_t * const data = (uint8_t *) vdata;
    
    for (uint16_t n = 0; n < size; ++n)
    {
       Packet_SendDataByte(data[n]);
    }
 }

 void Packet_SendString(const uint8_t size, char * str)
 {
    uint8_t len = strlen(str);
    
    for (uint8_t n = 0; n < size; ++n)
    {
       Packet_SendDataByte(n < len ? str[n] : 0);
    }
 }

 void Packet_End(void)
 {
    SerialPort_Write(DLE);
    SerialPort_Write(ETX);
 }

 void Packet_SendNotAcknowledge(Packet* self, const uint8_t errorCode)
 {
    SerialPort_Write(DLE);
    SerialPort_Write(STX);
    
    Packet_SendDataByte(0U);
    Packet_SendDataByte(1U);
    Packet_SendDataByte(errorCode);
    
    SerialPort_Write(DLE);
    SerialPort_Write(ETX);
 }

 void Packet_Acknowledge(Packet* self)
 {
    SerialPort_Write(DLE);
    SerialPort_Write(STX);
    
    Packet_SendDataByte(self->code);
    Packet_SendDataByte(0U);
    
    SerialPort_Write(DLE);
    SerialPort_Write(ETX);
 }


 /******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

 void Packet_SendDataByte(uint8_t data)
 {
    if (data == DLE)
    {
       SerialPort_Write(DLE);
       SerialPort_Write(DLE);
    }
    else
    {
       SerialPort_Write(data);
    }
 }

 void Packet_HandleWaitingForDLE(Packet* self, uint8_t data)
 {
    if (data == DLE)
    {
       self->state = WAITING_FOR_STX;
    }
 }

 void Packet_HandleWaitingForSTX(Packet* self, uint8_t data)
 {
    if (data == STX)
    {
       self->state = RECEIVING_DATA;
       self->count = 0;
    }
    else if (data != DLE)
    {
       self->state = WAITING_FOR_DLE;
    }
 }

 void Packet_HandleReceivingData(Packet* self, uint8_t data)
 {
    if (data != DLE)
    {
       Packet_HandleAddData(self, data);
    }
    else
    {
       self->state = WAITING_FOR_ETX;
    }
 }

 uint8_t Packet_HandleWaitingForETX(Packet* self, uint8_t data)
 {
    uint8_t retValue = 0U;
    
    if (data == DLE)
    {
       Packet_HandleAddData(self, DLE);
       self->state = RECEIVING_DATA;
    }
    else if (data == ETX)
    {
       self->state = WAITING_FOR_DLE;
       retValue = 1U;
    }
    else if (data == STX)
    {
       self->state = RECEIVING_DATA;
       self->count = 0;
    }
    else
    {
       self->state = WAITING_FOR_DLE;
    }
    
    return retValue;
 }

 inline uint16_t Packet_GetLengthSize(Packet* self)
 {
    switch (self->lengthEncoding)
    {
       case LENGTH_UINT8: return 1;
       case LENGTH_UINT16: return 2;
       default: return 2;
    }
 }

 inline uint16_t Packet_GetAddressOffset(Packet* self)
 {
    return Packet_GetLengthSize(self) + 2;
 }

 inline uint16_t Packet_GetDataOffset(Packet* self)
 {
    int retValue = Packet_GetLengthSize(self) + 2;

    if (self->addressEnabled)
    {
       retValue += 1;
    }

    return retValue;
 }

 inline uint16_t Packet_GetChecksumOffset(Packet* self)
 {
    return Packet_GetDataOffset(self) + self->length;
 }

 inline uint16_t Packet_GetPacketSize(Packet* self)
 {
    if (self->extended)
    {
       return self->checksumType == CHKSUM_NONE ? Packet_GetChecksumOffset(self) : Packet_GetChecksumOffset(self) + 1;
    }
    else
    {
       return self->length + 2;
    }
 }


 void Packet_HandleAddData(Packet* self, uint8_t data)
 {
    if (self->count == 0)
    {
       self->code = data;
    }
    else if (self->count == 1)
    {
       if (data < 128) // Standard Frame
       {
          self->length = data;
          self->extended = 0;
       }
       else // Extended Frame
       {
          const enum LengthEncoding lengthEncoding = (enum LengthEncoding) (0x03 & data);
          const enum ChecksumType chksumType = (enum ChecksumType) (0x0C & data);

          self->extended = 1;

          // Parse the length encoding
          switch (lengthEncoding)
          {
             case LENGTH_UINT8:
             case LENGTH_UINT16:
             self->lengthEncoding = lengthEncoding;
             break;

             case LENGTH_UINT32: // Not implemented on this system
             default:
             self->state = WAITING_FOR_DLE; // Error skip frame and wait for the next one.
             break;
          }

          switch (chksumType)
          {
             case CHKSUM_NONE:
             case CHKSUM_CRC8CCIT:
             self->checksumType = chksumType;
             break;

             case CHKSUM_ADDITIVE: // Not implemented on this system.
             default:
             self->state = WAITING_FOR_DLE; // Error skip frame and wait for the next one.
             break;
          }

          self->addressEnabled = (0x10 & data) != 0;
          self->length = Packet_GetDataOffset(self);
       }
    }
    else if (self->count < Packet_GetPacketSize(self))
    {
       if (self->extended)
       {
          const uint16_t dataOffset = Packet_GetDataOffset(self);

          if (self->count < Packet_GetAddressOffset(self)) // LENGTH FIELD
          {
             switch (self->lengthEncoding)
             {
                case LENGTH_UINT8:
                self->length = data;
                break;
                case LENGTH_UINT16:
                self->lengthBuffer[self->count - 2] = data;

                if ((self->count - 2) == 1)
                {
                   self->length = *((uint16_t *) self->lengthBuffer);
                }
                break;
                default:
                self->state = WAITING_FOR_DLE; // Error skip frame and wait for the next one.
                break;
             }
          }
          else if ((self->count < dataOffset) && self->addressEnabled) // ADDRESS FIELD
          {
             self->address = data;
          }
          else if ((self->count < Packet_GetChecksumOffset(self))) // DATA FIELD
          {
             self->data[self->count - dataOffset] = data;
          }
          else if (self->checksumType != CHKSUM_NONE)
          {
             self->checksum = data;
          }
       }
       else
       {
          self->data[self->count - 2] = data;
       }
    }

    if (self->count < UINT16_MAX)
    {
       ++self->count;
    }
 }
