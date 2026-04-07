//************************** Thread_IPC ***************************************
// Copyright (c) 2026 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : ThreadHandler.h
// Summary  : Header file defining the thread callback functions.
// Note     : None
// Author   : Shani
// Date     : Mar 30, 2026
//
//*****************************************************************************

#ifndef INC_THREADHANDLER_H_
#define INC_THREADHANDLER_H_

//******************************* Include Files *******************************
#include "main.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Global Variables ******************************
typedef struct _DATA_MSG_
{
    uint32_t ulButtonId;
} DATA_MSG;

//**************************** Forward Declarations ***************************
void ThreadHandlerPoller(void* pArguments);
void ThreadHandlerTransport(void* pArguments);
void ThreadHandlerLogger(void* pArguments);

//*********************** Inline Method Implementations ***********************

#endif /* INC_THREADHANDLER_H_ */
// EOF
