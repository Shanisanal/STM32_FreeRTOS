//**************************** FreeRTOSTask *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved
//*****************************************************************************
//
// File      : ThreadService.c
// Summary   : Function that connects thread handlers to core functions.
// Note      : None
// Author    : Shani
// Date      : Mar 30, 2026
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "main.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************
#define TOTAL_THREADS           (sizeof(sstThreadConfigTable) / \
                                sizeof(sstThreadConfigTable[0]))
#define TOTAL_IPC_OBJECTS		(sizeof(stIPCConfigTable) / \
                                sizeof(stIPCConfigTable[0]))
#define		QUEUE_LENGTH		5

//***************************** Local Variables *******************************
osThreadId_t gPollerThreadId      = 0;
const osThreadAttr_t stPollerAttr =
{
  .name 	  = POLLER_THREAD,
  .priority   = osPriorityAboveNormal,
  .stack_size = STACK_SIZE_POLLER
};

osThreadId_t gTrasnsportThreadId  = 0;
const osThreadAttr_t stTrasnsportAttr =
{
  .name 	  = TRANSPORT_THREAD,
  .priority   = osPriorityNormal,
  .stack_size = STACK_SIZE_TRANSPORT
};

osThreadId_t gLoggerThreadId  = 0;
const osThreadAttr_t stLoggerAttr =
{
  .name 	  = LOGGER_THREAD,
  .priority   = osPriorityNormal,
  .stack_size = STACK_SIZE_LOGGER
};

SemaphoreHandle_t 	gPollerSemaphore   	   = NULL;
QueueHandle_t 		gstTPollerDataQueue    = NULL;
SemaphoreHandle_t 	gTransportAckSem   	   = NULL;
QueueHandle_t 		gstTransportDataQueue  = NULL;
SemaphoreHandle_t 	gstLoggerAckSem    	   = NULL;

//****************************** Local Functions ******************************
/* Function table for creating the Thread*/
static const THREAD_DEFINITION sstThreadConfigTable[] =
{
	{ &gPollerThreadId,    ThreadHandlerPoller,    &stPollerAttr,    NULL },
	{ &gTrasnsportThreadId,ThreadHandlerTransport, &stTrasnsportAttr,NULL },
	{ &gLoggerThreadId,	   ThreadHandlerLogger,    &stLoggerAttr,    NULL },
};

/* Function table for creating the IPC*/
const IPC_DEFINITION stIPCConfigTable[] =
{
    { (void**)&gPollerSemaphore, 	IPC_BINARY_SEMAPHORE, POLLER_SEMAPHORE     },
	{ (void**)&gstTPollerDataQueue, IPC_QUEUE,            POLLER_DATA_QUEUE    },
	{ (void**)&gTransportAckSem,    IPC_BINARY_SEMAPHORE, TRANSPORT_ACK_SEM    },
    { (void**)&gstTransportDataQueue, IPC_QUEUE,          TRANSPORT_DATA_QUEUE },
    { (void**)&gstLoggerAckSem,      IPC_BINARY_SEMAPHORE,LOGGER_ACK_SEM       }
};

//***************************** ThreadServiceRun ******************************
//Purpose   : Initializes and starts the system threads
//Inputs    : None
//Outputs   : None
//Return    : true if the thread system started successfully, false if any
//		      thread fails.
//Notes     : None.
//******************************************************************************
bool ThreadServiceRun(void)
{
    bool blStatus = true;

    if(true == ThreadServiceSetupIPC())
    {
        if(false == ThreadServiceCreateThreads())
        {
            printf("ERROR: Failed to create system threads.\r\n");
            blStatus = false;
        }

    }
    else
    {
        printf("ERROR: Failed to create IPC.\r\n");
        blStatus = false;
    }

    return blStatus;
}

//******************************* ThreadServiceSetupIPC ************************
//Purpose   : Initialize all IPC objects .
//Inputs    : None
//Outputs   : None
//Return    : true if IPC objects are created successfully, false if IPC object
//			  creation failed.
//Notes     : None.
//******************************************************************************
bool ThreadServiceSetupIPC(void)
{
    bool blStatus = true;

    for (uint8_t ucIndex = 0; ucIndex < TOTAL_IPC_OBJECTS; ucIndex++)
    {
        const IPC_DEFINITION* pstIPCConfig = &stIPCConfigTable[ucIndex];

        switch (pstIPCConfig->eIPCType)
        {
            case IPC_BINARY_SEMAPHORE:
            {
            	if (false == ThreadCoreCreateBinarySemaphore(pstIPCConfig))
				{
					blStatus = false;
				}
                break;

            }
            case IPC_QUEUE:
            {
            	continue;
            }

            default:
            {
                printf("ERROR: Unknown IPC Type for %s\r\n", pstIPCConfig->pcIPCName);
                blStatus = false;
                break;
            }

        }

        if (NULL == *(pstIPCConfig->pIPCHandle))
        {
            printf("ERROR: Failed to create %s\r\n", pstIPCConfig->pcIPCName);
            blStatus = false;
            break;
        }

    }

    return blStatus;
}

//******************************* ThreadServiceCreateThreads *******************
//Purpose   : Create all system threads with the specified attributes
//Inputs    : None
//Outputs   : None
//Return    : true if all threads were successfully created, false if any thread
//            creation failed.
//Notes     : None
//******************************************************************************
bool ThreadServiceCreateThreads (void)
{
	bool blStatus = true;

	for(uint8_t ucIndex = 0; ucIndex < TOTAL_THREADS; ucIndex++)
	{
		if (false == ThreadCoreCreateThread(&sstThreadConfigTable[ucIndex]))
		{
			blStatus = false;
	        printf("ERROR: Failed to create %s\r\n",
	        				sstThreadConfigTable[ucIndex].pstAttributes->name);
			break;
		}
	}

	return blStatus;
}

//*************************** ThreadServiceCreatePollerQueue *****************
//Purpose   : Create the Poller Data Queue.
//Inputs    : pstDataQueue - Pointer to the IPC definition for the queue.
//Outputs   : None
//Return    : true if queue creation succeeded, false if queue creation failed.
//Notes     : None
//*****************************************************************************
bool ThreadServiceCreatePollerQueue(const IPC_DEFINITION* pstDataQueue)
{
    bool blStatus = true;

    if(NULL == pstDataQueue)
    {
        printf("ERROR: Data Queue creation failed - Null Pointer\r\n");
        blStatus = false;
    }

    const uint32_t ulQueueLength = QUEUE_LENGTH;
    const uint32_t ulSize    	 = sizeof(DATA_MSG);

    if (false == ThreadCoreCreateQueue(pstDataQueue, ulQueueLength, ulSize))
    {
        printf("ERROR: %s creation failed\r\n",pstDataQueue->pcIPCName);
        blStatus = false;
    }

    return blStatus;
}
