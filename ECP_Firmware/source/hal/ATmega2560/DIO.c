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

/** @}*/

/******************************************************************************
*                                                                            *
*                       Public Function Implementation                       *
*                                                                            *
******************************************************************************/

void DIO_Initialize(void)
{
   // Port A: Unused
   //
   //      Name           Configuration               Arduino Pin
   // PA0: Unused         Input (Pull-Up Enabled)
   // PA1: Unused         Input (Pull-Up Enabled)
   // PA2: Unused         Input (Pull-Up Enabled)
   // PA3: Unused         Input (Pull-Up Enabled)
   // PA4: Unused         Input (Pull-Up Enabled)
   // PA5: Unused         Input (Pull-Up Enabled)
   // PA6: Unused         Input (Pull-Up Enabled)
   // PA7: Unused         Input (Pull-Up Enabled)
   DDRA  = (0<<DDA7)   | (0<<DDA6)   | (0<<DDA5)   | (0<<DDA4)   | (0<<DDA3)   | (0<<DDA2)   | (0<<DDA1)   | (0<<DDA0);
   PORTA = (1<<PORTA7) | (1<<PORTA6) | (1<<PORTA5) | (1<<PORTA4) | (1<<PORTA3) | (1<<PORTA2) | (1<<PORTA1) | (1<<PORTA0);

   // Port B: Used for Debug LED and SPI communication
   //
   //      Name           Configuration               Arduino Pin
   // PB0: Unused         Input  (Pull-Up Enabled)    D53
   // PB1: SCK            Output (LOW)                D52
   // PB2: MOSI           Output (LOW)                D51
   // PB3: MISO           Input  (Pull-Up Enabled)    D50
   // PB4: Unused         Input  (Pull-Up Enabled)    D10
   // PB5: Unused         Input  (Pull-Up Enabled)    D11
   // PB6: DEBUG_OUT_02   Output (LOW)                D12
   // PB7: DEBUG_OUT_01   Output (LOW)                D13
   DDRB =(1<<DDB7)   | (1<<DDB6)   | (0<<DDB5)   | (0<<DDB4)   | (0<<DDB3)   | (1<<DDB2)   | (1<<DDB1)   | (0<<DDB0);
   PORTB=(0<<PORTB7) | (0<<PORTB6) | (1<<PORTB5) | (1<<PORTB4) | (1<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (1<<PORTB0);

   // Port C: Unused all configured as inputs with pull-up enabled
   DDRC =(0<<DDC7)   | (0<<DDC6)   | (0<<DDC5)   | (0<<DDC4)   | (0<<DDC3)   | (0<<DDC2)   | (0<<DDC1)   | (0<<DDC0);
   PORTC=(1<<PORTC7) | (1<<PORTC6) | (1<<PORTC5) | (1<<PORTC4) | (1<<PORTC3) | (1<<PORTC2) | (1<<PORTC1) | (1<<PORTC0);

   // Port D: Used for DIO
   //
   //      Name           Configuration               Arduino Pin
   // PD0: PIN_D21        Input (Pull-Up Enabled)    D21
   // PD1: PIN_D20        Input (Pull-Up Enabled)    D20
   // PD2: PIN_D19        Input (Pull-Up Enabled)    D19
   // PD3: PIN_D18        Input (Pull-Up Enabled)    D18
   // PD4: Unused         Input (Pull-Up Enabled)
   // PD5: Unused         Input (Pull-Up Enabled)
   // PD6: Unused         Input (Pull-Up Enabled)
   // PD7: Unused         Input (Pull-Up Enabled)
   DDRD =(0<<DDD7)   | (0<<DDD6)   | (0<<DDD5)   | (0<<DDD4)   | (0<<DDD3)   | (0<<DDD2)   | (0<<DDD1)   | (0<<DDD0);
   PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

   // Port E: Used for USART0
   //
   //      Name           Configuration               Arduino Pin
   // PE0: RX0            Input (Pull-Up Enabled)     D0
   // PE1: TX0            Output (HIGH)               D1
   // PE2: Unused         Input (Pull-Up Enabled)     
   // PE3: Unused         Input (Pull-Up Enabled)     D5
   // PE4: Unused         Input (Pull-Up Enabled)     D2
   // PE5: Unused         Input (Pull-Up Enabled)     D3
   // PE6: Unused         Input (Pull-Up Enabled)    
   // PE7: Unused         Input (Pull-Up Enabled)
   DDRE =(0<<DDE7)   | (0<<DDE6)   | (0<<DDE5)   | (0<<DDE4)   | (0<<DDE3)   | (0<<DDE2)   | (1<<DDE1)   | (0<<DDE0);
   PORTE=(1<<PORTE7) | (1<<PORTE6) | (0<<PORTE5) | (1<<PORTE4) | (1<<PORTE3) | (1<<PORTE2) | (1<<PORTE1) | (0<<PORTE0);

   // Port F: Unused
   //
   //      Name           Configuration               Arduino Pin
   // PF0: Unused         Input (Pull-Up Enabled)
   // PF1: Unused         Input (Pull-Up Enabled)
   // PF2: Unused         Input (Pull-Up Enabled)
   // PF3: Unused         Input (Pull-Up Enabled)
   // PF4: Unused         Input (Pull-Up Enabled)
   // PF5: Unused         Input (Pull-Up Enabled)
   // PF6: Unused         Input (Pull-Up Enabled)
   // PF7: Unused         Input (Pull-Up Enabled)   
   DDRF =(0<<DDF7)   | (0<<DDF6)   | (0<<DDF5)   | (0<<DDF4)   | (0<<DDF3)   | (0<<DDF2)   | (0<<DDF1)   | (0<<DDF0);
   PORTF=(1<<PORTF7) | (1<<PORTF6) | (1<<PORTF5) | (1<<PORTF4) | (1<<PORTF3) | (1<<PORTF2) | (1<<PORTF1) | (1<<PORTF0);

   // Port G: Unused
   //
   //      Name           Configuration               Arduino Pin
   // PG0: Unused         Input (Pull-Up Enabled)
   // PG1: Unused         Input (Pull-Up Enabled)
   // PG2: Unused         Input (Pull-Up Enabled)
   // PG3: Unused         Input (Pull-Up Enabled)
   // PG4: Unused         Input (Pull-Up Enabled)
   // PG5: Unused         Input (Pull-Up Enabled)
   // PG6: Unused         Input (Pull-Up Enabled)
   // PG7: Unused         Input (Pull-Up Enabled)
   DDRG =(0<<DDG5)   | (0<<DDG4)   | (0<<DDG3)   | (0<<DDG2)   | (0<<DDG1)   | (0<<DDG0);
   PORTG=(1<<PORTG5) | (1<<PORTG4) | (1<<PORTG3) | (1<<PORTG2) | (1<<PORTG1) | (1<<PORTG0);

   // Port H: Used for DIO
   //
   //      Name           Configuration               Arduino Pin
   // PH0: PIN_D14        Output(LOW)                 D16
   // PH1: PIN_D15        Output (LOW)                D17
   // PH2: Unused         Input (Pull-Up Enabled)
   // PH3: Unused         Input (Pull-Up Enabled)
   // PH4: Unused         Input (Pull-Up Enabled)
   // PH5: Unused         Input (Pull-Up Enabled)
   // PH6: Unused         Input (Pull-Up Enabled)
   // PH7: Unused         Input (Pull-Up Enabled)
   DDRH =(0<<DDH7)   | (0<<DDH6)   | (0<<DDH5)   | (0<<DDH4)   | (0<<DDH3)   | (0<<DDH2)   | (1<<DDH1)   | (1<<DDH0);
   PORTH=(1<<PORTH7) | (1<<PORTH6) | (1<<PORTH5) | (1<<PORTH4) | (1<<PORTH3) | (1<<PORTH2) | (0<<PORTH1) | (0<<PORTH0);

   // Port J: Used for DIO
   //
   //      Name           Configuration               Arduino Pin
   // PJ0: PIN_D14        Output(LOW)                 D14
   // PJ1: PIN_D15        Output (LOW)                D15
   // PJ2: Unused         Input (Pull-Up Enabled)
   // PJ3: Unused         Input (Pull-Up Enabled)     
   // PJ4: Unused         Input (Pull-Up Enabled)     
   // PJ5: Unused         Input (Pull-Up Enabled)     
   // PJ6: Unused         Input (Pull-Up Enabled)
   // PJ7: Unused         Input (Pull-Up Enabled)
   DDRJ =(0<<DDJ7)   | (0<DDJ6)    | (0<<DDJ5)   | (0<<DDJ4)   | (0<<DDJ3)   | (0<<DDJ2)   | (1<<DDJ1)   | (1<<DDJ0);
   PORTJ=(1<<PORTJ7) | (1<<PORTJ6) | (1<<PORTJ5) | (1<<PORTJ4) | (1<<PORTJ3) | (1<<PORTJ2) | (0<<PORTJ1) | (0<<PORTJ0);

   // Port K: Unused
   //
   //      Name           Configuration               Arduino Pin
   // PK0: Unused         Input (Pull-Up Enabled)
   // PK1: Unused         Input (Pull-Up Enabled)
   // PK2: Unused         Input (Pull-Up Enabled)
   // PK3: Unused         Input (Pull-Up Enabled)
   // PK4: Unused         Input (Pull-Up Enabled)
   // PK5: Unused         Input (Pull-Up Enabled)
   // PK6: Unused         Input (Pull-Up Enabled)
   // PK7: Unused         Input (Pull-Up Enabled)
   DDRK =(0<<DDK7)   | (0<<DDK6)   | (0<<DDK5)   | (0<<DDK4)   | (0<<DDK3)   | (0<<DDK2)   | (0<<DDK1)   | (0<<DDK0);
   PORTK=(1<<PORTK7) | (0<<PORTK6) | (0<<PORTK5) | (0<<PORTK4) | (1<<PORTK3) | (1<<PORTK2) | (1<<PORTK1) | (1<<PORTK0);

   // Port L: Unused
   //
   //      Name           Configuration               Arduino Pin
   // PL0: Unused         Input (Pull-Up Enabled)
   // PL1: Unused         Input (Pull-Up Enabled)
   // PL2: Unused         Input (Pull-Up Enabled)
   // PL3: Unused         Input (Pull-Up Enabled)
   // PL4: Unused         Input (Pull-Up Enabled)
   // PL5: Unused         Input (Pull-Up Enabled)
   // PL6: Unused         Input (Pull-Up Enabled)
   // PL7: Unused         Input (Pull-Up Enabled)
   DDRL =(0<<DDL7)   | (0<<DDL6)   | (0<<DDL5)   | (0<<DDL4)   | (0<<DDL3)   | (0<<DDL2)   | (0<<DDL1)   | (0<<DDL0);
   PORTL=(1<<PORTL7) | (1<<PORTL6) | (1<<PORTL5) | (1<<PORTL4) | (1<<PORTL3) | (1<<PORTL2) | (1<<PORTL1) | (1<<PORTL0);   
}

void DIO_SetPin(const enum Pin pin, const uint8_t value)
{
   if (pin < PIN_EOL)
   {
      pin_states[pin] = value;
   }
	
   if (value)
   {
      switch (pin)
      {      
	      case PIN_D14: D14_HIGH(); break;
	      case PIN_D15: D15_HIGH(); break;
	      case PIN_D16: D16_HIGH(); break;
	      case PIN_D17: D17_HIGH(); break;

         case PIN_DEBUG_OUT01: PORTB |= (1 << PB7); break;
         case PIN_DEBUG_OUT02: PORTB |= (1 << PB6); break;
         default: break;
      }
   }
   else
   {
      switch (pin)
      {
	      case PIN_D14: D14_LOW(); break;
	      case PIN_D15: D15_LOW(); break;
	      case PIN_D16: D16_LOW(); break;
	      case PIN_D17: D17_LOW(); break;
         case PIN_DEBUG_OUT01: PORTB &= ~(1 << PB7); break;
         case PIN_DEBUG_OUT02: PORTB &= ~(1 << PB6); break;
         default: break;
      }
   }
}

uint8_t DIO_GetPin(const enum Pin pin)
{
	switch (pin)
	{
	   case PIN_D14: return pin_states[pin];
	   case PIN_D15: return pin_states[pin];
	   case PIN_D16: return pin_states[pin];
	   case PIN_D17: return pin_states[pin];
	   case PIN_D18: return D18_READ();
	   case PIN_D19: return D19_READ();
	   case PIN_D20: return D20_READ();
	   case PIN_D21: return D21_READ();
	   case PIN_DEBUG_OUT01: return pin_states[pin];
	   case PIN_DEBUG_OUT02: return pin_states[pin];
      default:
         return 0;
	}
}

enum Pin DIO_GetDebugPin(const uint8_t number)
{
   return PIN_DEBUG_OUT01 + number;
}


/******************************************************************************
*                                                                            *
*                       Private Function Implementation                      *
*                                                                            *
******************************************************************************/
