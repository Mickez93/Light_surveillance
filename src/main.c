/*
 * Labb4_upp1.c
 *
 * Created: 2022-11-14 17:14:46
 * Author : mini0072
 */ 
///SYSTEMET LOGGAR DATA I 3 DAGAR OCH BÖRJAR SEDAN OM MED ATT LOGGA PÅ MINNESADRESS NOLL IGEN

#define F_CPU 1000000UL
#define FLIP_BIT(ADDR,BIT) (ADDR ^= (1<<BIT))
//LUXREGISTER
#define Result_register 0x00
#define Config_register 0x01
#define LL_reg 0x02
//AUTO FULL SCALE 800ms conversion 
//LUXDEFINES
#define HStart_config 0b11000110
#define LStart_config 0b00000000
#define HEOCmode 0b11000000
#define LEOCmode 0b00000000


#define Mem_max 864

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "RW_i2c.h"
#include "i2cmaster.h"
#include <inttypes.h>
#include "Calc_lux.h"
#include <avr/eeprom.h>
#include "Clk_defines.h"
#include "Clk_i2c_rw.h"
#include <avr/interrupt.h>
#include "Ext_int.h"
#include "Clk_alarm.h"

//MINNESVARIABLER
volatile uint16_t EPRM_cu_adr = 0;
//EEPROM
uint8_t active_adr2 = 1;
//KLOCKA
uint8_t active_adr3 = 1;
volatile uint8_t eeprom_results[8];
//KNAPPFLAGGA FÖR EXTRA MÄTNING
volatile uint8_t Extra_meas_flg = 0;
volatile uint8_t Timer_count = 4;
volatile uint8_t Timer_meas_flg = 0;







///UART PRINTF

