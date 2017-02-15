/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"
#include "crc.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
#define NSS_DO_pin		GPIO_PIN_6
#define NSS_DO_port		GPIOC
#define NSS_DI_pin		GPIO_PIN_12
#define NSS_DI_port		GPIOB
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void setNSS_DO(GPIO_PinState PinState);
void setNSS_DI(GPIO_PinState PinState);
static void Delay(__IO uint32_t nTime);
unsigned char crcSmallEncode16 (unsigned char byte1, unsigned char byte2);
unsigned char Loop_CRC (unsigned char crc, unsigned char byte);
bool crcSmallCheck16 (unsigned char byte1, unsigned char byte2, unsigned char byte3);
uint8_t checkCRC(uint8_t inputs);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

//MAX14900E
uint8_t MAX1_IN_Settings 	  = 0x00;
uint8_t MAX1_IN_Configuration = 0x00;
uint8_t MAX1_IN_CRC           = 0x00;
uint8_t MAX2_IN_Settings 	  = 0x00;
uint8_t MAX2_IN_Configuration = 0x00;
uint8_t MAX2_IN_CRC           = 0x00;
uint8_t MAX1_OUT_FaultBits    = 0x00;
uint8_t MAX1_OUT_StatusBits   = 0x00;
uint8_t MAX1_OUT_CRC          = 0x00;
uint8_t MAX2_OUT_FaultBits    = 0x00;
uint8_t MAX2_OUT_StatusBits   = 0x00;
uint8_t MAX2_OUT_CRC          = 0x00;
bool    MAX1_CRC_OK;
bool    MAX2_CRC_OK;

