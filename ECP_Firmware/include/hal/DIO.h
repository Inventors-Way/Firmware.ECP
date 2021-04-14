/*
 * DIO.h
 *
 * Created: 14-04-2021 12:58:58
 *  Author: KristianHennings
 */ 
#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

enum Pin
{
	PIN_LED_DEBUG = 0,     ///< Debug Diode (PB7)
	PIN_EOL
};

/**
 * \brief Initialize the digital I/O
 * This function has the responsibility of initializing all pins on the microprocessor.
 *
 * \return void
 */
void DIO_Initialize(void);

void DIO_Run(void);

/**
 * \brief Set the value of a DIO pin
 * 
 * \param pin the pin to update the value for
 * \param value the new value for the pin if it is 0U the pin is set to low, otherwise it is set to high
 */
void DIO_SetPin(const enum Pin pin, const uint8_t value);

/**
 * \brief Get the value of a pin
 *
 * \param pin the pin to read the value for.
 * \return uint8_t value read from the pin, 0U if the pin is read as low, otherwise 1U if it is read as high. If the pin is between its low and high level the return value of this function is undefined.
 */
uint8_t DIO_GetPin(const enum Pin pin);

/** @}*/



#endif /* DIO_H_ */