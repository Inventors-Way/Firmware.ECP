/*
 * HalInternal.h
 *
 * Created: 14-04-2021 13:43:19
 *  Author: KristianHennings
 */ 


#ifndef HALINTERNAL_H_
#define HALINTERNAL_H_

#ifdef F_CPU
#undef F_CPU
#endif

#define F_CPU          16000000UL ///< Clock frequency of the processor

#endif /* HALINTERNAL_H_ */