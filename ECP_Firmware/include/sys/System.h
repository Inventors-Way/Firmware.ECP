/*
 * System.h
 *
 * Created: 14-04-2021 13:02:50
 *  Author: KristianHennings
 */ 
 #include <stdint.h>
 #include <sys/DebugSignal.h>

#ifndef SYSTEM_H_
#define SYSTEM_H_

void System_Initialize(void);

void System_Run(void);

void System_HandleFatalError(void);

/**
 * @brief 
 * 
 * @param id 
 * @param format 
 * @param ... 
 */
void System_Printf(const char* format, ...);

/**
 * @brief 
 * 
 * @param code 
 * @param length 
 * @param data 
 */
void System_TransmitMessage(const uint8_t code, 
                            const uint8_t length, 
                            const uint8_t * const data);

#endif /* SYSTEM_H_ */