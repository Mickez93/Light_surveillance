/*
 * Clk_alarm.c
 *
 * Created: 2022-11-18 14:32:12
 *  Author: mini0072
 */ 
#include "Clk_i2c_rw.h"
#include "Clk_defines.h"

void Clk_enable_alarm(uint8_t Sensor_addr)
{
	Clk_write_ctrl(Sensor_addr,0x08,0b10000000);
	Clk_write_ctrl(Sensor_addr,0x09,0b10000000);
	Clk_write_ctrl(Sensor_addr,0x0A,0b10000000);
	
}

void Clk_clear_alarm(uint8_t Sensor_addr)
{
	Clk_write_ctrl(Sensor_addr,Status_reg_addr,0b00000000);
}