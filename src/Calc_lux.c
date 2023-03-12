/*
 * Calc_lux.c
 *
 * Created: 2022-11-16 11:13:00
 *  Author: mini0072
 */ 
#include <inttypes.h>

float LSB_calc(uint16_t Lux_result)
{	
	uint8_t LSB = 0;
	float LSB_float = 0;
	Lux_result = Lux_result & 0b1111000000000000;
	Lux_result = (Lux_result>>12);
	LSB = Lux_result;
	
	switch(LSB)
	{
		case 0:
			LSB_float = 0.01;
			break;
		case 1:
			LSB_float= 0.02;
			break;
		case 2:
			LSB_float = 0.04;
			break;
		case 3:
			LSB_float = 0.08;
			break;
		case 4:
			LSB_float = 0.16;
			break;
		case 5:
			LSB_float = 0.32;
			break;
		case 6:
			LSB_float = 0.64;
			break;
		case 7:
			LSB_float = 1.28;
			break;
		case 8:
			LSB_float = 2.56;
			break;
		case 9:
			LSB_float = 5.12;
			break;
		case 10:
			LSB_float = 10.24;
			break;
		case 11:
			LSB_float = 20.48;
			break;
		default:
			LSB_float = 0.01;
	}
	return LSB_float;
}

uint16_t Calc_lux(uint16_t Lux_result, float LSB)
{	
	uint16_t Lux_reading = 0;
	 
	Lux_result = Lux_result & 0b0000111111111111;
	
	Lux_reading = (uint16_t)(LSB * Lux_result);
	
	return Lux_reading;
}