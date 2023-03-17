/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  Service			    *************************/
/*************************		SWC: 	TMU 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "TMU_Interface.h"
#include "TMU_private.h"
#include "TMU_Config.h"

static u8 TMU_CompCount=0;
static u8 TMU_ISRNum=0;
static u8 TMU_Flag=0;

static TCB_t TMU_SystemTasks[TASK_NUM]={{NULL}};
void TMU_Start(void)
{
	u16 Local_OCRValue;
	u8 Local_Max=0;
	u8 Local_Index=0;
#if TIM_CH == CH0
	TIMER0_voidInit();
#if OS_TICK > 0 && OS_TICK <= 32
	Local_OCRValue=(F_CPU*OS_TICK)/(1024000UL);
	TMU_CompCount=1;
	TMU_ISRNum=1;
#elif OS_TICK > 32 && OS_TICK < 4000
	Local_Max=TMU_GCM(OS_TICK,32);
	Local_OCRValue=(F_CPU*Local_Max)/(1024000UL);
	TMU_CompCount=OS_TICK/Local_Max;
	TMU_ISRNum=OS_TICK/Local_Max;
#else
#error "You Exceeded the Limit of OS_Tick"
#endif
	TIMER0_voidSetCompMatchValue(Local_OCRValue);
#elif TIM_CH == CH1
	TIMER1_voidInit();
#if OS_TICK > 0 && OS_TICK <= 4000
	Local_OCRValue=(u32)(F_CPU*OS_TICK)/(1024000UL);
	TIMER1_voidSetChannelACompMatchValue(Local_OCRValue);
	TMU_CompCount=1;
	TMU_ISRNum=1;
#else
#error "You Exceeded the Limit of OS_Tick"
#endif
#elif TIM_CH ==CH2
	TIMER2_voidInit();
#if OS_TICK > 0 && OS_TICK <= 32
	Local_OCRValue=(F_CPU*OS_TICK)/(1024000UL);
	TMU_CompCount=1;
	TMU_ISRNum=1;
#elif OS_TICK > 32 && OS_TICK < 4000
	Local_Max=TMU_GCM(OS_TICK,32);
	Local_OCRValue=(F_CPU*Local_Max)/(1024000UL);
	TMU_CompCount=OS_TICK/Local_Max;
	TMU_ISRNum=OS_TICK/Local_Max;
#else
#error "You Exceeded the Limit of OS_Tick"
#endif
	TIMER2_voidSetCompMatchValue(Local_OCRValue);
#endif
	TIMER_u8SetCallBack(TMU_Scheduler,TIM_CH);
	GIE_voidEnable();
	while(1)
	{
		if(TMU_Flag == 1)
		{
			TMU_Flag=0;
			for(Local_Index=0;Local_Index<TASK_NUM;Local_Index++)
			{
				if(TMU_SystemTasks[Local_Index].State == RESUMED)
				{
					if(TMU_SystemTasks[Local_Index].FirstDelay == 0)
					{
						if(TMU_SystemTasks[Local_Index].TaskFunc != NULL)
						{
							TMU_SystemTasks[Local_Index].TaskFunc(TMU_SystemTasks[Local_Index].PrameterPtr);
							(TMU_SystemTasks[Local_Index].FirstDelay) = (TMU_SystemTasks[Local_Index].Periodicity)-1;
						}
					}
					else
					{
						TMU_SystemTasks[Local_Index].FirstDelay--;
					}
				}
			}
		}
	}
}

u8 TMU_CreateTask(TMU_TaskParmeters* Copy_TaskPar)
{
	u8 Local_ErrorState=OK;
	if(Copy_TaskPar == NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else if(Copy_TaskPar->Priority >= TASK_NUM)
	{
		Local_ErrorState=NOK;
	}
	else if(TMU_SystemTasks[Copy_TaskPar->Priority].TaskFunc == NULL)
	{
		TMU_SystemTasks[Copy_TaskPar->Priority].Periodicity=Copy_TaskPar->Periodicity;
		TMU_SystemTasks[Copy_TaskPar->Priority].PrameterPtr=Copy_TaskPar->Parameter;
		TMU_SystemTasks[Copy_TaskPar->Priority].TaskFunc=Copy_TaskPar->TaskFunc;
		TMU_SystemTasks[Copy_TaskPar->Priority].State=RESUMED;
		TMU_SystemTasks[Copy_TaskPar->Priority].FirstDelay=Copy_TaskPar->FirstDelay;
	}
	return Local_ErrorState;
}

void TMU_SuspendTask(u8 Copy_Priority)
{
	if(Copy_Priority < TASK_NUM)
	{
		TMU_SystemTasks[Copy_Priority].State=SUSPENDED;
	}
}

void TMU_ResumeTask(u8 Copy_Priority)
{
	if(Copy_Priority < TASK_NUM)
	{
		TMU_SystemTasks[Copy_Priority].State=RESUMED;
	}
}

void TMU_DeleteTask(u8 Copy_Priority)
{
	{
		TMU_SystemTasks[Copy_Priority].TaskFunc=NULL;
	}
}

static void TMU_Scheduler(void)
{
	TMU_CompCount--;
	if(TMU_CompCount == 0)
	{
		TMU_CompCount=TMU_ISRNum;
		TMU_Flag=1;
	}
}

u8 TMU_GCM(u16 Greater_Num , u8 Less_Num)
{
	u8 Common=Less_Num;
	while(Greater_Num%Common !=0)
	{
		Common--;
	}
	return Common;
}
