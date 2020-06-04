/**********************************************************************/
/* Programa diseñado para controlar un cruce automovilistico con dos  */
/* semaforos de automoviles y dos peatonales, con 2 minutos para el   */
/* verde de autos, 6 segundos de parpadeo en verde y 6 segundos de    */
/* amarillo, los peatones tienen 60 segundos para pasar en cada caso  */
/**********************************************************************/
 

/* El ricas se la come*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define	SEMAFORO_A_R	GPIO_NUM_0
#define	SEMAFORO_A_A	GPIO_NUM_1
#define	SEMAFORO_A_V	GPIO_NUM_2

#define	SEMAFORO_B_R	GPIO_NUM_3
#define	SEMAFORO_B_A	GPIO_NUM_4
#define	SEMAFORO_B_V	GPIO_NUM_5

#define	SEMAFORO_C_R	GPIO_NUM_6
#define	SEMAFORO_C_V	GPIO_NUM_7

#define	SEMAFORO_D_R	GPIO_NUM_8
#define	SEMAFORO_D_V	GPIO_NUM_9

void Semaforo(void);
void InicializarSalidas(void);
void Encender(int Cual);
void Apagar(int Cual);
void Toggle(int Cual);

int Paso = 0;

void app_main(void)
{
    InicializarSalidas();
    
    while(1) 
    {        
        Semaforo();
        vTaskDelay(1E6/portTICK_PERIOD_MS);   
    }
}

int Contador = 0;

void Semaforo(void)
{
	switch(Paso)
	{
		Contador++;
		
		case 1: //Verde Semaforo 1
			Apagar(SEMAFORO_D_V);
			Encender(SEMAFORO_D_R);
			Apagar(SEMAFORO_A_R);
			Encender(SEMAFORO_A_V);
			
			if(Contador >= 120)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 2: //Verde parpadeo Semaforo 1
			Toggle(SEMAFORO_A_V);
			if(Contador >= 6)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 3: //Amarillo Semaforo 1
			Apagar(SEMAFORO_A_V);
			Encender(SEMAFORO_A_A);
			if(Contador >= 6)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 4: //Verde Semaforo Peaton 1
			Apagar(SEMAFORO_A_A);
			Apagar(SEMAFORO_C_R);
			Encender(SEMAFORO_A_R);
			Encender(SEMAFORO_C_V);
			
			if(Contador >= 60)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 5: //Verde Semaforo 2
			Apagar(SEMAFORO_C_V);
			Apagar(SEMAFORO_B_R);
			Encender(SEMAFORO_C_R);
			Encender(SEMAFORO_B_V);
			if(Contador >= 120)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 6: //Verde parpadeo Semaforo 2
			Toggle(SEMAFORO_B_V);
			if(Contador >= 6)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 7: //Amarillo Semaforo 2
			Apagar(SEMAFORO_B_V);
			Encender(SEMAFORO_B_A);
			if(Contador >= 6)
			{
				Contador = 0;
				Paso++;
			}
			break;
			
		case 8: //Verde Semaforo Peaton 2
			Apagar(SEMAFORO_B_A);
			Apagar(SEMAFORO_D_R);
			Encender(SEMAFORO_B_R);
			Encender(SEMAFORO_D_V);
			
			if(Contador >= 60)
			{
				Contador = 0;
				Paso = 0;
			}
			break;		
	}
}

void Encender(int Cual)
{
	gpio_set_level(Cual, 1);
}

void Apagar(int Cual)
{
	gpio_set_level(Cual, 0);
}

void Toggle(int Cual)
{
	gpio_set_level(Cual, !gpio_get_level(Cual));
}

void InicializarSalidas(void)
{
	gpio_pad_select_gpio(SEMAFORO_A_R);
	gpio_pad_select_gpio(SEMAFORO_A_A);
	gpio_pad_select_gpio(SEMAFORO_A_V);
	
	gpio_pad_select_gpio(SEMAFORO_B_R);
	gpio_pad_select_gpio(SEMAFORO_B_A);
	gpio_pad_select_gpio(SEMAFORO_B_V);
	
	gpio_pad_select_gpio(SEMAFORO_C_R);
	gpio_pad_select_gpio(SEMAFORO_C_V);
	
	gpio_pad_select_gpio(SEMAFORO_D_R);
	gpio_pad_select_gpio(SEMAFORO_D_V);
	
	gpio_set_direction(SEMAFORO_A_R, GPIO_MODE_OUTPUT);
	gpio_set_direction(SEMAFORO_A_A, GPIO_MODE_OUTPUT);
	gpio_set_direction(SEMAFORO_A_V, GPIO_MODE_OUTPUT);
	
	gpio_set_direction(SEMAFORO_B_R, GPIO_MODE_OUTPUT);
	gpio_set_direction(SEMAFORO_B_A, GPIO_MODE_OUTPUT);
	gpio_set_direction(SEMAFORO_B_V, GPIO_MODE_OUTPUT);
	
	gpio_set_direction(SEMAFORO_C_R, GPIO_MODE_OUTPUT);
	gpio_set_direction(SEMAFORO_C_V, GPIO_MODE_OUTPUT);
	
	gpio_set_direction(SEMAFORO_D_R, GPIO_MODE_OUTPUT);
	gpio_set_direction(SEMAFORO_D_V, GPIO_MODE_OUTPUT);
	
	Encender(SEMAFORO_A_R);
	Apagar(SEMAFORO_A_A);
	Apagar(SEMAFORO_A_V);
	
	Encender(SEMAFORO_B_R);
	Apagar(SEMAFORO_B_A);
	Apagar(SEMAFORO_B_V);
	
	Encender(SEMAFORO_C_R);
	Apagar(SEMAFORO_C_V);
	
	Encender(SEMAFORO_D_R);
	Apagar(SEMAFORO_D_V);
    
}
