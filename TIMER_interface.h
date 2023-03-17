/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	TIMER 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/
#ifndef COTS_1_MCAL_6__TIMER_TIMER_INTERFACE_H_
#define COTS_1_MCAL_6__TIMER_TIMER_INTERFACE_H_

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

#define OVERFLOW_INT 		0
#define CTC_INT				1
#define ICU_INT				2

#define TIMER0_COMP_INT		1
#define TIMER1_COMPA_INT	2
#define TIMER2_COMP_INT		3


void TIMER0_voidInit(void);

void TIMER1_voidInit(void);

void TIMER2_voidInit(void);

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value);

void TIMER1_voidSetChannelACompMatchValue(u16 Copy_u16Value);

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value);

u8 TIMER_u8SetCallBack(void (* Copy_pvCallBackFunc) (void),u8 Copy_u8ChannelID);

#endif /* COTS_1_MCAL_6__TIMER_TIMER_INTERFACE_H_ */