//MAX31913
uint8_t MAX1_INPUTS       = 0x00;
uint8_t MAX1_ERRORS       = 0x00;
uint8_t MAX1_CRC	      = 0x00;
uint8_t MAX1_OVERVOLTAGE  = 0x00;
uint8_t MAX1_EXPECTED_CRC = 0x00;
bool    MAX1_INPUT_CRC_OK;
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI2_Init();
  MX_CRC_Init();

  /* USER CODE BEGIN 2 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		/* Capture error */
		while (1);
	}


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


	// The NSS pin starts HIGH!
	setNSS_DO(GPIO_PIN_SET);
	setNSS_DI(GPIO_PIN_SET);

	while (1)
	{
		// INPUT PART
		// Read MAX31913 Inputs!
		setNSS_DI(GPIO_PIN_RESET);
		HAL_SPI_Receive(&hspi2, &MAX1_INPUTS, 1, 10);
		HAL_SPI_Receive(&hspi2, &MAX1_ERRORS, 1, 10);
		setNSS_DI(GPIO_PIN_SET);

		MAX1_CRC 		 	= (MAX1_ERRORS & 0b11111000) >> 3;
		MAX1_OVERVOLTAGE 	= MAX1_ERRORS & 0b00000111;
		MAX1_EXPECTED_CRC	= checkCRC(MAX1_INPUTS);

		/* Insert ms delay */
		Delay(5000);


		//TODO: compare "MAX1_CRC" with "MAX1_EXPECTED_CRC"
		// if true, then update the state of the output pins


		// OUTPUT PART
		// Each MAX14900E is configured to receive and output 16bits
		// The input is divided in two 8bits registers (Settings and Configuration)
		// The Settings (DOx) bits configure each output pin as ON (1/HIGH) or OFF (0/LOW)
		// The Configuration (Cx) bits configure each output pin as HIGH-SIDE (0) or PUSH-PULL (1)
	    MAX1_IN_Settings      = 0b11110000;
	  	MAX2_IN_Settings      = 0b00001111;
	    MAX1_IN_Configuration = 0b00000000;
	  	MAX2_IN_Configuration = 0b00000000;


	  	// It's necessary to send more 8 bits with the proper CRC
	  	// for the MAX14900E to accept the Settings and Configurations!
	  	MAX1_IN_CRC = crcSmallEncode16 (MAX1_IN_Settings, MAX1_IN_Configuration);
	  	MAX2_IN_CRC = crcSmallEncode16 (MAX2_IN_Settings, MAX2_IN_Configuration);


		// Send/Receive 3x8 Bits to SPI
		setNSS_DO(GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive(&hspi2, &MAX1_IN_Settings, &MAX1_OUT_FaultBits, 1, 10);
		HAL_SPI_TransmitReceive(&hspi2, &MAX1_IN_Configuration, &MAX1_OUT_StatusBits, 1, 10);
		HAL_SPI_TransmitReceive(&hspi2, &MAX1_IN_CRC, &MAX1_OUT_CRC, 1, 10);
		HAL_SPI_TransmitReceive(&hspi2, &MAX2_IN_Settings, &MAX2_OUT_FaultBits, 1, 10);
		HAL_SPI_TransmitReceive(&hspi2, &MAX2_IN_Configuration, &MAX2_OUT_StatusBits, 1, 10);
		HAL_SPI_TransmitReceive(&hspi2, &MAX2_IN_CRC, &MAX2_OUT_CRC, 1, 10);
		setNSS_DO(GPIO_PIN_SET);


		// Each MAX14900E send us 16bits with Monitoring Data
		// The first 8 bits (Fx) are the Output Fault bits
		// The second 8 bits (Sx) are the Output Status bits
		MAX1_CRC_OK = crcSmallCheck16(MAX1_OUT_FaultBits, MAX1_OUT_StatusBits, MAX1_OUT_CRC);
		MAX2_CRC_OK = crcSmallCheck16(MAX2_OUT_FaultBits, MAX2_OUT_StatusBits, MAX2_OUT_CRC);


	    /* Insert ms delay */
	    Delay(5000);




  /* USER CODE END WHILE */


  /* USER CODE BEGIN 3 */



  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the main internal regulator output voltage 
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}






/* USER CODE BEGIN 4 */

// Functions to change the Chip Select Pins!
void setNSS_DO(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(NSS_DO_port, NSS_DO_pin, PinState);
}

void setNSS_DI(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(NSS_DI_port, NSS_DI_pin, PinState);
}


// CRC stuff for the MAX31913
// Adapted from: https://www.ghsi.de/CRC/
//
uint8_t checkCRC(uint8_t inputs)
{
	char BitString[8];
	uint8_t Res = 0;
	uint8_t nCRC[5];
	int i;
	char DoInvert;

	for (i=0; i<8; i++)		BitString[7-i] = (inputs >> i) & 1 ? '1' : '0';

	for (i=0; i<5; ++i)		nCRC[i] = 0;                    // Init before calculation

	for (i=0; i<strlen(BitString); ++i)
	{
		DoInvert = ('1'==BitString[i]) ^ nCRC[4];         // XOR required?

		nCRC[4] = nCRC[3] ^ DoInvert;
		nCRC[3] = nCRC[2];
		nCRC[2] = nCRC[1] ^ DoInvert;
		nCRC[1] = nCRC[0];
		nCRC[0] = DoInvert;
	}

	for (i=5; i>=0; i--)	Res = (uint8_t) (Res << 1) | nCRC[i];

	return(Res);
}


// CRC stuff for the MAX14900E
// https://www.maximintegrated.com/en/app-notes/index.mvp/id/6002
//
unsigned char crcSmallEncode16 (unsigned char byte1, unsigned char byte2)
{
	unsigned char synd;

	synd = Loop_CRC (0x7f, byte1);
	synd = Loop_CRC (synd, byte2);
	return Loop_CRC (synd, 0x80) | 0x80;
}

unsigned char Loop_CRC (unsigned char crc, unsigned char byte)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		crc <<= 1;
		if (crc & 0x80)
			crc ^= 0xB7; // 0x37 with MSBit on purpose
		if (byte & 0x80)
			crc ^=1;
		byte <<= 1;
	}

	return crc;
}

bool crcSmallCheck16 (unsigned char byte1, unsigned char byte2, unsigned char byte3)
{
	unsigned char synd;

	synd = Loop_CRC (0x7f, byte1);
	synd = Loop_CRC (synd, byte2);
	return Loop_CRC (synd, byte3) == 0;
}





/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0)
  {
    TimingDelay--;
  }
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
