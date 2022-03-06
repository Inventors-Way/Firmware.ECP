/*
 * SPI_Implementation.c
 *
 * Created: 05/03/2022 16.21.37
 *  Author: KristianHennings
 */ 
#include <hal/SPI.h>

/******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

struct SPIAction *current;

/******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

void SPI_Initialize(void)
{
	current = NULL;
}

uint8_t SPI_Start(struct SPIAction * action)
{
	if (action == NULL) return 0;
	if (current != NULL) return 0;
	
	return 1;	
}

/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/