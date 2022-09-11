#ifndef PROJDEFS_H
#define PROJDEFS_H
//TaskFunction_t不是一个函数指针了，它代表着一种类型，这种类型可以定义一个指向返回值为void，参数为void *类型的指针
typedef void (*TaskFunction_t)( void * );//

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )


#endif /* PROJDEFS_H */

