/*
* SPI_Implementation.c
*
* Created: 05/03/2022 16.21.37
*  Author: KristianHennings
*/
#include <hal/SPI.h>
#include "SPI_Internal.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <sys/System.h>

/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

#define DAC_LDAC_HIGH()         PORTF  |=  _BV(PF2)
#define DAC_LDAC_LOW()          PORTF  &= ~_BV(PF2)

#define CS_HIGH()               PORTB  |=  _BV(PB0)
#define CS_LOW()                PORTB  &= ~_BV(PB0)

#define DISABLE_SPI_INTERRUPT() SPCR |= (1 << SPIE);
#define ENABLE_SPI_INTERRUPT()  SPCR &= ~(1 << SPIE);

struct SPI *current;
uint16_t count;

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void SPI_Start(uint16_t length,
               uint8_t *txData,
               uint8_t *rxData)
{
	if (txData == 0U)
	{
		System_HandleFatalError();
	}
	
	for (uint16_t n = 0; n < length; ++n)
	{
		SPDR = txData[n];
		while (!(SPSR & (1 << SPIF)));
		
		if (rxData != 0U)
		{
			rxData[n] = SPDR;			
		}
	}
}

/******************************************************************************
*                                                                            *
*                       Internal Function Implementation                     *
*                                                                            *
******************************************************************************/

void SPI_Initialize(void)
{
	current = 0U;
	
	// SPCR - SPI Control Register
	//
	// Bit.   7      6     5      4      3      2      1      0
	// 0x2C [ SPIE | SPE | DORD | MSTR | CPOL | CPHA | SPR1 | SPR0 ]
	//
	// SPIE       : SPI Interrupt Enable
	//              Setting this bit to ONE(1) causes the SPI interrupt to be executed, and if the Global Interrupt
	//              Enable bit in SREG is set.
	// SPE        : SPI Enable
	//              Setting this bit to ONE(1) enables SPI.
	// DORD       : Data Order
	//              1: LSB of the data word is transmitted first.
	//              0: MSB of the data word is transmitted first
	// MSTR       : Master/Slave Select
	//              1: The SPI operates as a master.
	//              0: The SPI operates as a slave.
	// CPOL       : Clock Polarity
	//              Value of the SCK when the SPI is idle.
	//              0: Leading clock edge (Rising).
	//              1: Leading clock edge (Falling).
	// CPHA       : Clock Phase
	//              Determine if data is sampled on the leading (first) or trailing (last) edge of SCK.
	//              0: Sampled on leading edge
	//              1: Sampled on trailing edge
	// SPR1, SPR0 : SPI Clock Rate Select
	//              Determine SCL clock rate together with the SPI2X bit in SPSR (see page 197 in the datasheet)
	SPCR = (0 << SPIE) | (1 << SPE) | (0 << DORD) | (1 << MSTR) | (0 << CPOL) | (0 << CPHA) | (0 << SPR1) | (0 << SPR0);
	
	// SPSR - SPI Status Register
	//
	// Bit.   7      6      5   4   3   2   1   0
	// 0x2C [ SPIF | WCOL | - | - | - | - | - | SPI2X ]
	//
	// SPIF  : SPI Interrupt Flag
	// WCOL  : Write COLision flag
	// SPI2X : Double SPI Bit
	SPSR = (1 << SPI2X);
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/

