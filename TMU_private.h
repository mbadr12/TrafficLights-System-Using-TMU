/************************************************************************************/
/************************************************************************************/
/*************************		Author: Mahmoud Badr		*************************/
/*************************		Layer:  Service			    *************************/
/*************************		SWC: 	TMU 				*************************/
/*************************		Version:1.00				*************************/
/************************************************************************************/
/************************************************************************************/

#ifndef TMU_PRIVATE_H_
#define TMU_PRIVATE_H_

typedef struct
{
	void(*TaskFunc)(void*);
	void *PrameterPtr;
	u16 Periodicity;
	u16 FirstDelay;
	u8 State;
}TCB_t;

#define CH0	1
#define CH1	2
#define CH2	3

#define SUSPENDED	0

#define RESUMED		1

static void TMU_Scheduler(void);

u8 TMU_GCM(u16 Greater_Num , u8 Less_Num);

#endif /* TMU_PRIVATE_H_ */
