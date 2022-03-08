/*
 * DRV.c
 *
 * Created: 08/03/2022 15.28.41
 *  Author: KristianHennings
 */ 
#include <drv/DRV.h>
#include <drv/MCP48X2.h>

void DRV_Initialize(void)
{
   MCP48X2_Initialize();   
}