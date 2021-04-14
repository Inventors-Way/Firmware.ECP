/*
 * PeripheralHandler.c
 *
 * Created: 14-04-2021 13:05:05
 *  Author: KristianHennings
 */ 
 #include <hal/SerialPort.h>
 #include <sys/SystemConfig.h>
 #include <srv/comm/ecp/PeripheralHandler.h>
 #include "Packet.h"
 #include <string.h>

/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

typedef struct {
   Packet mRequest;
   uint32_t counter;
} PeripheralHandler;

PeripheralHandler peripheralHandler;

/**
* \brief Polls the serial port and check if a request has been received
*
* \param self a reference to self
*
* \return uint8_t return 1 if a request is available otherwise 0
*/
uint8_t PeripheralHandler_IsRequestAvailable(PeripheralHandler* self);

void PeripheralHandler_DeviceIdentification(PeripheralHandler* self);

void PeripheralHandler_Ping(PeripheralHandler* self);

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void PeripheralHandler_Initialize(void)
{
   Packet_Initialize(&peripheralHandler.mRequest);
   peripheralHandler.counter = 0U;
}

void PeripheralHandler_Run(void)
{
   PeripheralHandler* self = &peripheralHandler;

   if (PeripheralHandler_IsRequestAvailable(self))
   {
      ++(self->counter);

      switch (self->mRequest.code)
      {
         case DEVICE_IDENTIFICATION:
            PeripheralHandler_DeviceIdentification(self);
            break;
         case PING:
            PeripheralHandler_Ping(self);
            break;

         default:
            Packet_SendNotAcknowledge(&self->mRequest, UNKNOWN_FUNCTION_ERR);
            break;
      }
      
      Packet_Initialize(&self->mRequest);
   }
}

void PeripheralHandler_TransmitMessage(const uint8_t code, const uint8_t length, const uint8_t * const data)
{
   Packet_Start(code, length);
   Packet_SendData(length, data);
   Packet_End();
}

void PeripheralHandler_Printf(char* str)
{
   const uint8_t length = strlen(str);
   
   Packet_Start(PRINTF_MSG, length);
   Packet_SendData(length, (uint8_t *) str);
   Packet_End();
}


 /******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

 uint8_t PeripheralHandler_IsRequestAvailable(PeripheralHandler* self)
 {
    uint8_t retValue = 0;

    while (SerialPort_IsPending() && !retValue)
    {
       retValue = Packet_Add(&self->mRequest, SerialPort_Read());
    }

    return retValue;
 }

void PeripheralHandler_DeviceIdentification(PeripheralHandler* self)
{
   Packet_Start(self->mRequest.code, 64);
   Packet_SendUint32(MANUFACTURER_ID);
   Packet_SendUint16(DEVICE_TYPE);        // Device Type
   Packet_SendUint32(1); // Serial number
   Packet_SendUint8(MAJOR_REVISION);     // Major Revision
   Packet_SendUint8(MINOR_REVISION);
   Packet_SendUint8(PATCH_REVISION);
   Packet_SendUint8(ENGINEERING_REVISION);
   Packet_SendUint16(UINT16_MAX);    // Program checksum
   Packet_SendString(24, MANUFACTORER_NAME);
   Packet_SendString(24, DEVICE_NAME);
   Packet_End();
}

void PeripheralHandler_Ping(PeripheralHandler* self)
{
   Packet_Start(self->mRequest.code, sizeof(uint32_t));
   Packet_SendUint32(self->counter);
   Packet_End();

   ++self->counter;
}
