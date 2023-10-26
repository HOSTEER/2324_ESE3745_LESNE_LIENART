#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "usart.h"
#include "mylibs/shell.h"
#include "mylibs/pwm.h"
#include "tim.h"
#include "mylibs/asserv.h"

int asserv_speed_init(void){
	asserv_speed.Kd = 0;
	asserv_speed.Ki = 0;
	asserv_speed.Kp = 1;
	asserv_speed.target_current = 0;
	return 0;
}

int asserv_current_init(void){
	asserv_speed.Kd = 0;
	asserv_speed.Ki = 0;
	asserv_speed.Kp = 0.008;
	asserv_speed.target_current = 0;
	return 0;
}

int pid_asserv(void){
	h_asserv_t * a = &asserv_current;
	static float current = 0, current_previous = 0;
	current_previous = current;
	current = (adcValue + current_previous)/2;

	static float new_epsilon = 0, previous_espilon = 0;
	static float integrator_output = 0, integrator_previous_ouput = 0.5;
	static float final_output = 0;
	new_epsilon = a->target_current - current;
	integrator_output = integrator_previous_ouput + a->Ki*(0.0001/2)*(new_epsilon - previous_espilon);
	final_output = integrator_output + a->Kp*new_epsilon;

	//Mise a jour des variables
	previous_espilon = new_epsilon;
	integrator_previous_ouput = integrator_output;


	float dutyCycle = final_output;

	if(dutyCycle >= 0 && dutyCycle<=1){

	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, (uint16_t)(  (  dutyCycle  )  )*PWM_100);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, htim1.Instance->ARR - htim1.Instance->CCR1);
	}
	else{
		HAL_GPIO_TogglePin(USR_LED_GPIO_Port, USR_LED_Pin);
	}
	return 0;
}

void asserv_function_handler(void){
	if(strcmp(argv[1],"speed")==0){
		int speed = atoi(argv[2]);
		if(speed > 1500){
			printf("valeur trop grande tour par minute > 1500\r\n");
		}else if(speed < -1500){
			printf("valeur trop petite tour par minute < -1500\r\n");
		}else{
			//asserv_speed. = speed;
			//printf("consigne = %f\r\n", asserv_speed.n_in);
		}
	}
	if(strcmp(argv[1],"start")==0){
		begin = 1;
	}
}
