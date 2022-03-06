/*
 * SPI.h
 *
 * Created: 05/03/2022 16.19.12
 *  Author: KristianHennings
 */ 
#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

struct SPI
{
	uint16_t length;
	uint8_t *rxData;
	uint8_t *txDate;
	
	void (*callback)(void *owner);
	void *owner;
};

uint8_t SPI_Start(struct SPI * action);


#endif /* SPI_H_ */