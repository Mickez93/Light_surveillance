/*
 * RW_i2c.h
 *
 * Created: 2022-11-15 10:05:35
 *  Author: mini0072
 */ 


#ifndef RW_I2C_H_
#define RW_I2C_H_

uint8_t Scan_i2c_bus(uint8_t* active_address1, uint8_t* active_address2, uint8_t* active_address3);
void Sensor_write(uint8_t Sensor_addr, uint8_t Reg_addr, uint8_t Command_high, uint8_t Command_low);
uint16_t Sensor_read(uint8_t Sensor_addr, uint8_t Read_reg);
//SKRIVER 2 BYTES
void E2PROM_write(uint8_t Sensor_addr, volatile uint16_t *Mem_addr, uint8_t *data, uint8_t arr_length);
//LÄSER 2 BYTES
void E2PROM_read(uint8_t Sensor_addr, uint16_t Mem_addr,volatile uint8_t *data, uint8_t arr_length);




#endif /* RW_I2C_H_ */