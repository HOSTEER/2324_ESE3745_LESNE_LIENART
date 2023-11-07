#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "usart.h"
#include "mylibs/shell.h"
#include "mylibs/pwm.h"
#include "tim.h"
#include "mylibs/asserv.h"

/**
 * @brief Initialise les paramètres de l'asservissement de vitesse.
 * @return Retourne 0 en cas de réussite.
 */
int asserv_speed_init(void){
	// Initialisation des paramètres de l'asservissement de vitesse
	asserv_speed.Kd = 0;
	asserv_speed.Ki = 0;
	asserv_speed.Kp = 1;
	asserv_speed.target_current = 0;
	return 0;
}

/**
 * @brief Initialise les paramètres de l'asservissement de courant.
 * @return Retourne 0 en cas de réussite.
 */
int asserv_current_init(void){
	// Initialisation des paramètres de l'asservissement de courant
	asserv_speed.Kd = 0;
	asserv_speed.Ki = 0;
	asserv_speed.Kp = 0.008;
	asserv_speed.target_current = 0;
	return 0;
}

/**
 * @brief Fonction principale pour le contrôle PID (asservissement).
 * @return Retourne 0 en cas de réussite.
 */
int pid_asserv(void){
	// Variables statiques pour le contrôle PID
	h_asserv_t * a = &asserv_current;
	static float current = 0, current_previous = 0;
	current_previous = current;
	current = (adcValue + current_previous)/2;

	// Variables pour le contrôle PID (calculs)
	static float new_epsilon = 0, previous_espilon = 0;
	static float integrator_output = 0, integrator_previous_ouput = 0.5;
	static float final_output = 0;
	new_epsilon = a->target_current - current;
	integrator_output = integrator_previous_ouput + a->Ki*(0.0001/2)*(new_epsilon - previous_espilon);
	final_output = integrator_output + a->Kp*new_epsilon;

	// Mise à jour des variables pour le prochain calcul
	previous_espilon = new_epsilon;
	integrator_previous_ouput = integrator_output;

	// Définition de dutyCycle en fonction du contrôle PID
	float dutyCycle = final_output;

	// Vérification de la plage de dutyCycle pour l'application PWM
	if(dutyCycle >= 0 && dutyCycle<=1){
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, (uint16_t)(  (  dutyCycle  )  )*PWM_100);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, htim1.Instance->ARR - htim1.Instance->CCR1);
	}
	else{
		HAL_GPIO_TogglePin(USR_LED_GPIO_Port, USR_LED_Pin);	// Clignoter la LED en cas de dépassement
	}
	return 0;
}

/**
 * @brief Gestionnaire des fonctions de l'asservissement.
 */
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
		begin = 1;					// Activation du système de contrôle de l'asservissement en courant
	}
}
