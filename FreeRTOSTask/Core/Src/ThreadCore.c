//**************************** FreeRTOSTask *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved
//*****************************************************************************
//
// File      : ThreadCore.c
// Summary   : A centralized utility file for wrapping standard pthread calls
// Note      : None
// Author    : Shani
// Date      : Mar 25, 2026
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "ThreadCore.h"
#include "ThreadService.h"
#include "main.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//****************************** Local Functions ******************************

//*************************** ThreadCoreCreateBinarySemaphore ****************
//Purpose   : Creates a binary semaphore .
//Inputs    : pstIPCConfig - pointer to the IPC definition structure.
//Outputs   : None
//Return    : true if semaphore creation succeeded false if failed to create
//			  binary semaphore.
//Notes     : None
//*****************************************************************************
bool ThreadCoreCreateBinarySemaphore(const IPC_DEFINITION* pstIPCConfig)
{
    bool blStatus = true;

    do
    {
        if (NULL == pstIPCConfig )
        {
            printf("ERROR: IPC creation failed - Null pointer configuration.\r\n");
            blStatus = false;
            break;
        }

        *(pstIPCConfig->pIPCHandle) = xSemaphoreCreateBinary();

        if (NULL == *(pstIPCConfig->pIPCHandle))
        {
            printf("ERROR: %s Allocation failed\r\n", pstIPCConfig->pcIPCName);
            blStatus = false;
        }

    } while (0);

    return blStatus;
}

//*************************** ThreadCoreCreateThread *************************
//Purpose   : Creates thread with specific attribute
//Inputs    : pstThreadConfig - pointer to the thread definition structure.
//Outputs   : None
//Return    : true if thread creation succeeded.
//Notes     : None
//*****************************************************************************
bool ThreadCoreCreateThread(const THREAD_DEFINITION* pstThreadConfig)
{
    bool blStatus = true;

    do
    {

        if (NULL == pstThreadConfig)
        {
            printf("ERROR: Thread creation failed - Null pointer configuration.\r\n");
            blStatus = false;
            break;
        }

        *(pstThreadConfig->pHandle) = osThreadNew(pstThreadConfig->pTaskFunc,
        					pstThreadConfig->pArgument,pstThreadConfig->pstAttributes);

        if (NULL == *(pstThreadConfig->pHandle))
        {
            printf("ERROR: %s Creation failed\r\n", pstThreadConfig->pstAttributes->name);
            blStatus = false;
            break;
        }
        else
        {
            printf("%s Created Successfully\r\n", pstThreadConfig->pstAttributes->name);
        }

    } while (0);

    return blStatus;
}

//*************************** ThreadCoreCreateQueue **************************
//Purpose   : Creates Queue.
//Inputs    : pstIPCConfig  - Pointer to the IPC definition structure.
//            ulQueueLength - The maximum number of items the queue can hold.
//            ulItemSize    - The size of each item in the queue.
//Outputs   : None
//Return    : true if the queue was successfully created, false if queue
//            creation failed .
//Notes     : None
//*****************************************************************************
bool ThreadCoreCreateQueue(const IPC_DEFINITION* pstIPCConfig, uint32_t ulQueueLength,
																	uint32_t ulItemSize)
{
    bool blStatus = true;

    do
    {
        /* 1. Safety check for the configuration and handle destination */
        if (NULL == pstIPCConfig)
        {
            printf("ERROR: Queue creation failed - Null configuration.\r\n");
            blStatus = false;
            break;
        }

        *(pstIPCConfig->pIPCHandle) = xQueueCreate(ulQueueLength, ulItemSize);

        if (NULL == *(pstIPCConfig->pIPCHandle))
        {
            printf("ERROR: %s Allocation failed \r\n", pstIPCConfig->pcIPCName);
            blStatus = false;
            break;
        }

    } while (0);

    return blStatus;
}

