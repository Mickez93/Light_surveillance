/*
 * Clk_i2c_rw.h
 *
 * Created: 2022-11-17 13:56:10
 *  Author: mini0072
 */ 
#include <inttypes.h>

#ifndef CLK_I2C_RW_H_
#define CLK_I2C_RW_H_


//Write till kontroll-register klocka
void Clk_write_ctrl(uint8_t Sensor_addr, uint8_t Reg_addr, uint8_t Command);
//Skriver det antal bytes som skickas in till dataregister
void Clk_write_data(uint8_t Sensor_addr, uint8_t Reg_addr, uint8_t data[], uint8_t arr_length);
//Läser
void Clk_read_data(uint8_t Sensor_addr, uint8_t Read_reg, uint8_t data[], uint8_t arr_length);

//void Clk_bcd_conv(uint8_t data[], uint8_t arr_length);
uint8_t Seconds_bcd(uint8_t *Seconds);
uint8_t Minutes_bcd(uint8_t *Minutes);
uint8_t Hours_bcd(uint8_t *Hours);
uint8_t Date_bcd(uint8_t *Date);
uint8_t Month_bcd(uint8_t *Months);
uint8_t Years_bcd(uint8_t *Years);




#endif /* CLK_I2C_RW_H_ */