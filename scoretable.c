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
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
				整型变量n，表示学生人数
				整型变量m，表示考试科目
	函数返回值：	无
*/
void InitScore(FILE *fp, STUDENT *stu)
{
    int i;
    STUDENT *p;
    for (i = 0, p = stu; p < p + MAX_STUDENT_NUMBER; p++)
    {
        if (fgetc(fp) == EOF)
        {
            break;
        }
        fscanf(fp, "%s", p->name);
        fscanf(fp, "%d", p->id);
        fscanf(fp, "%s", p->sex);
        fscanf(fp, "%f", p->score[0]);
        fscanf(fp, "%f", p->score[1]);
        fscanf(fp, "%f", p->score[2]);
        i++;
    }
    student_number = i;
}

/*  函数功能：	向datas.dat文件的末尾添加从键盘输入学生的姓名、学号、性别、成绩
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
				整型变量n，表示学生人数
				整型变量m，表示考试科目
	函数返回值：	无
*/
void AppendScore(STUDENT *head, int n, int m)
{
    int j;
    STUDENT *p;

    for (p = head; p < head + n; p++)
    {
        printf("\nInput number:");
        scanf("%d", &p->id);
        printf("Input name:");
        scanf("%s", p->name);
        for (j = 0; j < m; j++)
        {
            printf("Input score%d:", j + 1);
            scanf("%d", p->score + j);
        }
    }
}

/*	函数功能：	打印n个学生的学号、姓名和成绩等信息
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
				整型变量n，表示学生人数
				整型变量m，表示考试科目
	函数返回值：	无
*/
void PrintScore(STUDENT *head, int n, int m)
{
    STUDENT *p;
    int i;
    char str[100] = {'\0'}, temp[3];

    strcat(str, "Number     Name  ");
    for (i = 1; i <= m; i++)
    {
        strcat(str, "Score");
        itoa(i, temp, 10);
        strcat(str, temp);
        strcat(str, " ");
    }
    strcat(str, "     sum  average");

    printf("%s", str);                /* 打印表头 */
    for (p = head; p < head + n; p++) /* 打印n个学生的信息 */
    {
        printf("\nNo.%3d%8s", p->id, p->name);
        for (i = 0; i < m; i++)
        {
            printf("%7d", p->score[i]);
        }
        printf("%9.2f\n", p->averageSCore);
    }
}

/* 	函数功能：	计算每个学生3门功课的平均成绩
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
	函数返回值：	无
*/
void TotalScore(STUDENT *head, int n, int m)
{
    STUDENT *p;
    int i;
    float sum;

    for (p = head; p < head + n; p++)
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
void SortScore(STUDENT *head, int n)
{
    int i, j, k;
    STUDENT temp;

    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i; j < n; j++)
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
				整型变量n，表示学生人数
	函数返回值：	如果找到学号，则返回它在结构体数组中的位置，否则返回-1
*/
int SearchNum(STUDENT *head, int num, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if ((head + i)->id == num)
            return i;
    }
    return -1;
}

/* 	函数功能：	按学号查找学生成绩并显示查找结果
	函数参数：	结构体指针head，指向存储学生信息的结构体数组的首地址
				整型变量n，表示学生人数
				整型变量m，表示考试科目
	函数返回值：	无
*/
void SearchScore(STUDENT *head, int n, int m)
{
    int number, findNo;

    printf("Please Input the number you want to search:");
    scanf("%d", &number);
    findNo = SearchNum(head, number, n);
    if (findNo == -1)
    {
        printf("\nNot found!\n");
    }
    else
    {
        PrintScore(head + findNo, 1, m);
    }
}

/*	函数功能：	显示菜单并获得用户键盘输入的选项
	函数参数：	无
	函数返回值：	用户输入的选项
*/
char Menu(void)
{
    char ch;

    printf("\n操作指南\n");
    printf(" 1.添加学生\n");
    printf(" 2.成绩表\n");
    printf(" 3.查找\n");
    printf(" 4.排序\n");
    printf(" 0.\n");
    printf("请输入一个指令：");
    scanf(" %c", &ch); /*在%c前面加一个空格，将存于缓冲区中的回车符读入*/
    return ch;
}

int main()
{
    STUDENT stu[MAX_STUDENT_NUMBER];
    char ch;
    int m, n;
    FILE *fp = fopen("F:\\Study\\IT\\C\\Project\\table\\datas.dat", "at+");
    InitScore(fp, stu);
    if (fp != NULL)
    {

        printf("Input student number and course number(n<40,m<10):");
        scanf("%d,%d", &n, &m);
        while (1)
        {
            ch = Menu(); /* 显示菜单，并读取用户输入 */
            switch (ch)
            {
            case '1':
                AppendScore(stu, n, m); /* 调用成绩添加模块 */
                TotalScore(stu, n, m);
                break;
            case '2':
                PrintScore(stu, n, m); /* 调用成绩显示模块 */
                break;
            case '3':
                SearchScore(stu, n, m); /* 调用按学号查找模块 */
                break;
            case '4':
                SortScore(stu, n); /* 调用成绩排序模块 */
                printf("\nSorted result\n");
                PrintScore(stu, n, m); /* 显示成绩排序结果 */
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
    }
    fclose(fp);
    return 0;
}
