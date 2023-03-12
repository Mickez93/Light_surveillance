/*
 * Clk_i2c_rw.c
 *
 * Created: 2022-11-17 13:55:12
 *  Author: mini0072
 */ 
#define F_CPU 1000000UL

#include <inttypes.h>
#include "i2cmaster.h"
#include <stdio.h>
#include <util/delay.h>





void Clk_write_ctrl(uint8_t Sensor_addr, uint8_t Reg_addr, uint8_t Command)
{
	
	if((i2c_start(Sensor_addr)))
	{
		printf("No sensor found    ");
	}
	
	
	if((i2c_write(Reg_addr)))
	{
		printf("Error ");
	}
	if((i2c_write(Command)))
	{
		printf("Error ");
	}
	
	i2c_stop();
	_delay_ms(1);
}

void Clk_write_data(uint8_t Sensor_addr, uint8_t Reg_addr, uint8_t data[], uint8_t arr_length)
{
	if((i2c_start(Sensor_addr)))
	{
		printf("No sensor found    ");
	}
	
	
	if((i2c_write(Reg_addr)))
	{
		printf("Error ");
	}
	for(int i = 0 ; i < arr_length ; i++)
	{	
		
		if((i2c_write(data[i])))
		{
			printf("Error ");
		}
	}
	i2c_stop();
	_delay_ms(1);
	
}

void Clk_read_data(uint8_t Sensor_addr, uint8_t Read_reg, uint8_t *data,uint8_t arr_length)
{
	
	
	i2c_start(Sensor_addr);
	i2c_write(Read_reg);
	i2c_rep_start(Sensor_addr+1);
	for (int i = 0 ; i < arr_length; i++ )
	{
		data[i] = i2c_readAck();
	}
	i2c_readNak();
	
	//Result =(Result<<8) + i2c_readNak();
	i2c_stop();
	
	
	return;
}

/*void Clk_bcd_conv(uint8_t data[], uint8_t arr_length)
{
	for(int i = 0; i < arr_length ; i++)
	{
		switch(i)
		{
			case 0:
				data[0] = Seconds_bcd()
			break;
			
			case 1:
			
			break;
			
			case 2:
			
			break;
			
			case 3:
			
			break;
			
			case 4:
			
			break;
			
			case 5:
			
			break;
			
			case 6:
			
			break;
		}
	}
}
*/

uint8_t Seconds_bcd(uint8_t *Seconds)
{
	uint8_t Sec_temp = 0;
	uint8_t BCD = 0;
	Sec_temp = *Seconds;
	
	while(Sec_temp >= 64)
	{
		BCD = BCD + 40;
		Sec_temp = Sec_temp -64;
	}
	while(Sec_temp >= 32)
	{
		BCD = BCD + 20;
		Sec_temp = Sec_temp - 32;
	}
	while(Sec_temp >= 16)
	{
		BCD = BCD + 10;
		Sec_temp = Sec_temp - 16;
	}
	
	BCD = BCD + Sec_temp;
	return BCD;
}

uint8_t Minutes_bcd(uint8_t *Minutes)
{
	uint8_t Min_temp = 0;
	uint8_t BCD = 0;
	Min_temp = *Minutes;
	
	while(Min_temp >= 64)
	{
		BCD = BCD + 40;
		Min_temp = Min_temp -64;
	}
	while(Min_temp >= 32)
	{
		BCD = BCD + 20;
		Min_temp = Min_temp - 32;
	}
	while(Min_temp >= 16)
	{
		BCD = BCD + 10;
		Min_temp = Min_temp - 16;
	}
	
	BCD = BCD + Min_temp;
	return BCD;
}



uint8_t Hours_bcd(uint8_t *Hours)
{
	uint8_t Hour_temp = 0;
	uint8_t BCD = 0;
	Hour_temp = *Hours;
	
	while(Hour_temp >= 32)
	{
		BCD = BCD + 20;
		Hour_temp = Hour_temp -32;
	}
	while(Hour_temp >= 16)
	{
		BCD = BCD + 10;
		Hour_temp = Hour_temp - 16;
	}
	
	BCD = BCD + Hour_temp;
	return BCD;
}


uint8_t Date_bcd(uint8_t *Date)
{
	uint8_t Date_temp = 0;
	uint8_t BCD = 0;
	Date_temp = *Date;
	
	while(Date_temp >= 32)
	{
		BCD = BCD + 20;
		Date_temp = Date_temp -32;
	}
	while(Date_temp >= 16)
	{
		BCD = BCD + 10;
		Date_temp = Date_temp - 16;
	}
	
	BCD = BCD + Date_temp;
	return BCD;
}

uint8_t Month_bcd(uint8_t *Months)
{
	uint8_t Month_temp = 0;
	uint8_t BCD = 0;
	Month_temp = *Months;
	
	while(Month_temp >= 16)
	{
		BCD = BCD + 10;
		Month_temp = Month_temp -16;
	}	
	BCD = BCD + Month_temp;
	return BCD;
}

uint8_t Years_bcd(uint8_t *Years)
{
	uint8_t Year_temp = 0;
	uint8_t BCD = 0;
	Year_temp = *Years;
	while(Year_temp >= 128)
	{
		BCD = BCD + 80;
		Year_temp = Year_temp - 128;
	}
	while(Year_temp >= 64)
	{
		BCD = BCD + 40;
		Year_temp = Year_temp -64;
	}
	while(Year_temp >= 32)
	{
		BCD = BCD + 20;
		Year_temp = Year_temp - 32;
	}
	while(Year_temp >= 16)
	{
		BCD = BCD + 10;
		Year_temp = Year_temp - 16;
	}
	
	BCD = BCD + Year_temp;
	return BCD;
}
