#ifndef ADC_INTERNAL_H_
#define ADC_INTERNAL_H_

/** \addtogroup ADC 
 *  @{
 */

#include <stdint.h>
#include <hal/ADC.h>

/**
 * \brief Initialize the ADC
 */
void ADC_Initialize(void);

void ADC_Run();

/** @}*/

#endif /* ADC_H_ */