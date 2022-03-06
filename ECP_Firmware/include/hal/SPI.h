/*
 * SPI.h
 *
 * Created: 05/03/2022 16.19.12
 *  Author: KristianHennings
 */ 
#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

struct SPIAction
{
	uint8_t length;
	uint8_t *rxData;
	uint8_t *txDate;
};

void SPI_Initialize(void);

uint8_t SPI_Start(struct SPIAction * action);


#endif /* SPI_H_ */