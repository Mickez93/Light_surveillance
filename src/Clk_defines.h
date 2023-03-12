/*
 * Clk_defines.h
 *
 * Created: 2022-11-17 11:45:39
 *  Author: mini0072
 */ 


#ifndef CLK_DEFINES_H_
#define CLK_DEFINES_H_
//KLOCKDEFINES
//KLOCKREGISTER
#define Clock_conf_reg 0x0E
#define Clk_init_config 0b10000101
//Klockregister börjar på 0
#define Time_keeping_reg 0x00
//Tidsregister defines
#define Seconds_init_vlu 0b00000000
#define Minutes_init_vlu 0b00100100
//Timregister sätts till 24timmars-läge och startas som 12:00
#define Hours_init_vlu 0b00010110
//Dagregister sätts som standard till 4 torsdag
#define Days_init_vlu 0b00000100
//Datum sätts som 17:e
#define Date_init_vlu 0b00011000
//Månad sätts som standard till 11
#define Months_init_vlu 0b00010001
//
#define Year_init_vlu 0b00100010
//STATUS REG
#define Status_reg_addr 0x0F
#define Alarm_off 0b00000000;


#endif /* CLK_DEFINES_H_ */