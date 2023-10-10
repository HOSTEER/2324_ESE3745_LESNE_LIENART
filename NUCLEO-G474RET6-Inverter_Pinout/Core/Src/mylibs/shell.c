/*
 * shell.c
 *
 *  Created on: Oct 1, 2023
 *      Author: nicolas
 */
#include "usart.h"
#include "mylibs/shell.h"
#include <stdio.h>
#include <string.h>

uint8_t prompt[]="user@Nucleo-STM32G474RET6>>";
uint8_t started[]=
		"\r\n*-----------------------------*"
		"\r\n| Welcome on Nucleo-STM32G474 |"
		"\r\n*-----------------------------*"
		"\r\n";
uint8_t newline[]="\r\n";
uint8_t backspace[]="\b \b";
uint8_t cmdNotFound[]="Command not found\r\n";
uint8_t brian[]="Brian is in the kitchen\r\n";
uint8_t uartRxReceived;
uint8_t uartRxBuffer[UART_RX_BUFFER_SIZE];
uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE];

char	 	cmdBuffer[CMD_BUFFER_SIZE];
int 		idx_cmd;
char* 		argv[MAX_ARGS];
int		 	argc = 0;
char*		token;
int 		newCmdReady = 0;


/**
 * @brief Initializes the shell environment.
 *
 * This function initializes various buffers and sets up UART communication using
 * the HAL (Hardware Abstraction Layer) for STM32 microcontrollers.
 */
void Shell_Init(void){
	memset(argv,(int)NULL, MAX_ARGS*sizeof(char*));
	memset(cmdBuffer, (int)NULL, CMD_BUFFER_SIZE*sizeof(char));
	memset(uartRxBuffer,(int)NULL, UART_RX_BUFFER_SIZE*sizeof(char));
	memset(uartTxBuffer,(int)NULL, UART_TX_BUFFER_SIZE*sizeof(char));

	HAL_UART_Receive_IT(&huart2, uartRxBuffer, UART_RX_BUFFER_SIZE);
	HAL_UART_Transmit(&huart2, started, strlen((char *)started), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, prompt, strlen((char *)prompt), HAL_MAX_DELAY);
}


/**
 * @brief Main loop for the shell functionality.
 *
 * This function handles user input from UART and processes commands accordingly.
 * It listens for UART input and performs the following actions:
 *
 * - If a newline character is received, it tokenizes the command, sets up argument
 *   pointers, and signals that a new command is ready.
 * - If a backspace character is received, it removes the last character from the
 *   command buffer.
 * - If any other character is received, it appends it to the command buffer and
 *   echoes it back to the UART.
 *
 * Once a new command is ready, it checks for specific commands and responds accordingly:
 * - If the command is "WhereisBrian?", it transmits a response with information.
 * - If the command is "help", it transmits a list of available functions.
 * - Otherwise, it transmits a "Command not found" message.
 *
 * After processing a command, it transmits the shell prompt for the next input.
 */
void Shell_Loop(void){
	if(uartRxReceived){
		switch(uartRxBuffer[0]){
		case ASCII_CR: // Nouvelle ligne, instruction à traiter
			HAL_UART_Transmit(&huart2, newline, sizeof(newline), HAL_MAX_DELAY);
			cmdBuffer[idx_cmd] = '\0';
			argc = 0;
			token = strtok(cmdBuffer, " ");
			while(token!=NULL){
				argv[argc++] = token;
				token = strtok(NULL, " ");
			}
			idx_cmd = 0;
			newCmdReady = 1;
			break;
		case ASCII_BACK: // Suppression du dernier caractère
			cmdBuffer[idx_cmd--] = '\0';
			HAL_UART_Transmit(&huart2, backspace, sizeof(backspace), HAL_MAX_DELAY);
			break;

		default: // Nouveau caractère
			cmdBuffer[idx_cmd++] = uartRxBuffer[0];
			HAL_UART_Transmit(&huart2, uartRxBuffer, UART_RX_BUFFER_SIZE, HAL_MAX_DELAY);
		}
		uartRxReceived = 0;
	}

	if(newCmdReady){
		if(strcmp(argv[0],"WhereisBrian?")==0){
			HAL_UART_Transmit(&huart2, brian, sizeof(brian), HAL_MAX_DELAY);
		}
		else if(strcmp(argv[0],"help")==0){
			int uartTxStringLength = snprintf((char *)uartTxBuffer, UART_TX_BUFFER_SIZE, "Print all available functions here\r\n");
			HAL_UART_Transmit(&huart2, uartTxBuffer, uartTxStringLength, HAL_MAX_DELAY);
		}
		else{
			HAL_UART_Transmit(&huart2, cmdNotFound, sizeof(cmdNotFound), HAL_MAX_DELAY);
		}
		HAL_UART_Transmit(&huart2, prompt, sizeof(prompt), HAL_MAX_DELAY);
		newCmdReady = 0;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart){
	uartRxReceived = 1;
	HAL_UART_Receive_IT(&huart2, uartRxBuffer, UART_RX_BUFFER_SIZE);
}
