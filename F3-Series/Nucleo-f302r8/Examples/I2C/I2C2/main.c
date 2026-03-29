/**
 * @file 			main.c (I2C2_init_example_1)
 * @brief 			STM32 I2C2 register-level initialization example 1 (Register-level, no HAL/LL)
 * @target-board	stm32-NUCLEO-f302r8
 * @author 			Abdusselam
 * @license 		MIT
 */

#include "stm32f3xx.h"

#define SDA_PIN		10		//PA10
#define SCL_PIN		9		//PA9

void i2c2_init_example_1(void);

int main(void){
	i2c2_init_example_1();

	while(1){


	}//while(1) end
}//int main end


void i2c2_init_example_1(void){
	//CLOCK SETTINGS
	RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

	/**
	 * @brief  I2C2 Clock Source Configuration
 	 * @note   Reference Manual RM0365 - Section 9.4.13: RCC_CFGR3 Register
 	 * * The I2C2SW (Bit 5) bit is used to select the I2C2 clock source:
 	 * 0: HSI clock selected as I2C2 clock source (Default 8MHz)
 	 * 1: SYSCLK clock selected as I2C2 clock source
 	 *
 	 * Why we use the Masking & Logical OR method instead of 'RCC->CFGR3 &= ~(1 << 5);' ?
 	 * 1. Portability: Macros adapt to different MCU variants automatically.
 	 * 2. Readability: 'I2C2SW_HSI' explicitly states the INTENT of the code.
 	 * 3. Safety: 'Msk' ensure only the target bits are modified without affecting neighbors.
 	 */

	/* 1. Clear the specific bit(s) using the bit-mask */
	RCC->CFGR3 &= ~(RCC_CFGR3_I2C2SW_Msk);

	/* 2. Set the desired value (0 for HSI) */
	/* Note: While HSI is 0 and setting it is technically 'redundant' after a clear,
   	   using the macro is a professional 'seal' that confirms the design choice. */
	RCC->CFGR3 |= (RCC_CFGR3_I2C2SW_HSI);

	//SDA PIN RESET & AF
	GPIOA->MODER &= ~(3 << (SDA_PIN*2));
	GPIOA->MODER |=  (2 << (SDA_PIN*2));

	//SCL PIN RESET & AF
	GPIOA->MODER &= ~(3 << (SCL_PIN*2));
	GPIOA->MODER |=  (2 << (SCL_PIN*2));

	//SCL AND SDA OPEN-DRAIN MODE
	GPIOA->OTYPER |= (1 << SDA_PIN);
	GPIOA->OTYPER |= (1 << SCL_PIN);


	/* * Map PA9 & PA10 to AF4 (I2C2).
	 *Consult the Datasheet (e.g., Table 14: Alternate Functions) for correct AF values:
	 *Link: https://www.st.com/resource/en/datasheet/stm32f302r6.pdf
	 */
	//SDA AF MODE SET
	GPIOA->AFR[1] &= ~(0xF << (SDA_PIN-8)*4);
	GPIOA->AFR[1] |=  (4 << (SDA_PIN-8)*4);

	//SCL AF MODE SET
	GPIOA->AFR[1] &= ~(0xF << (SCL_PIN-8)*4);
	GPIOA->AFR[1] |=  (4 << (SCL_PIN-8)*4);

	// I2C2 Timing for 100kHz Standard Mode @ 8MHz I2CCLK (RM0365, Table 143)
	I2C2->TIMINGR = (0x01U << 28) | // PRESC: 8MHz / (1+1) = 4MHz internal clock
                	(0x04U << 20) | // SCLDEL: Data setup time
					(0x02U << 16) | // SDADEL: Data hold time
					(0x0FU << 8)  | // SCLH: High period
					(0x13U << 0);   // SCLL: Low period


	I2C2->CR1 |= I2C_CR1_PE;

}
