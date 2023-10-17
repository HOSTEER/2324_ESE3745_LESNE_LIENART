#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usart.h"
#include "mylibs/shell.h"
#include "mylibs/pwm.h"
#include "tim.h"

void pwm_function_handler(void){
	if(strcmp(argv[1],"start")==0){
		pwm_start();
	}
	else if(strcmp(argv[1],"stop")==0){
		pwm_stop();
	}
	else if(strcmp(argv[1],"duty")==0){
		int dutyCycle = atoi(argv[2]);
		if(dutyCycle > 99){
			htim1.Instance->CCR1 = PWM_100;
		}else if(dutyCycle < 1){
			htim1.Instance->CCR1 = 0;
		}else{
			htim1.Instance->CCR1 = (  (  (float)dutyCycle  )/100  )*PWM_100;
		}
	}
}

void pwm_start(void){
	if(HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, PWM_50-1);
	if(HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, htim1.Instance->ARR - htim1.Instance->CCR1);
}

void pwm_stop(void){
	if(HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}

	if(HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error");
	}
}
