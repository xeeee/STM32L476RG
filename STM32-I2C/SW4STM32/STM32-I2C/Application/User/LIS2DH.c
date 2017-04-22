/*
 * LIS2DH.c
 *
 *  Created on: Feb 24, 2017
 *      Author: fabiomonteiro
 */
#include "main.h"
#include "LIS2DH.h"
#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "stdbool.h"

void ACC_Init(uint8_t ACC_ADDRESS)
{
	bool boot_check = 1;

	// Check if everything is OK with the Accelerometer...
	ACC_ADDRESS = (uint8_t) ACC_DEFAULT_ADDRESS << 1 | 0x00;
	while(boot_check)
	{
	  if (HAL_I2C_IsDeviceReady(&hi2c1,ACC_ADDRESS,1,10) == HAL_OK)
	  {
		  uint8_t ACC_ID;
		  HAL_I2C_Mem_Read(&hi2c1, ACC_ADDRESS, LIS2DH_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &ACC_ID, 1, 10);
		  if(ACC_ID == 0x33) boot_check = 0;
	  }
	}


	//Registers...
	uint8_t pData[17][2] =  {{0x1F, 0b00000000},	// Disable the temperature sensor									DONE
			   	   	   	   	 {0x20, 0b00010111},	// 1Hz, Normal Mode, XYZ Enabled									DONE
			   	   	   	   	 {0x21, 0b00000000},	// High Pass filter Disabled										DONE
			   	   	   	   	 {0x22, 0b01000000},	// Enables the I1_AOI1 interrupt on pin INT1						DONE
			   	   	   	   	 {0x23, 0b00000000},	// 2G, Low Power/NORMAL Mode Enabled								DONE
			   	   	   	   	 {0x24, 0b00000000},	// FIFO disabled, 4D detection disabled, Latch interrupt disabled	DONE
			   	   	   	   	 {0x25, 0b00100000},	// Enables the I2_INT2 interrupt on pin INT2						DONE
			   	   	   	   	 {0x26, 0b00000000},	// Reference value for Interrupt generation (HPF)					DONE
							 {0x2E, 0b00000000},	// FIFO Disabled													DONE

							 //Interrupt 1 - BOARD POSITION
							 {0x30, 0b00100110},	// OR Z-X Axis HIGH, Y Axis LOW Interrupt
							 {0x32, 0b00010000},	// Threshold (1LSB=16mg) => 256mg
							 {0x33, 0b00000010},	// Minimum duration of the Interrupt event to be recognized (1LSB=1/ODR) => 2Seconds

							 //Interrupt 2 - BOARD ACCELERATION
							 {0x34, 0b00100110},	// OR Z-X Axis LOW and HIGH Interrupt
							 {0x36, 0b00001000},	// Threshold (1LSB=16mg) => 128mg
							 {0x37, 0b00000000},	// Duration 0sec


							 //The LIS2DH can be programmed to automatically switch to Low power mode upon recognition of a determined event.
							 //  Once the event condition is over, the device returns back to the preset Normal or High resolution mode.
							 //Sleep to wake, return to Sleep activation...
							 // Not being used...
							 {0x3E, 0b00000000},	// Sleep to wake, return to Sleep activation threshold in Low power mode
							 {0x3F, 0b00000000}};	// Sleep to Wake, Return to Sleep duration


	uint8_t reg_size = sizeof(pData)/sizeof(pData[0]);
	for (int i=0; i<reg_size; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, ACC_ADDRESS, pData[i][0], I2C_MEMADD_SIZE_8BIT, &pData[i][1], 1, 100);
	}


}


void ACC_Read(uint8_t ACC_ADDRESS)
{
	int8_t pData[6] = {0,0,0,0,0,0};

	HAL_I2C_Mem_Read(&hi2c1, ACC_ADDRESS, (LIS2DH_OUT_X_L | 0x80), I2C_MEMADD_SIZE_8BIT, &pData, 6, 100);


	int16_t ACC_X = pData[0] | ((int16_t) pData[1]) << 8;
	int16_t ACC_Y = pData[2] | ((int16_t) pData[3]) << 8;
	int16_t ACC_Z = pData[4] | ((int16_t) pData[5]) << 8;

	double ACC_X_MS = ((double)ACC_X / 8190.0);
	double ACC_Y_MS = ((double)ACC_Y / 8190.0);
	double ACC_Z_MS = ((double)ACC_Z / 8190.0);


}
