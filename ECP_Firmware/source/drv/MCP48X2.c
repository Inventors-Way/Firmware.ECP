/*
 * MCP48X2.c
 *
 * Created: 08/03/2022 11.12.58
 *  Author: KristianHennings
 */ 
#include <drv/MCP48X2.h>
#include <hal/DIO.h>
#include <hal/SPI.h>

/******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

#define DAC_LDAC_HIGH()   D14_HIGH()
#define DAC_LDAC_LOW()    D14_LOW()

#define CS_HIGH()         D15_HIGH()
#define CS_LOW()          D15_LOW()

void MCP48X2_WriteChannel(const uint8_t config, uint16_t value);


/******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

void MCP48X2_Initialize(void)
{
   CS_HIGH();
   DAC_LDAC_HIGH();

   MCP48X2_Update(0, 0);   
}

void MCP48X2_Update(const uint16_t ch01, const uint16_t ch02)
{
   CS_LOW();
   MCP48X2_WriteChannel(0b00010000, ch01); 
   CS_HIGH();
   
   CS_LOW();
   MCP48X2_WriteChannel(0b10010000, ch02);
   CS_HIGH();
   
   DAC_LDAC_LOW();
   DAC_LDAC_HIGH();
}

/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

void MCP48X2_WriteChannel(const uint8_t config, uint16_t value)
{
	uint16_t dac_data = 0;
   uint8_t txData[2];

	if (value > 4095)
   {
	   value = 4095;
   }   

	dac_data |= value;
	dac_data |= ((uint16_t) config) << 8;

	txData[0] = (dac_data >> 8);
	txData[1] = (dac_data & 0x00FF);	
   
   SPI_Start(2, txData, 0U);
}