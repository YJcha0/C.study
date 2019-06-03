#include "sqqueue.h"

void InitQueue(QuType *&qu)
{
    qu=(QuType *)malloc(sizeof(QuType));
    qu->front=0;
    qu->count=0;
}

void DestroyQueue(QuType *&q)
{
    free(q);
}

bool QueueEmpty(QuType *q)
{
    return(q->count==0);
}

bool EnQueue(QuType *&qu,ElemType x)
{
    int rear;
    if(qu->count==MaxSize)
        return false;
    else
    {
        rear=(qu->front+qu->count)%MaxSize;
        rear=(rear+1)%MaxSize;
        qu->data[rear]=x;
        qu->count++;
        return true;
    }
}

bool DeQueue(QuType *&qu,ElemType &x)
{
    if(qu->count==0)
        return false;
    else
    {
        qu->front=(qu->front+1)%MaxSize;
        x=qu->data[qu->front];
        qu->count--;
        return true;
    }
}
