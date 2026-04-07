//************************** FreeRTOSTask ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : ThreadService.h
// Summary  : Header file defining the thread service functions.
// Note     : None
// Author   : Shani
// Date     : Mar 25, 2026
//
//*****************************************************************************
#ifndef INC_THREADSERVICE_H_
#define INC_THREADSERVICE_H_

//******************************* Include Files *******************************
#include "main.h"
#include "Common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************
#define POLLER_THREAD       	"Poller_Thread"
#define TRANSPORT_THREAD    	"Transport_Thread"
#define LOGGER_THREAD       	"Logger_Thread"
#define STACK_SIZE_POLLER       (1 * 1024)
#define STACK_SIZE_TRANSPORT    (1 * 1024)
#define STACK_SIZE_LOGGER       (1 * 1024)
#define POLLER_SEMAPHORE 		"Poller HW Semaphore"
#define POLLER_DATA_QUEUE 		"Poller Data Queue"
#define TRANSPORT_ACK_SEM       "Transport ACK Semaphore"
#define TRANSPORT_DATA_QUEUE 	"Transport Data Queue"
#define LOGGER_ACK_SEM			"Logger ACK Semaphore"

//***************************** Global Variables ******************************
extern osThreadId_t gPollerThreadId ;
extern SemaphoreHandle_t gPollerSemaphore;				//todo
extern QueueHandle_t gstTPollerDataQueue;
extern SemaphoreHandle_t gTransportAckSem;
extern  QueueHandle_t gstTransportDataQueue;
extern const IPC_DEFINITION stIPCConfigTable[];

//**************************** Forward Declarations ***************************
bool ThreadServiceRun(void);
bool ThreadServiceSetupIPC(void);
bool ThreadServiceCreateThreads (void);
bool ThreadServiceCreatePollerQueue(const IPC_DEFINITION* pstDataQueue);

//*********************** Inline Method Implementations ***********************

#endif /* INC_THREADSERVICE_H_ */

// EOF
