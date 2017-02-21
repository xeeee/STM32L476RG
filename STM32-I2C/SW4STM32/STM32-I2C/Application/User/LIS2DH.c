/** Based on ST MicroElectronics LIS2DH datasheet
http://www.st.com/web/en/resource/technical/document/datasheet/DM00042751.pdf
* 30/09/2014 by Conor Forde <me@conorforde.com>
* Updates should be available at https://github.com/Snowda/LIS2DH
*
* Changelog:
*     ... - ongoing development release

* NOTE: THIS IS ONLY A PARIAL RELEASE. 
* THIS DEVICE CLASS IS CURRENTLY UNDERGOING ACTIVE DEVELOPMENT AND IS MISSING MOST FEATURES. 
* PLEASE KEEP THIS IN MIND IF YOU DECIDE TO USE THIS PARTICULAR CODE FOR ANYTHING.
*/

#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "gpio.h"
#include "stdbool.h"
#include "LIS2DH.h"

void ACC_Init(void)
{

	//HAL_I2C_Mem_Write(&hi2c1, ACC_ADDRESS, LIS2DH_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, 0x00, 1, 10);


}



//bool LIS2DH::(void) {
//    return 0;
//}
