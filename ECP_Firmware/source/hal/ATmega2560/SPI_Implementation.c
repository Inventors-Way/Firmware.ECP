/*
* SPI_Implementation.c
*
* Created: 05/03/2022 16.21.37
*  Author: KristianHennings
*/
#include <hal/SPI.h>
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

uint8_t SPI_Initialize(const enum SPI_DORD dord,
                       const enum SPI_CPOL cpol,
                       const enum SPI_CPHA cpha,
                       const enum SPI_CLK clk)
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
	//
	// SPSR - SPI Status Register
	//
	// Bit.   7      6      5   4   3   2   1   0
	// 0x2C [ SPIF | WCOL | - | - | - | - | - | SPI2X ]
	//
	// SPIF  : SPI Interrupt Flag
	// WCOL  : Write COLision flag
		
	SPCR = 0; // Reset the SPI Control Register
	SPSR = 0; // Reset the SPI Status Register
	
	switch (dord)
	{
		case DORD_MSB: SPCR |= (1 << DORD); break;
		case DORD_LSB: SPCR |= (0 << DORD); break;
		default: return 0;		
	}
	
	switch (cpol)
	{
		case CPOL1: SPCR |= (1 << CPOL); break;
		case CPOL0: SPCR |= (0 << CPOL); break;
		default: return 0;
	}
	
	switch (cpha)
	{
		case CPHA1: SPCR |= (1 << CPHA); break;
		case CPHA0: SPCR |= (0 << CPHA); break;
		default: return 0;		
	}
	
	switch (clk)
	{
	   case CLKDIV_02:  SPCR |= (0 << SPR1) | (0 << SPR0); SPSR |= (1 << SPI2X); break;
	   case CLKDIV_04:  SPCR |= (0 << SPR1) | (0 << SPR0); SPSR |= (0 << SPI2X); break;
	   case CLKDIV_08:  SPCR |= (0 << SPR1) | (1 << SPR0); SPSR |= (1 << SPI2X); break;
	   case CLKDIV_16:  SPCR |= (0 << SPR1) | (1 << SPR0); SPSR |= (0 << SPI2X); break;
	   case CLKDIV_32:  SPCR |= (0 << SPR1) | (1 << SPR0); SPSR |= (1 << SPI2X); break;
	   case CLKDIV_64:  SPCR |= (1 << SPR1) | (1 << SPR0); SPSR |= (1 << SPI2X); break;
	   case CLKDIV_128: SPCR |= (1 << SPR1) | (1 << SPR0); SPSR |= (0 << SPI2X); break;
	   default: return 0;
	}
	
	SPCR |= (1 << SPE) | (1 << MSTR);
	
	return 1;
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/

