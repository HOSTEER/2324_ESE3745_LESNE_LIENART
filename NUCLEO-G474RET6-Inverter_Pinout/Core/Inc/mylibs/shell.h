/*
 * shell.h
 *
 *  Created on: Oct 1, 2023
 *      Author: nicolas
 */

#ifndef INC_MYLIBS_SHELL_H_
#define INC_MYLIBS_SHELL_H_

#define UART_RX_BUFFER_SIZE 1
#define UART_TX_BUFFER_SIZE 64
#define CMD_BUFFER_SIZE 64
#define MAX_ARGS 9
#define ASCII_LF 0x0A			// LF = line feed, saut de ligne
#define ASCII_CR 0x0D			// CR = carriage return, retour chariot
#define ASCII_BACK 0x08			// BACK = Backspace

void Shell_Init(void);
void Shell_Loop(void);
void pwm_function_handler(void);
void pwm_start(void);
void pwm_stop(void);

uint8_t duty_cycle_interpretor(void);

#endif /* INC_MYLIBS_SHELL_H_ */


