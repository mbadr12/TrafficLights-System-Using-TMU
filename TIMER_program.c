/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  MCAL			    *************************/
/*************************		SWC: 	TIMER 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"

static void (*TIMERS_pvCallBackFunc[4]) (void)={NULL};

void TIMER0_voidInit(void)
{
	SET_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);
	/*Output Compare Match Interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);
	/*Compare match output mode*/
	TCCR0&=COMP_OPMODE_MASK;
	TCCR0|=TIMER0_COMPARE_OUTPUT_MODE;
	SET_BIT(TIMSK,TIMSK_OCIE0);
	/*Prescaler*/
	TCCR0&=TIMER_PRESCALER_MASK;
	TCCR0|=TIMER0_PRESCALER;
}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMERS_pvCallBackFunc[1]!=NULL)
	{
		TIMERS_pvCallBackFunc[1]();
	}
}

void TIMER1_voidInit(void)
{
	/*Choose Waveform Generation Mode*/
	TCCR1A&=TIMER1_WAVE_MODE_MASK_TCCR1A;
	TCCR1B&=TIMER1_WAVE_MODE_MASK_TCCR1B;
	TCCR1A|=(TIMER1_GENERATION_MODE&TIMER1_WGM10_WGM11_MASK);
	TCCR1B|=((TIMER1_GENERATION_MODE&TIMER1_WGM12_WGM13_MASK)<<1);
	/*Compare Output Mode for Channel A*/
	TCCR1A&=COMP_OPMODE_CHANA_MASK;
	TCCR1A|=(TIMER1_COMPARE_OUTPUT_MODE<<TCCR1A_COM1A0);
	SET_BIT(TIMSK,TIMSK_OCIE1A);
	/*Prescaler*/
	TCCR1B&=TIMER_PRESCALER_MASK;
	TCCR1B|=TIMER1_PRESCALER;
}

void TIMER1_voidSetChannelACompMatchValue(u16 Copy_u16Value)
{
	OCR1A=Copy_u16Value;
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if(TIMERS_pvCallBackFunc[2]!=NULL)
	{
		TIMERS_pvCallBackFunc[2]();
	}
}

void TIMER2_voidInit(void)
{
	/*choose Wave Generation Mode*/
	SET_BIT(TCCR2,TCCR2_WGM21);
	CLR_BIT(TCCR2,TCCR2_WGM20);
	/*Output Compare Match Interrupt Enable*/
	SET_BIT(TIMSK,TIMSK_OCIE2);
	/*Compare match output mode*/
	TCCR2&=COMP_OPMODE_MASK;
	TCCR2|=TIMER2_COMPARE_OUTPUT_MODE;
	/*Prescaler*/
	TCCR2&=TIMER_PRESCALER_MASK;
	TCCR2|=7;
}

void TIMER2_voidSetCompMatchValue(u8 Copy_u8Value)
{
	OCR2=Copy_u8Value;
}

void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if(TIMERS_pvCallBackFunc[3]!=NULL)
	{
		TIMERS_pvCallBackFunc[3]();
	}
}

u8 TIMER_u8SetCallBack(void (* Copy_pvCallBackFunc) (void),u8 Copy_u8ChannelID)
{
	u8 Local_u8ErrorStatus=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		/*pass The pointer to local function to global pointer to function to be called in ISR*/
		TIMERS_pvCallBackFunc[Copy_u8ChannelID]=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}
