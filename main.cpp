#include "sqqueue.h"

int main()
{
    char c;
    int i;
    QuType *q;
    printf("���г�ʼ��������");
    InitQueue(q);
    printf("��������ɣ�\n");
    char s[6]= {'a','b','c','d','e','f'};
    for(i=0; i<6; i++)
        EnQueue(q,s[i]);
    if(QueueEmpty(q))
        printf("����Ϊ�գ�\n");
    else
        printf("���зǿգ�\n");
    DeQueue(q,c);
    putchar(c);
    printf("������Ԫ�ظ���Ϊ��%d\n",q->count);
    printf("������3�ַ���");
    for(i=0; i<3; i++)
    {
        scanf("%c",&c);
        EnQueue(q,c);
    }
    printf("������Ԫ�ظ���Ϊ��%d\n",q->count);
    while(q->count==0)
    {
        DeQueue(q,c);
        putchar(c);
    }
    DestroyQueue(q);
    return 0;
}
