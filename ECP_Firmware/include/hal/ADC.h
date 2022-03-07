#ifndef ADC_H_
#define ADC_H_

/** \addtogroup ADC 
 *  @{
 */

#include <stdint.h>

enum AnalogChannel
{
	CHAN01 = 0,
	CHAN02,
	CHAN03,
	CHAN04,
    CHAN_MAX_CHANNELS
};

/**
 * \brief Sample an ADC channel
 * 
 * \param channel the channel to sample
 * \return uint16_t the value sampled from the channel
 */
uint16_t ADC_GetValue(const enum AnalogChannel channel);

/** @}*/

#endif /* ADC_H_ */