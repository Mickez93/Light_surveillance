/*
 * Ext_int.h
 *
 * Created: 2022-11-18 10:14:18
 *  Author: mini0072
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_
//Initierar interrupt på falling edge pinne int2
void Eint2_init(void);
//Initierar interrupt på falling edge pinne int1
void Eint1_init(void);
//Initierar interrupt på falling edge pinne int0
void Eint0_init(void);




#endif /* EXT_INT_H_ */