/*
 * HalDefinitions.h
 *
 * Created: 06/03/2022 18.04.17
 *  Author: KristianHennings
 */ 


#ifndef HALDEFINITIONS_H_
#define HALDEFINITIONS_H_

#ifdef F_CPU
#undef F_CPU
#endif

#define F_CPU 16000000UL ///< Clock frequency of the processor

#endif /* HALDEFINITIONS_H_ */