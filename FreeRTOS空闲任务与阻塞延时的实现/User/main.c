#include "FreeRTOS.h"
#include "task.h"




extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];
portCHAR flag1;
portCHAR flag2;

#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];

//创建任务句柄
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;

//创建任务控制块
TCB_t Task1TCB;
TCB_t Task2TCB;
//创建空闲任务控制块
TCB_t IdleTaskTCB;
//定义空闲任务栈
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];


void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

/* 软件延时 */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}


/* 任务1 */
void Task1_Entry( void *p_arg )
{
	for( ;; )
	{
		flag1 = 1;
		vTaskDelay( 2 );		
		flag1 = 0;
		vTaskDelay( 2 );
	}
}


/* 任务2 */
void Task2_Entry( void *p_arg )
{
	for( ;; )
	{
		flag2 = 1;
		vTaskDelay( 2 );	//该延时为10ms这里设置为20ms	
		flag2 = 0;
		vTaskDelay( 2 );
	}
}


int main(void)
{
	prvInitialiseTaskLists();
	
	//创建任务
	Task1_Handle=xTaskCreateStatic(Task1_Entry,"Task1",TASK1_STACK_SIZE,NULL,Task1Stack,&Task1TCB);
	Task2_Handle=xTaskCreateStatic(Task2_Entry,"Task2",TASK2_STACK_SIZE,NULL,Task2Stack,&Task2TCB);
	
	//将任务节点添加到对应的任务就绪列表的对应根节点中
	vListInsertEnd( &( pxReadyTasksLists[1] ), &( ((TCB_t *)(&Task1TCB))->xStateListItem ) );
	vListInsertEnd( &( pxReadyTasksLists[2] ), &( ((TCB_t *)(&Task2TCB))->xStateListItem ) );
	
//	vListInsertEnd(&(pxReadyTasksLists[1]),&(Task1TCB.xStateListItem));
//	vListInsertEnd(&(pxReadyTasksLists[2]),&(Task2TCB.xStateListItem));
	
	/* 启动调度器，开始多任务调度，启动成功则不返回 */
   vTaskStartScheduler(); 
	for(;;)
	{}
}
