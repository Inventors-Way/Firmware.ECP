/*
 * DIO.h
 *
 * Created: 14-04-2021 12:58:58
 *  Author: KristianHennings
 */ 
#ifndef DIO_H_
#define DIO_H_

#include <stdint.h>

#ifdef AVR

#include <avr/io.h>

#define D14_HIGH()   PORTJ  |=  _BV(PJ1)
#define D14_LOW()    PORTJ  &= ~_BV(PJ1)
#define D15_HIGH()   PORTJ  |=  _BV(PJ0)
#define D15_LOW()    PORTJ  &= ~_BV(PJ0)
#define D16_HIGH()   PORTH  |=  _BV(PH1)
#define D16_LOW()    PORTH  &= ~_BV(PH1)
#define D17_HIGH()   PORTH  |=  _BV(PH0)
#define D17_LOW()    PORTH  &= ~_BV(PH0)

#define D18_READ()   ((PIND & (1 << PIND3)) != 0) 
#define D19_READ()   ((PIND & (1 << PIND2)) != 0) 
#define D20_READ()   ((PIND & (1 << PIND1)) != 0) 
#define D21_READ()   ((PIND & (1 << PIND0)) != 0) 

#endif
#ifdef WIN32

#endif

enum Pin
{
	// Public DIOs
	PIN_D14 = 0,
	PIN_D15,
	PIN_D16,
	PIN_D17,
	PIN_D18,
	PIN_D19,
	PIN_D20,
	PIN_D21,
	
	// Internal DIOs used by ECP
	PIN_DEBUG_OUT01,     ///< Debug Diode (PB7) [Arduino: D13 ]
    PIN_DEBUG_OUT02,         ///< Debug Diode (PB6) [Arduino: D12 ]
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

enum Pin DIO_GetDebugPin(const uint8_t number);

/** @}*/



#endif /* DIO_H_ */