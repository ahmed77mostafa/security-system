/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stm32f401xx.h>


#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3
#define BUTTON4_PIN 4

#define GREENLED_PIN 10
#define REDLED_PIN 11
#define BUZZER_PIN 15

int main(void)
{
	int sequence[] = {1, 2, 3, 4};
	int input[4];
	int index = 0;
	RCC->AHB1ENR |= (1 << 0);

	GPIOA->MODER |= ((1 << 2*GREENLED_PIN) | (1 << 2*REDLED_PIN) | (1 << 2*BUZZER_PIN));
	GPIOA->MODER &= ~((0b11 << 2 * BUTTON1_PIN) | (0b11 << 2 * BUTTON2_PIN) | (0b11 << 2 * BUTTON3_PIN) | (0b11 << 2 * BUTTON4_PIN));
	GPIOA->PUPDR |= ((0b10 << 2 * BUTTON1_PIN) | (0b10 << 2 * BUTTON2_PIN) | (0b10 << 2 * BUTTON3_PIN) | (0b10 << 2 * BUTTON4_PIN));

	while(1)
	{
		if(GPIOA->IDR & (1 << BUTTON1_PIN) && index < 4){
			input[index++] = 1;
			while(GPIOA->IDR & (1 << BUTTON1_PIN) && index < 4);
		}
		if(GPIOA->IDR & (1 << BUTTON2_PIN) && index < 4){
			input[index++] = 2;
			while(GPIOA->IDR & (1 << BUTTON2_PIN) && index < 4);
		}
		if(GPIOA->IDR & (1 << BUTTON3_PIN) && index < 4){
			input[index++] = 3;
			while(GPIOA->IDR & (1 << BUTTON3_PIN) && index < 4);
		}
		if(GPIOA->IDR & (1 << BUTTON4_PIN) && index < 4){
			input[index++] = 4;
			while(GPIOA->IDR & (1 << BUTTON4_PIN) && index < 4);
		}
		if(index == 4){
			int match = 1;
			for(int i = 0; i < 4; i++){
				if(input[i] != sequence[i]){
					match=0;
					break;
				}
			}

			if(match){
				GPIOA->ODR = (1 << GREENLED_PIN);
			}else{
				GPIOA->ODR = ((1 << REDLED_PIN) | (1 << BUZZER_PIN));
			}
			index = 0;
		}
	}
}