//*************************** ThreadCoreWaitSemaphore ************************
//Purpose   : Blocks the calling thread until the specified semaphore is signaled.
//Inputs    : pstIPCConfig - pointer to the IPC definition structure.
//            ulWaitMs     - Time to wait in milliseconds.
//Outputs   : None
//Return    : true if the semaphore was successfully taken, false if it timed out.
//Notes     : None
//*****************************************************************************
bool ThreadCoreWaitSemaphore(const IPC_DEFINITION* pstIPCConfig, uint32_t ulWaitMs)
{
    bool blStatus = true;

    do
    {
        if (NULL == pstIPCConfig)
        {
            printf("ERROR: Semaphore wait failed - NULL Pointer\r\n");
            blStatus = false;
            break;
        }

        if (pdPASS != xSemaphoreTake(*(pstIPCConfig->pIPCHandle), ulWaitMs))
        {
            printf("ERROR: Semaphore wait failed or Timed out\r\n");
            blStatus = false;
        }

    } while (0);

    return blStatus;
}

//*************************** ThreadCoreSignalSemaphore **********************
//Purpose   : Signals a semaphore to unblock a waiting thread.
//Inputs    : pstIPCConfig - Pointer to the IPC definition structure.
//Outputs   : None
//Return    : true if the semaphore was successfully given. False if semaphore
//			  giving failed
//Notes     : None.
//*****************************************************************************
bool ThreadCoreSignalSemaphore(const IPC_DEFINITION* pstIPCConfig)
{
    bool blStatus = true;

    do
    {
        if (NULL == pstIPCConfig )
        {
            printf("ERROR: Semaphore signal failed - Null pointer\r\n");
            blStatus = false;
            break;
        }

        /* Signal the semaphore */
        if (pdPASS != xSemaphoreGive(*(pstIPCConfig->pIPCHandle)))
        {
            printf("WARNING: %s already signaled\r\n", pstIPCConfig->pcIPCName);
            blStatus = false;
        }

    } while (0);

    return blStatus;
}

//*************************** ThreadCoreQueueSend ****************************
//Purpose   : Sends a data structure to a FreeRTOS Queue.
//Inputs    : pstIPCConfig - Pointer to the IPC definition .
//            pItemToQueue - Pointer to the data structure.
//            ulWaitMs      - Max time to wait (in ms) if the queue is full.
//Outputs   : None
//Return    : true if the item was successfully send to the queue. False if data
//			  send failed.
//Notes     : None
//*****************************************************************************
bool ThreadCoreQueueSend(const IPC_DEFINITION* pstIPCConfig, const void* pItemToQueue,
																uint32_t ulWaitMs)
{
    bool blStatus = true;
    TickType_t xTicksToWait = pdMS_TO_TICKS(ulWaitMs);

    do
    {
        if (NULL == pstIPCConfig || NULL == pItemToQueue)
        {
            printf("ERROR: Queue Send failed - Invalid Parameters or Handle\r\n");
            blStatus = false;
            break;
        }

        if (pdPASS != xQueueSend(*(pstIPCConfig->pIPCHandle), pItemToQueue, xTicksToWait))
        {
            printf("ERROR: Queue %s is full or Timeout reached\r\n", pstIPCConfig->pcIPCName);
            blStatus = false;
        }

    } while (0);

    return blStatus;
}

//*************************** ThreadCoreQueueReceive *************************
//Purpose   : Receives a data structure from a FreeRTOS Queue.
//Inputs    : pstIPCConfig - Pointer to the Queue definition.
//            pDataBuffer   - Address where the received data should be stored.
//            ulWaitMs      - Data wait time.
//Outputs   : None
//Return    : true if an data received successfully, false if reception failed.
//Notes     : None
//*****************************************************************************
bool ThreadCoreQueueReceive(const IPC_DEFINITION* pstIPCConfig, void* pDataBuffer,
															uint32_t ulWaitMs)
{
    bool blStatus = true;
    TickType_t xTicksToWait = (ulWaitMs == portMAX_DELAY) ?
    							portMAX_DELAY : pdMS_TO_TICKS(ulWaitMs);

    do
    {
		if (NULL == pstIPCConfig || NULL == pDataBuffer )
		{
			blStatus = false;
			break;
		}

		if (pdPASS != xQueueReceive(*(pstIPCConfig->pIPCHandle), pDataBuffer, xTicksToWait))
		{
			blStatus = false;
		}

    } while (0);

    return blStatus;
}
