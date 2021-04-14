/*
 * HalInternal.h
 *
 * Created: 14-04-2021 13:43:19
 *  Author: KristianHennings
 */ 


#ifndef HALINTERNAL_H_
#define HALINTERNAL_H_

#ifdef F_CPU
#undef F_CPU
#endif

#define F_CPU          16000000UL ///< Clock frequency of the processor

/**
 * \brief Initializes the serial port
 *
 */
void SerialPort_Initialize(void);

void TimerTick_Initialize(void);
void TimerTick_Run(void);

void DIO_Initialize(void);


#endif /* HALINTERNAL_H_ */