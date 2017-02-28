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


void ACC_Init(uint8_t ACC_ADDRESS)
{
	//Registers...
	uint8_t pData[17][2] =  {{0x1F, 0b00000000},	// Disable the temperature sensor									DONE
			   	   	   	   	 {0x20, 0b00011111},	// 1Hz, Low Power Mode, XYZ Enabled									DONE
			   	   	   	   	 {0x21, 0b00000000},	// High Pass filter Disabled										DONE
			   	   	   	   	 {0x22, 0b01000000},	// Enables the AOI1 interrupt on pin INT1							DONE
			   	   	   	   	 {0x23, 0b00000000},	// 2G, Low Power Mode Enabled										DONE
			   	   	   	   	 {0x24, 0b00000000},	// FIFO disabled, 4D detection disabled, Latch interrupt disabled 	DONE
			   	   	   	   	 {0x25, 0b00000000},	// Interrupt on pin INT2	Disabled								DONE
			   	   	   	   	 {0x26, 0b00000000},	// Reference value for Interrupt generation (HPF)???				DONE
			   	   	   	   	 {0x2E, 0b00000000},	// FIFO Disabled													DONE

							 //Interrupt 1
							 {0x30, 0b00101001},	// OR Z-Y Axis HIGH, X Axis LOW Interrupt
							 {0x32, 0b00100000},	// Threshold (1LSB=16mg) => 512mg
							 {0x33, 0b00000101},	// Minimum duration of the Interrupt event to be recognized (1LSB=1/ODR) => 5Seconds

							 //Interrupt 2
							 {0x34, 0b00000000},
							 {0x36, 0b00000000},
							 {0x37, 0b00000000},

							 /*The LIS2DH can be programmed to automatically switch to Low power mode upon recognition of a determined event.
							   Once the event condition is over, the device returns back to the preset Normal or High resolution mode.*/
							 //Sleep to wake, return to Sleep activation...
							 {0x3E, 0b00000000},	// Sleep to wake, return to Sleep activation threshold in Low power mode
							 {0x3F, 0b00000000}};	// Sleep to Wake, Return to Sleep duration


	uint8_t reg_size = sizeof(pData)/sizeof(pData[0]);
	for (int i=0; i<reg_size; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1, ACC_ADDRESS, pData[i][0], I2C_MEMADD_SIZE_8BIT, &pData[i][1], 1, 100);
	}




}
