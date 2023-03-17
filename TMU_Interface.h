/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  Service			    *************************/
/*************************		SWC: 	TMU 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#ifndef TMU_INTERFACE_H_
#define TMU_INTERFACE_H_

typedef struct
{
	u16 Periodicity;
	u8 Priority;
	void(*TaskFunc)(void);
	void* Parameter;
	u16 FirstDelay;
}TMU_TaskParmeters;

void TMU_Start(void);

u8 TMU_CreateTask(TMU_TaskParmeters* Copy_TaskPar);

void TMU_SuspendTask(u8 Copy_Priority);

void TMU_ResumeTask(u8 Copy_Priority);

void TMU_DeleteTask(u8 Copy_Priority);

#endif /* TMU_INTERFACE_H_ */
