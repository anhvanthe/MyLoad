#ifndef _MCP4822_H_
#define _MCP4822_H_

#include"main.h"

extern SPI_HandleTypeDef hspi2;

typedef enum{
	
	DAC_A=0,
	DAC_B
}DACx;

typedef enum{
	
	GAIN_X1=0,
	GAIN_X2
}OUTPUT_GAIN;

typedef enum{
	
	ACTIVE_MODE=0,
	SHUTDOWN_MODE
}OUTPUT_SHUTDOWN;

void MCP4822_DAC_Write(DACx DAC, OUTPUT_GAIN GAIN, OUTPUT_SHUTDOWN ACTIVE, uint16_t value);


#endif
