/*
 * SPI.h
 *
 * Created: 05/03/2022 16.19.12
 *  Author: KristianHennings
 */ 
#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

enum SPI_DORD 
{
	DORD_LSB = 0,
	DORD_MSB	
};

enum SPI_CPOL
{
	CPOL0 = 0,
	CPOL1	
};

enum SPI_CPHA
{
	CPHA0 = 0,
	CPHA1
};

enum SPI_CLK
{
	CLKDIV_02 = 0,
	CLKDIV_04,
	CLKDIV_08,	
	CLKDIV_16,
	CLKDIV_32,
	CLKDIV_64,
	CLKDIV_128
};

uint8_t SPI_Initialize(const enum SPI_DORD dord,
                       const enum SPI_CPOL cpol,
					   const enum SPI_CPHA cpha,
					   const enum SPI_CLK clk);

void SPI_Start(uint16_t length,
               uint8_t *txData,
               uint8_t *rxData);


#endif /* SPI_H_ */