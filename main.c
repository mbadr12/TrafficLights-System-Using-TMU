/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  APP				    *************************/
/*************************		Project: Traffic Lights		*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TMU_Interface.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
void RED_LED(void* Copy_Ptr);
void GREEN_LED(void* Copy_Ptr);
void YELLOW_LED(void* Copy_Ptr);
void SEV_SEG(void* Copy_Ptr);
void Switch1(void* Copy_Ptr);
void Switch2(void* Copy_Ptr);

typedef struct
{
	u8 Counter1;
	u8 Counter2;
	u8 Last_state;
	u8 Yellow_State;
	u8 MaxTime;
}Traffic_Par_t;
int main(void)
{
	Traffic_Par_t traffic={1,5,0,0,15};
	TMU_TaskParmeters Red_LED={100,2,RED_LED,&(traffic.Last_state),0};
	TMU_TaskParmeters Yellow_LED={100,3,YELLOW_LED,&(traffic.Yellow_State),0};
	TMU_TaskParmeters Green_LED={100,1,GREEN_LED,&(traffic.Last_state),0};
	TMU_TaskParmeters SSD_Dispaly={100,0,SEV_SEG,&traffic,0};
	TMU_TaskParmeters Plus_Switch={15,4,Switch1,&(traffic.MaxTime),150};
	TMU_TaskParmeters Minus_Switch={15,5,Switch2,&(traffic.MaxTime),150};
	PORT_voidInit();
	TMU_CreateTask(&Red_LED);
	TMU_CreateTask(&Yellow_LED);
	TMU_CreateTask(&Green_LED);
	TMU_CreateTask(&SSD_Dispaly);
	TMU_CreateTask(&Plus_Switch);
	TMU_CreateTask(&Minus_Switch);
	TMU_Start();
	while(1);
}

void RED_LED(void* Copy_Ptr)
{
	if((*((u8*)Copy_Ptr)) == 1)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8Pin_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8Pin_LOW);
	}
}
void YELLOW_LED(void* Copy_Ptr)
{
	if((*((u8*)Copy_Ptr)) == 1)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8Pin_HIGH);
	}
	if((*((u8*)Copy_Ptr))==0)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8Pin_LOW);
	}
}
void GREEN_LED(void* Copy_Ptr)
{
	if((*((u8*)Copy_Ptr)) == 0)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8Pin_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN2,DIO_u8Pin_LOW);
	}
}
void SEV_SEG(void* Copy_Ptr)
{
	Traffic_Par_t* ptr= (Traffic_Par_t*)Copy_Ptr;
	if((ptr->Counter1==0) && (ptr->Counter2==3))
	{
		ptr->Yellow_State=1;
	}
	else if((ptr->Counter1==(ptr->MaxTime/10)) && (ptr->Counter2==(ptr->MaxTime%10)))
	{
		ptr->Yellow_State=0;
		TOGGLE_BIT(ptr->Last_state,0);
	}
	DIO_u8SetPortValue(DIO_u8PORTC, (ptr->Counter1 | (ptr->Counter2<<4)));
	if((ptr->Counter1>0) && (ptr->Counter2==0))
	{
		ptr->Counter2=10;
		ptr->Counter1--;
	}
	if((ptr->Counter1==0) && (ptr->Counter2==1))
	{
		ptr->Counter1=ptr->MaxTime/10;
		ptr->Counter2=(ptr->MaxTime%10)+1;
	}
	ptr->Counter2--;
}
void Switch1(void* Copy_Ptr)
{
	u8 ButtonState=0;
	DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&ButtonState);
	if(ButtonState==0)
	{
		if((*((u8*)Copy_Ptr))<99)
		{
			(*((u8*)Copy_Ptr))++;
		}
	}
}
void Switch2(void*Copy_Ptr)
{
	u8 ButtonState=0;
	DIO_u8GetPinValue(DIO_u8PORTA,DIO_u8PIN4,&ButtonState);
	if(ButtonState==0)
	{
		if((*((u8*)Copy_Ptr))>3)
		{
			(*((u8*)Copy_Ptr))--;
		}
	}
}
