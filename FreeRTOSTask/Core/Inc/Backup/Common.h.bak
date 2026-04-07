//************************** FreeRTOSTask  ***********************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : Common.h
// Summary  : Contains Centralized definitions, shared structures, and global
//            declarations
// Note     : None
// Author   : Shani
// Date     : Mar 31, 2026
//
//*****************************************************************************
#ifndef COMMON_H
#define COMMON_H

//******************************* Include Files *******************************
#include <pthread.h>
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************
typedef enum
{
    IPC_BINARY_SEMAPHORE,
    IPC_QUEUE,
} IPC_TYPE;

typedef enum
{
    IPC_POLLER_SEM =	   0,
    IPC_POLLER_DATA_QUE	    ,
	IPC_TRANSPORT_ACK_SEM   ,
	IPC_TRANSPORT_DATA_QUE  ,
	IPC_LOGGER_ACK_SEM      ,
    IPC_MAX
} IPC_INDEX;

typedef struct _THREAD_DEFINITION_
{
    osThreadId_t* 			pHandle;
    osThreadFunc_t      	pTaskFunc;
    const osThreadAttr_t* 	pstAttributes;
    void* 					pArgument;
} THREAD_DEFINITION;

typedef struct _IPC_DEFINITION_
{
    void** 		pIPCHandle;
    IPC_TYPE 	eIPCType;
    const char* pcIPCName;
} IPC_DEFINITION;


//**************************** Forward Declarations ***************************

//*********************** Inline Method Implementations ***********************

#endif  /*COMMON_H */

// EOF
