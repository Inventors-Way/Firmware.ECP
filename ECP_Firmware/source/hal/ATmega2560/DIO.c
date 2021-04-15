/*
 * DIO.c
 *
 * Created: 14-04-2021 13:04:17
 *  Author: KristianHennings
 */ 
 #include <avr/io.h>
 #include <hal/DIO.h>
 
 /******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

 /** \addtogroup DIO
 *  @{
 */

 
uint8_t pin_states[PIN_EOL];

/**
* \brief [PRIVATE] Sample a pin
*
* \param pin the pin to sample
* \return the value read from the pin
*/
uint8_t DIO_SamplePin(const enum Pin pin);


/**
* \brief [PRIVATE] Set a pin active.
*
* \param pin the pin to set active.
*/
void DIO_SetPinActive(const enum Pin pin);


/**
* \brief [PRIVATE] Set a pin inactive.
*
* \param pin the pin to set inactive.
*/
void DIO_SetPinInActive(const enum Pin pin);

/** @}*/

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void DIO_Initialize(void)
{
   // Port A: Unused, all configured as inputs with pull-up enabled.
   // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
   DDRA  = (0<<DDA7)   | (0<<DDA6)   | (0<<DDA5)   | (0<<DDA4)   | (0<<DDA3)   | (0<<DDA2)   | (0<<DDA1)   | (0<<DDA0);
   PORTA = (1<<PORTA7) | (1<<PORTA6) | (1<<PORTA5) | (1<<PORTA4) | (1<<PORTA3) | (1<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

   // Port B: Used for Debug LED
   //
   //      Function                 Configuration
   // PB0-6: Unused                    Input, Pull-Up Enabled
   // PB7: Debug LED                 Output, Default Low
   DDRB =(1<<DDB7)   | (1<<DDB6)   | (0<<DDB5)   | (0<<DDB4)   | (0<<DDB3)   | (0<<DDB2)   | (0<<DDB1)   | (0<<DDB0);
   PORTB=(0<<PORTB7) | (0<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

   // Port C: Unused all configured as inputs with pull-up enabled
   DDRC =(0<<DDC7)   | (0<<DDC6)   | (0<<DDC5)   | (0<<DDC4)   | (0<<DDC3)   | (0<<DDC2)   | (0<<DDC1)   | (0<<DDC0);
   PORTC=(1<<PORTC7) | (1<<PORTC6) | (1<<PORTC5) | (1<<PORTC4) | (1<<PORTC3) | (1<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

   // Port D: Unused all configured as inputs with pull-up enabled
   DDRD =(0<<DDD7)   | (0<<DDD6)   | (0<<DDD5)   | (0<<DDD4)   | (0<<DDD3)   | (0<<DDD2)   | (0<<DDD1)   | (0<<DDD0);
   PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

   // Port E: Used for USART0
   //         Function         Configuration
   // PE2-7:  Unused           Input, Pull-Up Enabled
   // PE1:    TX0              Output, Default High
   // PE0:    RX0              Input, Pull-Up Enabled
   DDRE =(0<<DDE7)   | (0<<DDE6)   | (0<<DDE5)   | (0<<DDE4)   | (0<<DDE3)   | (0<<DDE2)   | (1<<DDE1)   | (0<<DDE0);
   PORTE=(1<<PORTE7) | (1<<PORTE6) | (0<<PORTE5) | (1<<PORTE4) | (1<<PORTE3) | (1<<PORTE2) | (1<<PORTE1) | (0<<PORTE0);

   // Port F: Unused all configured as inputs with pull-up enabled
   DDRF =(1<<DDF7)   | (1<<DDF6)   | (1<<DDF5)   | (1<<DDF4)   | (1<<DDF3)   | (1<<DDF2)   | (1<<DDF1)   | (1<<DDF0);
   PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

   // Port G: Unused all configured as inputs with pull-up enabled
   // PG5:   Front panel LED   Output, Default Low
   DDRG =(1<<DDG5)   | (0<<DDG4)   | (0<<DDG3)   | (0<<DDG2)   | (0<<DDG1)   | (0<<DDG0);
   PORTG=(0<<PORTG5) | (1<<PORTG4) | (1<<PORTG3) | (1<<PORTG2) | (1<<PORTG1) | (1<<PORTG0);

   // Port H: Unused all configured as inputs with pull-up enabled
   DDRH =(0<<DDH7)   | (0<<DDH6)   | (0<<DDH5)   | (0<<DDH4)   | (0<<DDH3)   | (0<<DDH2)   | (0<<DDH1)   | (0<<DDH0);
   PORTH=(1<<PORTH7) | (1<<PORTH6) | (1<<PORTH5) | (1<<PORTH4) | (1<<PORTH3) | (1<<PORTH2) | (1<<PORTH1) | (1<<PORTH0);

   // Port J: Unused all configured as inputs with pull-up enabled
   DDRJ =(0<<DDJ7)   | (0<<DDJ6)   | (0<<DDJ5)   | (0<<DDJ4)   | (0<<DDJ3)   | (0<<DDJ2)   | (0<<DDJ1)   | (0<<DDJ0);
   PORTJ=(1<<PORTJ7) | (1<<PORTJ6) | (1<<PORTJ5) | (1<<PORTJ4) | (1<<PORTJ3) | (1<<PORTJ2) | (1<<PORTJ1) | (1<<PORTJ0);

   // Port K: Unused all configured as inputs with pull-up enabled
   DDRK =(0<<DDK7)   | (0<<DDK6)   | (0<<DDK5)   | (0<<DDK4)   | (0<<DDK3)   | (0<<DDK2)   | (0<<DDK1)   | (0<<DDK0);
   PORTK=(1<<PORTK7) | (0<<PORTK6) | (0<<PORTK5) | (0<<PORTK4) | (1<<PORTK3) | (1<<PORTK2) | (1<<PORTK1) | (1<<PORTK0);

   // Port L: Unused all configured as inputs with pull-up enabled
   DDRL =(0<<DDL7)   | (0<<DDL6)   | (0<<DDL5)   | (0<<DDL4)   | (0<<DDL3)   | (0<<DDL2)   | (0<<DDL1)   | (0<<DDL0);
   PORTL=(1<<PORTL7) | (1<<PORTL6) | (1<<PORTL5) | (1<<PORTL4) | (1<<PORTL3) | (1<<PORTL2) | (1<<PORTL1) | (1<<PORTL0);   
}

void DIO_SetPin(const enum Pin pin, const uint8_t value)
{
   if (value)
   {
      DIO_SetPinActive(pin);
   }
   else
   {
      DIO_SetPinInActive(pin);
   }
}

uint8_t DIO_GetPin(const enum Pin pin)
{
   return pin_states[pin];
}

/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/


void DIO_SetPinActive(const enum Pin pin)
{
   switch (pin)
   {
      case PIN_DEBUG_OUT01:
         PORTB |= (1 << PB7);
         pin_states[pin] = 1;
         break;
      case PIN_DEBUG_OUT02:
         PORTB |= (1 << PB6);
         pin_states[pin] = 1;
         break;
      default:
         break;
   }
}

void DIO_SetPinInActive(const enum Pin pin)
{
   switch (pin)
   {
      case PIN_DEBUG_OUT01:
         PORTB &= ~(1 << PB7);
         pin_states[pin] = 0;
         break;
      case PIN_DEBUG_OUT02:
         PORTB &= ~(1 << PB6);
         pin_states[pin] = 0;
         break;
      default:
         break;
   }
}
