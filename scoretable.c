#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NAME_NUMBER 10         /*定义姓名最大长度*/
#define ID_NUMBER 9            /*定义学号长度*/
#define SEX_NUMBER 3           /*定义性别长度*/
#define SCORE_NUMBER 3         /*定义成绩门数，此时位3门*/
#define MAX_STUDENT_NUMBER 100 /*定义最大学生数*/

int student_number = 0; /*记录此时已经存入的学生个数*/

struct student
{
    char name[NAME_NUMBER];
    char id[ID_NUMBER];
    char sex[SEX_NUMBER];
    float score[SCORE_NUMBER];
    float averageSCore;
};
typedef struct student STUDENT;

/*  函数功能：	初始化结构体数组，将文件中的信息存入数组，并将student_number设置为已存入的人数
	函数参数：  文件指针，指向操作的文件	
               结构体指针head，指向存储学生信息的结构体数组的首地址
	函数返回值：	无
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

/*  函数功能：	向datas.dat文件的末尾添加从键盘输入学生的姓名、学号、性别、成绩
               并将student_number + 1
	函数参数：  文件指针	 
               结构体指针head，指向存储学生信息的结构体数组的首地址
	函数返回值：	无
*/
void AppendScore(FILE *fp, STUDENT *head)
{
    STUDENT *p;
    p = head;
    printf("\n输入姓名：");
    scanf("%s", &(p + student_number)->name);
    printf("输入学号：");
    scanf("%s", (p + student_number)->id);
    printf("请输入性别：");
    scanf("%s", &(p + student_number)->sex);
    printf("输入英语成绩：");
    scanf("%f", &(p + student_number)->score[0]);
    printf("输入计算机成绩：");
    scanf("%f", &(p + student_number)->score[1]);
    printf("输入高数成绩：");
    scanf("%f", &(p + student_number)->score[2]);
    student_number++;
}

/*	函数功能：	打印当前在datas.dat文件中学生的姓名、学号、性别和成绩等信息
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
	函数返回值：	无
*/
void PrintScore(STUDENT *head)
{
    STUDENT *p;
    int i;

    printf("姓名\t学号\t\t性别\t英语\t计算机\t高数\t平均分\n"); /* 打印表头 */
    for (p = head; p < head + student_number; p++)              /* 打印student_number个学生的信息 */
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

/* 	函数功能：	计算每个学生3门功课的平均成绩
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
	函数返回值：	无
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

/* 	函数功能：	用选择法按英语成绩由高到低排序
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
				整型变量n，表示学生人数
	函数返回值：	无
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

/* 	函数功能：	查找学生的学号
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
				整型变量num，表示要查找的学号
	函数返回值：	如果找到学号，则返回它在结构体数组中的位置，否则返回-1
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

/* 	函数功能：	按学号查找学生成绩并显示查找结果
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
	函数返回值：	无
*/
void SearchScore(STUDENT *head)
{
    char number[10], findNo;

    printf("请输入你想要查找的学生的学号：");
    scanf("%s", number);
    findNo = SearchNum(head, number);
    if (findNo == -1)
    {
        printf("\n无法找到该学生！\n");
    }
    else
    {
        printf("姓名\t学号\t\t性别\t英语\t计算机\t高数\t平均分\n"); /* 打印表头 */
        printf("%s\t%s\t%s\t%.0f\t%.0f\t%.0f\t%.1f", (head + findNo)->name,
               (head + findNo)->id,
               (head + findNo)->sex,
               (head + findNo)->score[0],
               (head + findNo)->score[1],
               (head + findNo)->score[2],
               (head + findNo)->averageSCore);
    }
}

/*	函数功能：	显示菜单并获得用户键盘输入的选项
	函数参数：	无
	函数返回值：	用户输入的选项
*/
char Menu(void)
{
    char ch;

    printf("\n操作菜单\n");
    printf(" 1.添加学生\n");
    printf(" 2.成绩表\n");
    printf(" 3.查找\n");
    printf(" 4.排序\n");
    printf(" 0.退出程序\n");
    printf("请输入一个指令：");
    scanf(" %c", &ch); /*在%c前面加一个空格，将存于缓冲区中的回车符读入*/
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
        printf("打开文件失败！\n");
    }
    while (1)
    {
        ch = Menu(); /* 显示菜单，并读取用户输入 */
        switch (ch)
        {
        case '1':
            AppendScore(fp, stu); /* 调用成绩添加模块 */
            TotalScore(stu);
            break;
        case '2':
            PrintScore(stu); /* 调用成绩显示模块 */
            break;
        case '3':
            SearchScore(stu); /* 调用按学号查找模块 */
            break;
        case '4':
            SortScore(stu); /* 调用成绩排序模块 */
            printf("\nSorted result\n");
            PrintScore(stu); /* 显示成绩排序结果 */
            break;
        case '0':
            exit(0); /* 退出程序 */
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
