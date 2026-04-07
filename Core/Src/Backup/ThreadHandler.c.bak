//**************************** FreeRTOSTask *************************************
//  Copyright (c) 2026 Trenser Technology Solutions
//  All Rights Reserved
//*****************************************************************************
//
// File      : ThreadHandler.c
// Summary   : Implementation of the primary thread routines .
// Note      : None
// Author    : Shani
// Date      : Mar 30, 2026
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "ThreadHandler.h"

//******************************* Local Types *********************************

//***************************** Local Constants *******************************
#define		MSG_ID					50
#define     QUEUE_TIMEOUT			10
#define     TRANSPORT_ACK_TIMEOUT	500
#define     LOGGER_ACK_TIMEOUT		500

//***************************** Local Variables *******************************

//****************************** Local Functions ******************************

//******************************* ThreadHandlerPoller **************************
//Purpose   : High-priority task that waits for a User Button interrupt.
//            Processes the hardware trigger and prepares data for the system.
//Inputs    : pArguments - Pointer to task arguments .
//Outputs   : None
//Return    : None
//Notes     : None
//******************************************************************************
void ThreadHandlerPoller(void* pArguments)
{
	const IPC_DEFINITION* pstPollerSem = &stIPCConfigTable[IPC_POLLER_SEM];
	const IPC_DEFINITION* pstPollerDataQueue = &stIPCConfigTable[IPC_POLLER_DATA_QUE];
	const IPC_DEFINITION* pstAckToPollerSem = &stIPCConfigTable[IPC_TRANSPORT_ACK_SEM];
	DATA_MSG stButtonMsg = {0};

	if(false == ThreadServiceCreatePollerQueue(pstPollerDataQueue))
	{
		  printf("ERROR: %s failed to create Data Queue\r\n",POLLER_THREAD);
	}

	for(;;)
	{
		if (true == ThreadCoreWaitSemaphore(pstPollerSem, portMAX_DELAY))
		{
			printf("----------------------------------------\r\n");
			printf("%s: Button Signal Received!\r\n",POLLER_THREAD);
			stButtonMsg.ulButtonId = MSG_ID;

			if(true == ThreadCoreQueueSend(pstPollerDataQueue, &stButtonMsg, QUEUE_TIMEOUT))
			{
				if (false == ThreadCoreWaitSemaphore(pstAckToPollerSem,
															TRANSPORT_ACK_TIMEOUT))
				{
					printf("ERROR: %s ACK from %s Timeout!\r\n", POLLER_THREAD,
															TRANSPORT_THREAD);
				}
			}
			else
			{
				printf("ERROR: %s Send Failed! \r\n",POLLER_DATA_QUEUE);
			}

		}
		else
		{
			printf("ERROR: %s failed to wait on semaphore.\r\n",POLLER_THREAD);
			osDelay(1000);
		}

	}
}

//******************************* ThreadHandlerTransport ***********************
//Purpose   : Middleman task that receives data from Poller, acknowledges it,
//            and forwards the data to the Logger task turning ON LED.
//Inputs    : pArguments - Generic pointer to thread configuration .
//Outputs   : None
//Return    : None
//Notes     : None
//******************************************************************************
void ThreadHandlerTransport(void* pArguments)
{
	const IPC_DEFINITION* pstFromPollerQue = &stIPCConfigTable[IPC_POLLER_DATA_QUE];
	const IPC_DEFINITION* pstAckToPollerSem  = &stIPCConfigTable[IPC_TRANSPORT_ACK_SEM];
	const IPC_DEFINITION* pstTransportDataQueue = &stIPCConfigTable[IPC_TRANSPORT_DATA_QUE];
	const IPC_DEFINITION* pstFromLoggerAckSem = &stIPCConfigTable[IPC_LOGGER_ACK_SEM];

	DATA_MSG stReceivedMsg = {0};

	if(false == ThreadServiceCreatePollerQueue(pstTransportDataQueue))
	{
		  printf("ERROR: %s failed to create Data Queue\r\n",TRANSPORT_THREAD);
	}

	for(;;)
	{
		if (true == ThreadCoreQueueReceive(pstFromPollerQue, &stReceivedMsg, portMAX_DELAY))
		{
			printf("%s: Received Button ID %lu from Poller\r\n",TRANSPORT_THREAD,
																stReceivedMsg.ulButtonId);
			if (true == ThreadCoreSignalSemaphore(pstAckToPollerSem))
			{
				if (true == ThreadCoreQueueSend(pstTransportDataQueue, &stReceivedMsg, QUEUE_TIMEOUT))
				{
					if (false == ThreadCoreWaitSemaphore(pstFromLoggerAckSem, LOGGER_ACK_TIMEOUT))
					{
						printf("ERROR: %s - Logger ACK Timeout!\r\n", TRANSPORT_THREAD);
					}
				}
				else
				{
					printf("ERROR: %s failed to forward to %s\r\n", TRANSPORT_THREAD,LOGGER_THREAD);
				}
			}
			else
			{
				printf("%s: Handshake ACK sent failed.\r\n",TRANSPORT_THREAD);
			}

		}

	}
}

//******************************* ThreadHandlerLogger **************************
//Purpose   : Receives button event data from the Transport thread acknowledges it
//			  and performs LED operations.
//Inputs    : pArguments - Generic pointer to thread configuration .
//Outputs   : None
//Return    : None
//Notes     : None
//******************************************************************************
void ThreadHandlerLogger(void* pArguments)
{
	const IPC_DEFINITION* pstFromTransportQue = &stIPCConfigTable[IPC_TRANSPORT_DATA_QUE];
	const IPC_DEFINITION* pstAckToPTransportSem = &stIPCConfigTable[IPC_LOGGER_ACK_SEM];
	DATA_MSG stLoggerReceiveMsg = {0};

	for(;;)
	{
		if (true == ThreadCoreQueueReceive(pstFromTransportQue, &stLoggerReceiveMsg,
																		portMAX_DELAY))
		{
			static bool blIsLEDOn = false;

			printf("%s: Received Button ID %lu. Processing...\r\n", LOGGER_THREAD,
														stLoggerReceiveMsg.ulButtonId);

			if (true == ThreadCoreSignalSemaphore(pstAckToPTransportSem))
			{
				printf("%s: ACK sent to %s.\r\n",LOGGER_THREAD,TRANSPORT_THREAD);

				if (blIsLEDOn == false)
				{
					HAL_GPIO_WritePin(GPIOB, LED_BLUE_Pin, GPIO_PIN_SET);
					blIsLEDOn = true;
					printf("%s: LED turned ON\r\n",LOGGER_THREAD);
				}
				else
				{
					HAL_GPIO_WritePin(GPIOB, LED_BLUE_Pin, GPIO_PIN_RESET);
					blIsLEDOn = false;
					printf("%s: LED turned OFF\r\n",LOGGER_THREAD);
				}

				printf("----------------------------------------\r\n\r\n");
			}
			else
			{
				printf("%s: Handshake ACK sent failed.\r\n",LOGGER_THREAD);

			}
		}
		else
		{
			printf("ERROR: %s failed to receive from %s\r\n",LOGGER_THREAD,
																TRANSPORT_DATA_QUEUE);
		}

	}

}
