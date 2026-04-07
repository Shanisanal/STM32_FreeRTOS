FreeRTOS IPC Project 



Project Overview

This project demonstrates a robust Inter-Process Communication (IPC) architecture on the STM32U575 (Nucleo-U575ZI-Q). It demonstrates how to handle asynchronous hardware events (button press interrupts) and safely transport data between multiple FreeRTOS threads using binary semaphores, message queues, and a thread-safe "Handshake" logic. In response to every validated button press, the system toggles the User Blue LED between ON and OFF states, providing immediate visual feedback .



System Architecture

The system consists of three dedicated threads that cooperate to process a single button event:



1\. Poller Thread

Trigger: Blocks on a Binary Semaphore signaled by the User Button EXTI interrupt.



Action: On high GPIO state, it packages a button ID message and sends it to the Transport thread using a data queue.



Handshake: It remains blocked until it receives an ACK Semaphore back from the Transport Thread.



2\. Transport Thread 

Action: Receives data from the Poller thread and immediately sends an ACK back to the Poller thread to release it.



Forwarding: It then forwards the data to the Logger thread using data queue.



Handshake: It waits for a secondary ACK Semaphore from the Logger Thread before completing its cycle.



3\. Logger Thread 

Action: Receives the button ID data from the Transport Thread.



Handshake: Sends a final ACK back to the Transport Thread.



Output: Toggles the Blue LED and prints the system status to the UART console.

