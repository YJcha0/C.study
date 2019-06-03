#include "sqqueue.h"

int main()
{
    char c;
    int i;
    QuType *q;
    printf("队列初始化。。。");
    InitQueue(q);
    printf("。。。完成！\n");
    char s[6]= {'a','b','c','d','e','f'};
    for(i=0; i<6; i++)
        EnQueue(q,s[i]);
    if(QueueEmpty(q))
        printf("队列为空！\n");
    else
        printf("队列非空！\n");
    DeQueue(q,c);
    putchar(c);
    printf("队列中元素个数为：%d\n",q->count);
    printf("请输入3字符：");
    for(i=0; i<3; i++)
    {
        scanf("%c",&c);
        EnQueue(q,c);
    }
    printf("队列中元素个数为：%d\n",q->count);
    while(q->count==0)
    {
        DeQueue(q,c);
        putchar(c);
    }
    DestroyQueue(q);
    return 0;
}
