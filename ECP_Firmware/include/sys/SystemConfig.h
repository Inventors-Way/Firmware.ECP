/*
 * SystemConfig.h
 *
 * Created: 14-04-2021 13:17:44
 *  Author: KristianHennings
 */ 


#ifndef SYSTEMCONFIG_H_
#define SYSTEMCONFIG_H_

/*****************************************************************************
 *                                                                           *
 *                         System Configuration                              *
 *                                                                           *
 *****************************************************************************/

#define MEMORY_POOL_SIZE      2048
#define TASK_TIMELIMIT       20000
#define PROFILER_PERIOD       1000

/*****************************************************************************
 *                                                                           *
 *                         Serial Port Configuration                         *
 *                                                                           *
 *****************************************************************************/

#define BAUDRATE                 38400
#define RX_BUFFER_SIZE           256

#define MAX_PACKET_SIZE          256

/*****************************************************************************
 *                                                                           *
 *                              ECP Specification                            *
 *                                                                           *
 *****************************************************************************/

// FUNCTIONS
#define DEVICE_IDENTIFICATION    0x01
#define PING                     0x02
#define GET_ENDIANNESS           0x03
#define SET_DEBUG_SIGNAL         0x04

// FUNCTIONS INTENDED TO DEMONSTRATE HOW TO USE ECP FUNCTIONS
#define SIMPLE_FUNCTION          0x10
#define DATA_FUNCTION            0x11

// FUNCTIONS INTEDED TO TEST THE HAL LAYER
#define SPI_CONFIGURE            0x20
#define SPI_TEST_FUNCTION        0x21

// MESSAGES
#define TIMING_MSG               0xFD
#define TIMING_VIOLATION_MSG     0xFE
#define PRINTF_MSG               0xFF

// ERROR CODES 
#define UNKNOWN_FUNCTION_ERR     0x01
#define INVALID_CONTENT_ERR      0x02

/*****************************************************************************
 *                                                                           *
 *                              Identification                               *
 *                                                                           *
 *****************************************************************************/
#define MANUFACTURER_ID                UINT32_MAX
#define DEVICE_TYPE                    1
#define MAJOR_REVISION                 1
#define MINOR_REVISION                 0
#define PATCH_REVISION                 0
#define ENGINEERING_REVISION           0
#define DEVICE_NAME                    "ECP Firmware"
#define MANUFACTORER_NAME              "Acme Coorporation"

#define NUMBER_OF_DEBUG_SIGNALS        2
#define MAX_STRING_LENGTH              127




#endif /* SYSTEMCONFIG_H_ */

