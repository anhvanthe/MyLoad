#include"MCP4822.h"

void MCP4822_DAC_Write(DACx DAC, OUTPUT_GAIN GAIN, OUTPUT_SHUTDOWN ACTIVE, uint16_t value){
		
	uint16_t data=0;
	HAL_GPIO_WritePin(DAC_CS_GPIO_Port,DAC_CS_Pin, GPIO_PIN_RESET);
	if(DAC == DAC_B)
		data|=(1<<15);
	else
		data&=~(1<<15);
	
	if(GAIN == GAIN_X1)
		data|=(1<<13);
	else
		data&=~(1<<13);
	
	if(ACTIVE == ACTIVE_MODE)
		data|=(1<<12);
	else
		data&=~(1<<12);
	
	data|=(value&0x0FFF);
	
	HAL_SPI_Transmit(&hspi2,(uint8_t*)&data,2,100);
	
	HAL_GPIO_WritePin(DAC_CS_GPIO_Port,DAC_CS_Pin, GPIO_PIN_SET);
	
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(DAC_LATCH_GPIO_Port,DAC_LATCH_Pin, GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(DAC_LATCH_GPIO_Port,DAC_LATCH_Pin, GPIO_PIN_SET);
}
