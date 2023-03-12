/*
 * I2C_readwrite.c
 *
 * Created: 2022-11-15 10:04:26
 *  Author: mini0072
 */ 
#define F_CPU 1000000UL

#include <inttypes.h>
#include "i2cmaster.h"
#include <stdio.h>
#include <util/delay.h>

uint8_t Scan_i2c_bus(uint8_t* active_address1, uint8_t* active_address2, uint8_t *active_address3)
{
	uint8_t count = 0;
	//LUX-sensor
	*active_address1 = 0;
	//EEPROM
	*active_address2 = 0;
	//Klocka
	*active_address3 = 0;
	
	for(int i = 0x06 ; i <= 0xFE ; i = i + 2)
	{
		if(!(i2c_start(i)))
		{
			if (count == 0)
			{
				*active_address1 = i;
				i2c_stop();
				count++;
			}
			else if (count == 1)
			{
				*active_address2 = i;
				i2c_stop();
				count++;
				//EEPROM har fler addresser än 1 hoppa övriga
				i = i+2;
			}
			else if (count == 2)
			{
				*active_address3 = i;
				i2c_stop();
				count++;
			}
			
			
			
		}
		
		
	}
	
	if(count != 0)
	{
		return count;
	}
	else
	{	
		return 0;
	}
	
}

void Sensor_write(uint8_t Sensor_addr, uint8_t Reg_addr, uint8_t Command_high, uint8_t Command_low)
{
	
	if((i2c_start(Sensor_addr)))
	{
		printf("No sensor found    ");
	}
	
	
	if((i2c_write(Reg_addr)))
	{
		printf("Error ");
	}
	if((i2c_write(Command_high)))
	{
		printf("Error ");
	}
	if((i2c_write(Command_low)))
	{
		printf("Error ");
	}
	
	_delay_ms(1);
	i2c_stop();
}

uint16_t Sensor_read(uint8_t Sensor_addr, uint8_t Read_reg)
{
	uint16_t Result;
	
	i2c_start(Sensor_addr);
	i2c_write(Read_reg);
	i2c_rep_start(Sensor_addr+1);
	Result = i2c_readAck();
	
	Result =(Result<<8) + i2c_readNak();
	i2c_stop();
	
	
	return Result;
}

void E2PROM_write(uint8_t Sensor_addr, volatile uint16_t *Mem_addr, uint8_t *data, uint8_t arr_length)
{
	
	uint8_t H_mem_addr = 0;
	uint8_t L_mem_addr = 0;
	//SEPARERAR 16bitars till hög och låg 8bitars
	L_mem_addr = *Mem_addr & 0b0000000011111111;
	H_mem_addr = (*Mem_addr>>8);
	
	
	if((i2c_start(Sensor_addr)))
	{
		printf("No sensor found    ");
	}
	
	
	if((i2c_write(H_mem_addr)))
	{
		printf("Error ");
	}
	if((i2c_write(L_mem_addr)))
	{
		printf("Error ");
	}
	for (int i = 0 ; i < arr_length; i++ )
	{
		if((i2c_write(data[i])))
		{
			printf("Error ");
		}
		*Mem_addr = *Mem_addr + 1;
	}
	i2c_stop();
	
	_delay_ms(1);
}

void E2PROM_read(uint8_t Sensor_addr, uint16_t Mem_addr, volatile uint8_t *data, uint8_t arr_length)
{
	uint8_t H_mem_addr = 0;
	uint8_t L_mem_addr = 0;
	
	L_mem_addr = Mem_addr & 0b0000000011111111;
	H_mem_addr = (Mem_addr>>8);
	
	i2c_start(Sensor_addr);
	i2c_write(H_mem_addr);
	i2c_write(L_mem_addr);
	i2c_rep_start(Sensor_addr+1);
	for (int i = 0 ; i < (arr_length-1); i++ )
	{
		
		data[i] = i2c_readAck();
	}
	
	
	data[arr_length-1] = i2c_readNak();
	
	i2c_stop();
	
	
	return;
}

