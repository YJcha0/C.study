#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NAME_NUMBER 10         /*����������󳤶�*/
#define ID_NUMBER 9            /*����ѧ�ų���*/
#define SEX_NUMBER 3           /*�����Ա𳤶�*/
#define SCORE_NUMBER 3         /*����ɼ���������ʱλ3��*/
#define MAX_STUDENT_NUMBER 100 /*�������ѧ����*/

int student_number = 0; /*��¼��ʱ�Ѿ������ѧ������*/

struct student
{
    char name[NAME_NUMBER];
    char id[ID_NUMBER];
    char sex[SEX_NUMBER];
    float score[SCORE_NUMBER];
    float averageSCore;
};
typedef struct student STUDENT;

/*  �������ܣ�	��ʼ���ṹ�����飬���ļ��е���Ϣ�������飬����student_number����Ϊ�Ѵ��������
	����������  �ļ�ָ�룬ָ��������ļ�	
               �ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
	��������ֵ��	��
*/
void InitScore(FILE *fp, STUDENT *stu)
{
    int i;
    STUDENT *p;
    for (i = 0, p = stu; p < p + MAX_STUDENT_NUMBER; p++)
    {

        fscanf(fp, "%s%s%s%f%f%f", &p->name, &p->id, &p->sex, &p->score[0], &p->score[1], &p->score[2]);
        if (fgetc(fp) == EOF)
        {
            break;
        }
        i++;
    }
    student_number = i;
}

/*  �������ܣ�	��datas.dat�ļ���ĩβ��ӴӼ�������ѧ����������ѧ�š��Ա𡢳ɼ�
               ����student_number + 1
	����������  �ļ�ָ��	 
               �ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
	��������ֵ��	��
*/
void AppendScore(FILE *fp, STUDENT *head)
{
    STUDENT *p;
    p = head;
    printf("\n����������");
    scanf("%s", &(p + student_number)->name);
    printf("����ѧ�ţ�");
    scanf("%s", (p + student_number)->id);
    printf("�������Ա�");
    scanf("%s", &(p + student_number)->sex);
    printf("����Ӣ��ɼ���");
    scanf("%f", &(p + student_number)->score[0]);
    printf("���������ɼ���");
    scanf("%f", &(p + student_number)->score[1]);
    printf("��������ɼ���");
    scanf("%f", &(p + student_number)->score[2]);
    student_number++;
}

/*	�������ܣ�	��ӡ��ǰ��datas.dat�ļ���ѧ����������ѧ�š��Ա�ͳɼ�����Ϣ
	����������	�ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
	��������ֵ��	��
*/
void PrintScore(STUDENT *head)
{
    STUDENT *p;
    int i;

    printf("����\tѧ��\t\t�Ա�\tӢ��\t�����\t����\tƽ����\n"); /* ��ӡ��ͷ */
    for (p = head; p < head + student_number; p++)              /* ��ӡstudent_number��ѧ������Ϣ */
    {
        printf("%s\t", p->name);
        printf("%s\t", p->id);
        printf("%s\t", p->sex);
        printf("%.0f\t", p->score[0]);
        printf("%.0f\t", p->score[1]);
        printf("%.0f\t", p->score[2]);
        printf("%.1f\n", p->averageSCore);
    }
}

/* 	�������ܣ�	����ÿ��ѧ��3�Ź��ε�ƽ���ɼ�
	����������	�ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
	��������ֵ��	��
*/
void TotalScore(STUDENT *head)
{
    STUDENT *p;
    int i;
    float sum;

    for (p = head; p < head + student_number; p++)
    {
        sum = 0;
        for (i = 0; i < SCORE_NUMBER; i++)
        {
            sum = sum + p->score[i];
        }
        p->averageSCore = sum / SCORE_NUMBER;
    }
}

