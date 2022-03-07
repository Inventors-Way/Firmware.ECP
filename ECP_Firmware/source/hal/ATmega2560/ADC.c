#include <hal/ADC.h>
#include <avr/io.h>
#include "HalDefinitions.h"
#include "ADC_Internal.h"
#include <util/delay.h>

/******************************************************************************
 *                                                                            *
 *                       Private Function Declaration                         *
 *                                                                            *
 ******************************************************************************/

#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

uint16_t ADC_Sample(const uint8_t pin);

uint16_t channels[CHAN_MAX_CHANNELS];

inline void ADC_SetChannel(const uint8_t pin)
{
   ADMUX = (pin & 0x07) | ADC_VREF_TYPE;     //0x1f

   if (pin & 0x08)
   {
      ADCSRB |= (1<<MUX5);  //0x20
   }
   else
   {
      ADCSRB &= ~(1<<MUX5);
   }   
}

inline uint8_t ADC_GetPinNumber(const enum AnalogChannel channel)
{
   switch (channel)
   {
      case CHAN01: return 0;
      case CHAN02: return 1;
      case CHAN03: return 3;
      case CHAN04: return 4;
      default: return 0; break;
   }   
}

inline enum AnalogChannel ADC_GetNextChannel(enum AnalogChannel current)
{
   ++current;      
   return current == CHAN_MAX_CHANNELS ? CHAN01 : current;
}

inline uint16_t ADC_Sample(const uint8_t pin)
{
   // Start the AD conversion
   ADCSRA |= (1<<ADSC);
   // Wait for the AD conversion to complete
   while ((ADCSRA & (1<<ADIF))==0);
   ADCSRA|=(1<<ADIF);
   return ADC;
}

enum AnalogChannel activeChannel;
uint8_t activePin;

/******************************************************************************
 *                                                                            *
 *                       Public Function Implementation                       *
 *                                                                            *
 ******************************************************************************/

void ADC_Initialize(void)
{
   // ADC initialization
   // ADC Clock frequency: 1000,000 kHz
   // ADC Voltage Reference: AVCC pin
   // ADC Auto Trigger Source: ADC Stopped
   // Only the 8 most significant bits of
   // the AD conversion result are used
   // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
   // ADC4: On, ADC5: On, ADC6: On, ADC7: On
   DIDR0=(0<<ADC7D) | (0<<ADC6D) | (0<<ADC5D) | (0<<ADC4D) | (0<<ADC3D) | (0<<ADC2D) | (0<<ADC1D) | (0<<ADC0D);
   // Digital input buffers on ADC8: On, ADC9: On, ADC10: On, ADC11: On
   // ADC12: On, ADC13: On, ADC14: On, ADC15: On
   DIDR2=(0<<ADC15D) | (0<<ADC14D) | (0<<ADC13D) | (0<<ADC12D) | (0<<ADC11D) | (0<<ADC10D) | (0<<ADC9D) | (0<<ADC8D);
   ADMUX=ADC_VREF_TYPE;
   ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
   ADCSRB=(0<<MUX5) | (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

   activeChannel = CHAN01;
   activePin = ADC_GetPinNumber(activeChannel);
   ADC_SetChannel(activePin);
   
   for (uint8_t n = 0; n < CHAN_MAX_CHANNELS; ++n)
   {
      channels[n] = 0;
   }
}

uint16_t ADC_GetValue(const enum AnalogChannel channel)
{   
   return channels[channel];
}

void ADC_Run()
{
   channels[activeChannel] = ADC_Sample(activePin);
   activeChannel = ADC_GetNextChannel(activeChannel);
   activePin = ADC_GetPinNumber(activeChannel);
   ADC_SetChannel(activePin);
}

/******************************************************************************
 *                                                                            *
 *                       Private Function Implementation                      *
 *                                                                            *
 ******************************************************************************/


