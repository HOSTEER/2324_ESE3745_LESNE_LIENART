#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "usart.h"
#include "mylibs/shell.h"
#include "mylibs/pwm.h"
#include "tim.h"


/**
 * @brief Gère les fonctionnalités PWM en fonction des commandes reçues.
 * @details Cette fonction gère le démarrage, l'arrêt et l'ajustement de la vitesse des signaux PWM.
 */
void pwm_function_handler(void){
	if(strcmp(argv[1],"start")==0){
		pwm_start();
	}
	else if(strcmp(argv[1],"stop")==0){
		pwm_stop();
	}
	else if(strcmp(argv[1],"speed")==0){
		int dutyCycle = atoi(argv[2]);
		if(dutyCycle > 100){
			printf("valeur trop grande speed > 100\r\n");
		}else if(dutyCycle < 0){
			printf("valeur trop grande speed < 0\r\n");
		}else{
			// Définit le cycle de service pour le PWM en fonction de la vitesse reçue
			// Ajuste TIM_CHANNEL_1 et TIM_CHANNEL_2 en fonction du cycle de service.
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, (  (  (float)dutyCycle  )/100  )*PWM_100);
			__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, htim1.Instance->ARR - htim1.Instance->CCR1);
		}
	}
}

/**
 * @brief Démarre la sortie PWM sur des canaux spécifiques.
 * @details Initialise et démarre la sortie PWM sur TIM_CHANNEL_1 et TIM_CHANNEL_2.
 * Définit un rapport cyclique initial et synchronise TIM_CHANNEL_2 avec la sortie complémentaire.
 */
void pwm_start(void){
	// Démarre le PWM sur TIM_CHANNEL_1
	if(HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, PWM_50-1);

	// Démarre le PWM sur TIM_CHANNEL_2
	if(HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, htim1.Instance->ARR - htim1.Instance->CCR1);
}

/**
 * @brief Arrête la sortie PWM sur des canaux spécifiques.
 * @details Arrête la sortie PWM sur TIM_CHANNEL_1 et TIM_CHANNEL_2.
 */
void pwm_stop(void){
	// Arrête le PWM sur TIM_CHANNEL_1
	if(HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1)==HAL_ERROR){
		printf("pwm error\r\n");
	}

	// Arrête le PWM sur TIM_CHANNEL_2
	if(HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
	if(HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2)==HAL_ERROR){
		printf("pwm error\r\n");
	}
}