void UART_init(void);
static int UART_putchar(char tecken, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(UART_putchar,NULL,_FDEV_SETUP_WRITE);
static int UART_putchar(char tecken, FILE *stream)
{
	
	while(!(UCSR0A & (1<<UDRE0)) )
	{
		
		
		PORTC = 0;
	}
	
	UDR0 = tecken;
	return 0;
}


///////////////////////////////////////
int main(void)
{
	
	
	//PORT INIT
	//INGÅNG OCH PULLUP FÖR INT2
	DDRB = DDRB & 0b11111011;
	PORTB = PORTB | 0b00000100;
	////
	DDRD = 0b11110011;
	PORTD = PORTD | 0b00001100;
	DDRC = 0xFF;
	PORTC = 0;
	//VARIABELDEKLARATIONER
	//LUXSENSOR
	uint8_t active_adr1 = 1;
	//RÅDATA FRÅN LUXMÄTARE
	uint16_t result = 0;
	//I2C SCAN ANTAL SENSORER HITTADE
	uint8_t number_of_sensors = 0;
	//FLOATAR
	//RESULTAT LSB från LUXMÄTNING
	float LSB = 0;
	//TOTAL LUXRESULTAT
	uint16_t Lux_result = 0;
	//Klockarrayer
	uint8_t clk_init_data[] = {Seconds_init_vlu,Minutes_init_vlu,Hours_init_vlu,Days_init_vlu,Date_init_vlu,Months_init_vlu,Year_init_vlu};
	//Inläsning från klocka
	uint8_t clk_time_data[7]; 
	//Array för skrivning till EEPROM
	uint8_t eeprom_data[8];
	
	
	
	/////////////////////
	
	
	stdout = &mystdout;
	//Kommunikationsinit
	UART_init();
	i2c_init();
	Eint2_init();
	Eint1_init();
	Eint0_init();
	
	
	//LÄS IN AKTIVA i2c adresser
	number_of_sensors = Scan_i2c_bus(&active_adr1,&active_adr2,&active_adr3);
	
	if(number_of_sensors == 0)
	{
		printf("FEL");
	}
	else
	{
		printf(" Adress1 %d ", active_adr1);
		printf(" Adress2 - %d ", active_adr2);
		printf(" Adress3 - %d ", active_adr3);
	}
	
	/////INIT LUX-SENSOR////////KONTINUERLIGA MÄTNINGAR////
	
	Sensor_write(active_adr1,Config_register,HStart_config,LStart_config);
	//Interrupt mode används ej
	//Sensor_write(active_adr,LL_reg,HEOCmode,LEOCmode);
	//printf("TX compl");
	_delay_ms(2000);
	result = Sensor_read(active_adr1,Result_register);
	///INIT KLOCKA
	Clk_write_ctrl(active_adr3,Clock_conf_reg,Clk_init_config);
	Clk_write_data(active_adr3,Time_keeping_reg,clk_init_data,7);
	Clk_enable_alarm(active_adr3);
	
	sei();
	//////MAIN LOOP
	while (1)
	{	
		
		
		//LJUSSENSOR-MÄTNING och klockläsning och sedan EEPROM-skrivning
		if((EPRM_cu_adr < 0xFFFF && (Extra_meas_flg || Timer_meas_flg)))
		{	
			
			//LJUSSENSOR
			cli();
			result = Sensor_read(active_adr1,0);
			LSB = LSB_calc(result);
			Lux_result = Calc_lux(result,LSB);
			eeprom_data[0] = (Lux_result>>8);
			eeprom_data[1] = Lux_result & 0b0000000011111111;
			//printf(" Lux = %d High %d Low %d ",Lux_result, eeprom_data[0], eeprom_data[1]);
			//Läs data lägg i array
			Clk_read_data(active_adr3,Time_keeping_reg,clk_time_data,7);
			//Översätt data i arrayen till BCD-siffror
			eeprom_data[2] = Seconds_bcd(&clk_time_data[0]);
			eeprom_data[3] = Minutes_bcd(&clk_time_data[1]);
			eeprom_data[4] = Hours_bcd(&clk_time_data[2]);
			eeprom_data[5] = Date_bcd(&clk_time_data[4]);
			eeprom_data[6] = Month_bcd(&clk_time_data[5]);
			eeprom_data[7] = Years_bcd(&clk_time_data[6]);
			//printf("Year %d Month %d Day %d H %d M %d S %d ",eeprom_data[7], eeprom_data[6],eeprom_data[5], eeprom_data[4], eeprom_data[3], eeprom_data[2]);
			E2PROM_write(active_adr2,&EPRM_cu_adr,eeprom_data,8);
			sei();
			if(Timer_meas_flg == 1)
			{
				Timer_meas_flg = 0;
			}
			else if(Extra_meas_flg == 1)
			{
				Extra_meas_flg = 0;
			}
			
	
			
		}
		//RESETTA OM MINNET BLIR FULLT
		else if(EPRM_cu_adr >= 0xFFFF)
		{
			EPRM_cu_adr = 0;
		}
	}
}

//UART INIT

void UART_init(void)
{
	UBRR0 = 12; //Baud 4800
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
	
}


ISR(INT2_vect)
{	
	
	for(int i = 0 ; i < EPRM_cu_adr ; i = i + 8)
	{	
		uint16_t Lux_16bit = 0;
		E2PROM_read(active_adr2,i,eeprom_results,8);
		Lux_16bit = (eeprom_results[0]<<8) + eeprom_results[1];
		printf("%d-%d-%d , %02d:%02d:%02d , %d\r", eeprom_results[7], eeprom_results[6], eeprom_results[5], eeprom_results[4], eeprom_results[3], eeprom_results[2], Lux_16bit );
	}
}

ISR(INT1_vect)
{
	Extra_meas_flg = 1;
}

ISR(INT0_vect)
{
	Timer_count++;
	if(Timer_count >= 5)
	{
		Timer_meas_flg = 1;
		Timer_count = 0;
	}
	Clk_clear_alarm(active_adr3);

}





//////////////////