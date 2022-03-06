/*
 * SerialPort.c
 *
 * Created: 14-04-2021 13:04:29
 *  Author: KristianHennings
 */ 
#include <hal/SerialPort.h>
#include <sys/Buffer.h>
#include <sys/SystemConfig.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <hal/DIO.h>

#include "HalInternal.h"

/******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

/** \addtogroup SERIAL 
 *  @{
 */

 

#define BAUD_PRESCALLER ((F_CPU/16/BAUDRATE) - 1)

Buffer rxBuffer;
uint8_t rxMemory[RX_BUFFER_SIZE];

Buffer txBuffer;
uint8_t txMemory[TX_BUFFER_SIZE];

uint8_t txComplete;

/******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/
 
void SerialPort_Initialize(void)
{
   Buffer_Create(&rxBuffer, rxMemory, RX_BUFFER_SIZE, sizeof(uint8_t));
   Buffer_Initialize(&rxBuffer);

   Buffer_Create(&txBuffer, txMemory, TX_BUFFER_SIZE, sizeof(uint8_t));
   Buffer_Initialize(&txBuffer);

   // USART0 initialization
   // Communication Parameters: 8 Data, 1 Stop, No Parity
   // USART0 Receiver: On
   // USART0 Transmitter: On
   // USART0 Mode: Asynchronous
   // USART0 Baud Rate: 38400
   UCSR0A = (0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
   UCSR0B = (1<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
   UCSR0C = (0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
   UBRR0 = BAUD_PRESCALLER;
   
   txComplete = 1;
}

void SerialPort_Write(const uint8_t data)
{
	if (txComplete)
	{
	   UDR0 = data;
	   txComplete = 0;
	}
	else
	{
		UCSR0B = (1<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
		
		if (!Buffer_IsFull(&txBuffer))
		{
			uint8_t * const ptr = Buffer_Write(&txBuffer);	
			*ptr = data;		
		}

		UCSR0B = (1<<RXCIE0) | (1<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
	}
}

uint8_t SerialPort_IsPending(void)
{
   return rxBuffer.count > 0;
}

uint8_t SerialPort_Read(void)
{
   uint8_t retValue = 0;
   
   UCSR0B = (0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
   if (rxBuffer.count > 0)
   {
      const uint8_t * const data = (uint8_t *) Buffer_Read(&rxBuffer);
      retValue = *data;

   }
   
   if (txComplete)
   {
	   UCSR0B = (1<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);	   
   }
   else
   {
	   UCSR0B = (1<<RXCIE0) | (1<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
   }
   
   return retValue;
}

/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

ISR(USART0_RX_vect)
{
   if (!Buffer_IsFull(&rxBuffer))
   {   
      uint8_t * const data = Buffer_Write(&rxBuffer);
      *data = UDR0;
   }
}

ISR(USART0_TX_vect)
{
	if (!Buffer_IsEmpty(&txBuffer))
	{
		uint8_t const * const data = (uint8_t *) Buffer_Read(&txBuffer);
		UDR0 = *data;
	}
	else
	{
		UCSR0B = (1<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);		
		txComplete = 1;
	}
}