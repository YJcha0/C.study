#ifndef SQQUEUE_H_INCLUDED
#define SQQUEUE_H_INCLUDED
#include <stdio.h>
#include <malloc.h>
#define ElemType char
#define MaxSize 30
typedef struct
{
    ElemType data[MaxSize];
    int front,count;
} QuType;
void InitQueue(QuType *&q);
void DestroyQueue(QuType *&q);
bool QueueEmpty(QuType *q);
bool EnQueue(QuType *&q,ElemType e);
bool DeQueue(QuType *&q,ElemType &e);

#endif // SQQUEUE_H_INCLUDED
