/*
 * SPI.h
 *
 * Created: 05/03/2022 16.19.12
 *  Author: KristianHennings
 */ 
#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void SPI_Start(uint16_t length,
               uint8_t *txData,
               uint8_t *rxData);


#endif /* SPI_H_ */