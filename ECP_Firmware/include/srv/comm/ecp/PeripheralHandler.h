/*
 * PeripheralHandler.h
 *
 * Created: 14-04-2021 13:03:44
 *  Author: KristianHennings
 */ 

#include <stdint.h>

#ifndef PERIPHERALHANDLER_H_
#define PERIPHERALHANDLER_H_

void PeripheralHandler_Initialize(void);

void PeripheralHandler_Run(void);

void PeripheralHandler_Printf(char* str);

void PeripheralHandler_TransmitMessage(const uint8_t code, const uint8_t length, const uint8_t * const data);

#endif /* PERIPHERALHANDLER_H_ */