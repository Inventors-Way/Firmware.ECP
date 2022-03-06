/*
 * PeripheralHandler.c
 *
 * Created: 14-04-2021 13:05:05
 *  Author: KristianHennings
 */ 
 #include <hal/SerialPort.h>
 #include <sys/SystemConfig.h>
 #include <sys/Timer.h>
 #include <sys/System.h>
 #include <sys/DebugSignal.h>
 #include <srv/comm/ecp/PeripheralHandler.h>
 #include "Packet.h"
 #include <string.h>
 #include <hal/DIO.h>
 #include <hal/SPI.h>

/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

#define DATA_BUFFER_SIZE 64
uint8_t buffer[DATA_BUFFER_SIZE];

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
void PeripheralHandler_GetEndianness(PeripheralHandler* self);
void PeripheralHandler_Ping(PeripheralHandler* self);
void PeripheralHandler_SetDebugSignals(PeripheralHandler* self);

// FUNCTIONS INTENDED TO DEMONSTRATE HOW TO USE ECP FUNCTIONS
void PeripheralHandler_SimpleFunction(PeripheralHandler* self);
void PeripheralHandler_DataFunction(PeripheralHandler* self);

// FUNCTIONS INTEDED TO TEST THE HAL LAYER
void PeripheralHandler_SPITestFunction(PeripheralHandler* self);

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
         case GET_ENDIANNESS:
            PeripheralHandler_GetEndianness(self);
            break;
         case SET_DEBUG_SIGNAL:
            PeripheralHandler_SetDebugSignals(self);
            break;
			
		case SIMPLE_FUNCTION:
			PeripheralHandler_SimpleFunction(self);
			break;
	    case DATA_FUNCTION:
			PeripheralHandler_DataFunction(self);
			break;
			
		case SPI_TEST_FUNCTION:
			PeripheralHandler_SPITestFunction(self);
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
       const uint8_t data = SerialPort_Read();
       retValue = Packet_Add(&self->mRequest, data);
    }

    return retValue;
 }

void PeripheralHandler_DeviceIdentification(PeripheralHandler* self)
{
   if (self->mRequest.length > 0)
   {
      Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
      return;
   }

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
   if (self->mRequest.length > 0)
   {
      Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
      return;
   }

   Packet_Start(self->mRequest.code, sizeof(uint32_t));
   Packet_SendUint32(self->counter);
   Packet_End();
}

void PeripheralHandler_GetEndianness(PeripheralHandler* self)
{
   if (self->mRequest.length > 0)
   {
      Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
      return;
   }

	Packet_Start(self->mRequest.code, sizeof(uint16_t));
	Packet_SendUint16(1);
	Packet_End();
}

void PeripheralHandler_SetDebugSignals(PeripheralHandler* self)
{
   enum DebugSignal signals[NUMBER_OF_DEBUG_SIGNALS];

   if (self->mRequest.length != NUMBER_OF_DEBUG_SIGNALS * sizeof(uint32_t))
   {
      Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
      return;
   }

   for (uint8_t n = 0; n < NUMBER_OF_DEBUG_SIGNALS; ++n)
   {
      const enum DebugSignal signal = Packet_GetUint32(&self->mRequest, n * sizeof(uint32_t));
      signals[n] = signal < DEBUG_SIGNAL_EOL ? signal : DEBUG_SIGNAL_NONE;
   }

   DebugSignal_SetActive(signals);

   Packet_Acknowledge(&self->mRequest);
}

// FUNCTIONS INTENDED TO DEMONSTRATE HOW TO USE ECP FUNCTIONS

void PeripheralHandler_SimpleFunction(PeripheralHandler* self)
{
	if (self->mRequest.length != sizeof(int32_t))
	{
		Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
		return;
	}	
	
	Packet_Start(self->mRequest.code, sizeof(uint32_t));
	Packet_SendUint32(-Packet_GetInt32(&self->mRequest, 0));
	Packet_End();	
}

void PeripheralHandler_DataFunction(PeripheralHandler* self)
{
	if (self->mRequest.length == 0)
	{
		Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
		return;		
	}
	
	Packet_Start(self->mRequest.code, self->mRequest.length);
	
	for (uint16_t n = 0; n < self->mRequest.length; ++n)
	{
		Packet_SendUint8(self->mRequest.data[n] + 1);
	}
	
	Packet_End();
}

void PeripheralHandler_SPITestFunction(PeripheralHandler* self)
{
	if (self->mRequest.length == 0)
	{
		Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR);
		return;
	}
	
	if (self->mRequest.length > DATA_BUFFER_SIZE)
	{
		Packet_SendNotAcknowledge(&self->mRequest, INVALID_CONTENT_ERR + 1);
		return;
	}	
	
	SPI_Start(self->mRequest.length, self->mRequest.data, buffer);

	Packet_Start(self->mRequest.code, self->mRequest.length);
	Packet_SendData(self->mRequest.length, buffer);
	Packet_End();
}



