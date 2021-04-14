/*
 * SerialPort.h
 *
 * Created: 14-04-2021 12:58:25
 *  Author: KristianHennings
 */ 
#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <stdint.h>

/** \addtogroup SERIAL_PORT SerialPort 
 *  @{
 */

/**
 * \brief Write a sequence of bytes to the serial port
 *
 * \param data the data to send over the serial communication line
 */
void SerialPort_Write(const uint8_t data);

/**
 * \brief Check if there is pending bytes in the RX buffer
 * \return uint8_t 1U if there is one or more pending bytes, 0U otherwise
 */
uint8_t SerialPort_IsPending(void); // { return (UCSR0A &(1<<RXC0)) != 0; }

/**
 * \brief Retrieve a byte from the RX buffer
 * \return uint8_t a byte from the RX buffer. If there is no pending bytes this function will return 0U
 */
uint8_t SerialPort_Read(void); // { return UDR0; }



/** @}*/



#endif /* SERIALPORT_H_ */