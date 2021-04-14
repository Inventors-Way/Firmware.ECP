/*
* System.c
*
* Created: 14-04-2021 13:06:11
*  Author: KristianHennings
*/
#include <sys/System.h>
#include <hal/DIO.h>
#include <srv/comm/ecp/PeripheralHandler.h>

/******************************************************************************
*                                                                            *
*                       Private Function Declaration                         *
*                                                                            *
******************************************************************************/

/**
* @addtogroup PSystem
* @{
*/

/** @} */

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void System_Initialize(void)
{
   PeripheralHandler_Initialize();
}

void System_Run(void)
{
   PeripheralHandler_Run();
}

void System_HandleFatalError(void)
{
   while (1)
   {
      // Halt the processor

      // S (Morse Code)
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 1);

      // SPACE
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);

      // O (Morese Code)
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 1);

      // SPACE
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);

      // S (Morse Code)
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 1);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 1);

      // SPACE
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);

      // SPACE
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);

      // SPACE
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
      DIO_SetPin(PIN_LED_DEBUG, 0);
   }
}

/**
* @brief
*
* @param id
* @param format
* @param ...
*/
void System_Printf(const char* format, ...)
{

}

/**
* @brief
*
* @param code
* @param length
* @param data
*/
void System_TransmitMessage(const uint8_t code,
                            const uint8_t length,
                            const uint8_t * const data)
{
   PeripheralHandler_TransmitMessage(code, length, data);
}

void System_SetActiveDebugSignal(const enum DebugSignal* signal)
{

}

void System_DebugOut(const enum DebugSignal signal, const uint8_t value)
{

}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/

