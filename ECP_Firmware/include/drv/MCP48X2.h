/*
 * MCP48X2.h
 *
 * Created: 08/03/2022 11.12.42
 *  Author: KristianHennings
 */ 
#ifndef MCP48X2_H_
#define MCP48X2_H_

#include <stdint.h>

void MCP48X2_Initialize(void);

void MCP48X2_Update(const uint16_t ch01, const uint16_t ch02);



#endif /* MCP48X2_H_ */