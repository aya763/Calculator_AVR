/*
 * KPD_config.h
 *
 *  Created on: Aug 18, 2023
 *      Author: aya
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT  DIO_u8PORTD

/*ALL KEYPAD PINS IN SAME PORT MAKE  KPD_SAMEPORT=1,
 ELSE KPD_SAMEPORT=0
 */
#define KPD_SAMEPORT  1

#define KPD_COLUM0_PORT  DIO_u8PORTD
#define KPD_COLUM1_PORT  DIO_u8PORTD
#define KPD_COLUM2_PORT  DIO_u8PORTD
#define KPD_COLUM3_PORT  DIO_u8PORTD

#define KPD_COLUM0_PIN  DIO_u8PIN0
#define KPD_COLUM1_PIN  DIO_u8PIN1
#define KPD_COLUM2_PIN  DIO_u8PIN2
#define KPD_COLUM3_PIN  DIO_u8PIN3

#define KPD_ROW0_PORT    DIO_u8PORTD
#define KPD_ROW1_PORT    DIO_u8PORTD
#define KPD_ROW2_PORT    DIO_u8PORTD
#define KPD_ROW3_PORT    DIO_u8PORTD


#define KPD_ROW0_PIN    DIO_u8PIN4
#define KPD_ROW1_PIN    DIO_u8PIN5
#define KPD_ROW2_PIN    DIO_u8PIN6
#define KPD_ROW3_PIN    DIO_u8PIN7


#define KPD_NO_PRESSED_KEY  0xff

//#define KPD_ARR_VAL {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}
#define KPD_ARR_VAL {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}}
//#define KPD_ARR_VAL {{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'c',0,'=','+'}}

#endif /* KPD_CONFIG_H_ */
