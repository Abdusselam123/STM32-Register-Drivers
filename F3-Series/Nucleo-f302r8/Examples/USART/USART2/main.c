/**
 * @file 			main.c (USART2_init_example_1)
 * @brief 			STM32 USART2 register-level initialization example 1 (Register-level, no HAL/LL)
 * @target-board	stm32-NUCLEO-f302r8
 * @author 			Abdusselam
 * @license 		MIT
 */


#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"

#define USART2_AF 					7
#define USART2_TX_PIN				2
#define USART2_RX_PIN				3
/* * NOTE: USART2 clock selection (USART2SW bits in RCC_CFGR3) is NOT available on STM32F302x8 devices.
 * USART2 is internally hard-wired to PCLK. 
 * Since we are running on default HSI (8MHz) and APB1 prescaler is 1,
 * USART2_BUS_CLOCK_HZ is fixed at 8,000,000Hz.
 */
#define USART2_BUS_CLOCK_HZ			8000000U
#define USART2_TARGET_BAUDRATE		9600U

void USART2_Init(void);

int main(void){
	//HAL_Init() is called because we need the HAL tick..
	//..for the test delay functions (i.e., HAL_Delay).
	HAL_Init();

	//Call the custom USART2_Init() function to configure..
	//..peripheral registers for initial setup.
	USART2_Init();

	while(1){

		//Transmit a test character every 100ms:
		while(!(USART2->ISR & USART_ISR_TXE));
		USART2->TDR = 'a';
		HAL_Delay(100);

	}//while(1) end
}//int main end



void USART2_Init(void)
	{
	//CLOCK SETTINGS
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//USART2_TX_PIN RESET & AF
	GPIOA->MODER &= ~(3<<(USART2_TX_PIN*2));
	GPIOA->MODER |= (2<<(USART2_TX_PIN*2));

	//USART2_RX_PIN RESET & AF
	GPIOA->MODER &= ~(3<<(USART2_RX_PIN*2));
	GPIOA->MODER |= (2<<(USART2_RX_PIN*2));

	//PA2 & PA3 RESET
	GPIOA->AFR[0] &= ~(0xF<<(USART2_TX_PIN*4));
	GPIOA->AFR[0] &= ~(0xF<<(USART2_RX_PIN*4));

	//PA2 & PA3 AF7
	/* * Map PA2 & PA3 to AF7 (USART2).
	 *Consult the Datasheet (e.g., Table 14: Alternate Functions) for correct AF values:
	 *Link: https://www.st.com/resource/en/datasheet/stm32f302r6.pdf
	 */
	GPIOA->AFR[0] |= (USART2_AF<<(USART2_TX_PIN*4));
	GPIOA->AFR[0] |= (USART2_AF<<(USART2_RX_PIN*4));

	//USART SETTINGS
	//Calculate and set the approximate Baud Rate (BRR) for the target speed:
	USART2->BRR = (USART2_BUS_CLOCK_HZ + (USART2_TARGET_BAUDRATE/2))/USART2_TARGET_BAUDRATE;
	//USART2 Transmitter and Receiver ENABLE:
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
	//USART2 ENABLE:
	USART2->CR1 |= USART_CR1_UE;
	}
