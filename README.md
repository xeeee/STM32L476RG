## STM32L476RG
Some tests with the ST Nucleo-L476RG
(http://www.st.com/en/evaluation-tools/nucleo-l476rg.html)


## STM32-SPI

- The MCU polls the state of the MAX31913 input pins via the SPI Bus, checks the CRC, overvoltage, undervoltage and temperature warning...
- Does some post processing with the input states...
- Updated the output state of two daisy chained MAX14900E, configured in 16 bit mode and with CRC enabled!



## STM32-I2C

- Still in early development...
- To implement EEPROM and Accelerometer comunication.