/* 	�������ܣ�	��ѡ�񷨰�Ӣ��ɼ��ɸߵ�������
	����������	�ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
				���ͱ���n����ʾѧ������
	��������ֵ��	��
*/
void SortScore(STUDENT *head)
{
    int i, j, k;
    STUDENT temp;

    for (i = 0; i < student_number - 1; i++)
    {
        k = i;
        for (j = i; j < student_number; j++)
        {
            if ((head + j)->score[0] > (head + k)->score[0])
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = *(head + k);
            *(head + k) = *(head + i);
            *(head + i) = temp;
        }
    }
}

/* 	�������ܣ�	����ѧ����ѧ��
	����������	�ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
				���ͱ���num����ʾҪ���ҵ�ѧ��
	��������ֵ��	����ҵ�ѧ�ţ��򷵻����ڽṹ�������е�λ�ã����򷵻�-1
*/
int SearchNum(STUDENT *head, char num[])
{
    int i;

    for (i = 0; i < student_number; i++)
    {
        if (strcmp((head + i)->id, num) == 0)
            return i;
    }
    return -1;
}

/* 	�������ܣ�	��ѧ�Ų���ѧ���ɼ�����ʾ���ҽ��
	����������	�ṹ��ָ��head��ָ��洢ѧ����Ϣ�Ľṹ��������׵�ַ
	��������ֵ��	��
*/
void SearchScore(STUDENT *head)
{
    char number[10], findNo;

    printf("����������Ҫ���ҵ�ѧ����ѧ�ţ�");
    scanf("%s", number);
    findNo = SearchNum(head, number);
    if (findNo == -1)
    {
        printf("\n�޷��ҵ���ѧ����\n");
    }
    else
    {
        printf("����\tѧ��\t\t�Ա�\tӢ��\t�����\t����\tƽ����\n"); /* ��ӡ��ͷ */
        printf("%s\t%s\t%s\t%.0f\t%.0f\t%.0f\t%.1f", (head + findNo)->name,
               (head + findNo)->id,
               (head + findNo)->sex,
               (head + findNo)->score[0],
               (head + findNo)->score[1],
               (head + findNo)->score[2],
               (head + findNo)->averageSCore);
    }
}

/*	�������ܣ�	��ʾ�˵�������û����������ѡ��
	����������	��
	��������ֵ��	�û������ѡ��
*/
char Menu(void)
{
    char ch;

    printf("\n�����˵�\n");
    printf(" 1.���ѧ��\n");
    printf(" 2.�ɼ���\n");
    printf(" 3.����\n");
    printf(" 4.����\n");
    printf(" 0.�˳�����\n");
    printf("������һ��ָ�");
    scanf(" %c", &ch); /*��%cǰ���һ���ո񣬽����ڻ������еĻس�������*/
    return ch;
}

int main()
{
    STUDENT stu[MAX_STUDENT_NUMBER];
    char ch;
    FILE *fp = fopen("F:\\Study\\IT\\C\\Project\\table\\datas.dat", "at+");

    InitScore(fp, stu);
    TotalScore(stu);
    if (fp == NULL)
    {
        printf("���ļ�ʧ�ܣ�\n");
    }
    while (1)
    {
        ch = Menu(); /* ��ʾ�˵�������ȡ�û����� */
        switch (ch)
        {
        case '1':
            AppendScore(fp, stu); /* ���óɼ����ģ�� */
            TotalScore(stu);
            break;
        case '2':
            PrintScore(stu); /* ���óɼ���ʾģ�� */
            break;
        case '3':
            SearchScore(stu); /* ���ð�ѧ�Ų���ģ�� */
            break;
        case '4':
            SortScore(stu); /* ���óɼ�����ģ�� */
            printf("\nSorted result\n");
            PrintScore(stu); /* ��ʾ�ɼ������� */
            break;
        case '0':
            exit(0); /* �˳����� */
            printf("End of program!");
            break;
        default:
            printf("Input error!");
            break;
        }
    }

    fclose(fp);
    return 0;
}
