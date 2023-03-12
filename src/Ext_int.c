/*
 * Ext_int.c
 *
 * Created: 2022-11-18 10:14:05
 *  Author: mini0072 
 */
 
 
#include <avr/io.h> 


void Eint2_init(void)
{
	//INTERRUPT ENABLAS PÅ PINNE INT2
	EIMSK = EIMSK | (1<<INT2);
	//FALLING EDGE INTERRUPT
	EICRA = EICRA | (1<<ISC21);
}

void Eint1_init(void)
{
	//INTERRUPT ENABLAS PÅ PINNE INT2
	EIMSK = EIMSK | (1<<INT1);
	//FALLING EDGE INTERRUPT
	EICRA = EICRA | (1<<ISC11);
}

void Eint0_init(void)
{
	//INTERRUPT ENABLAS PÅ PINNE INT2
	EIMSK = EIMSK | (1<<INT0);
	//FALLING EDGE INTERRUPT
	EICRA = EICRA | (1<<ISC01);
}