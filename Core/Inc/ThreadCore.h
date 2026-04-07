//************************** FreeRTOSTask ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : ThreadCore.h
// Summary  : Function declarations of wrapper functions in ThreadCore.c
// Note     : None
// Author   : Shani
// Date     : Mar 30, 2026
//
//*****************************************************************************
#ifndef INC_THREADCORE_H_
#define INC_THREADCORE_H_

//******************************* Include Files *******************************
#include "main.h"
#include "Common.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************

//**************************** Forward Declarations ***************************
bool ThreadCoreCreateBinarySemaphore(const IPC_DEFINITION* pstIPCConfig);
bool ThreadCoreCreateThread(const THREAD_DEFINITION* pstThreadConfig);
bool ThreadCoreWaitSemaphore(const IPC_DEFINITION* pstIPCConfig, uint32_t ulWaitMs);
bool ThreadCoreSignalSemaphore(const IPC_DEFINITION* pstIPCConfig);
bool ThreadCoreCreateQueue(const IPC_DEFINITION* pstIPCConfig, uint32_t ulQueueLength,
																	uint32_t ulItemSize);
bool ThreadCoreQueueSend(const IPC_DEFINITION* pstIPCConfig, const void* pItemToQueue,
																uint32_t ulWaitMs);
bool ThreadCoreQueueReceive(const IPC_DEFINITION* pstIPCConfig, void* pDataBuffer,
															uint32_t ulWaitMs);

#endif /* INC_THREADCORE_H_ */
// EOF
