/*
 * TimerTick.c
 *
 * Created: 14-04-2021 13:04:42
 *  Author: KristianHennings
 */ 

 #include <hal/TimerTick.h>
 #include <sys/SystemConfig.h>
 #include <sys/System.h>
 #include <avr/interrupt.h>
 #include <avr/io.h>

 #include "HalInternal.h"

 /******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

 #define F1_TIMER 1000
 #define OCR_REG1 (F_CPU/(F1_TIMER))

 volatile uint32_t timerTicks;
 uint32_t currentTimerTicks;

 /******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

 void TimerTick_Initialize(void)
 {
   // Configure Timer 1 (16 bit)
   OCR1A   = OCR_REG1;
   TCCR1A  = 0;                          // set entire TCCR1A register to 0
   TCCR1B  = (1 << WGM12) | (1 << CS10); // CTC mode + 1 x prescaler
   TIMSK1 |= (1 << OCIE1A);              // Enable timer compare interrupt:

   // Configure Timer 3 (16 bit)
   TCCR3A = 0;
   TCCR3B = (1 << CS31);

   timerTicks = 0;
   currentTimerTicks = 0;
 }

 uint32_t TimerTick_GetTicks(void)
 {
   return currentTimerTicks;
 }

 uint32_t TimerTick_GetMicroTicks(void)
 {
   return TCNT3 >> 1;
 }

 uint32_t TimerTick_MicroTickMaximum(void)
 {
   return UINT16_MAX >> 1;  
 }

 void TimerTick_Run(void)
 {
   const uint8_t ticks = timerTicks;

   if (ticks > 0)
   {
      timerTicks = 0;
      currentTimerTicks += ticks;
   }
 }

 /******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/

 ISR(TIMER1_COMPA_vect)
 {
   ++timerTicks;
 }
