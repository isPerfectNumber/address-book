#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0

struct books
{
    char name[20];      //姓名
    char tel[20];       //电话
    char company[100];  //单位
    char email[30];     //邮箱
    char add[100];      //住址
    char note[100];     //备注
}books[50];

int cnt = 0; //用全局变量cnt标记联系人数目

//声明函数
void enter();       //按1录入
void del();         //按2删除
void list();        //按3显示
void search();      //按4查找
void save();        //按5保存
void load();        //按6载入
void deleteALL();   //按7清空
void modify();      //按8修改

//other functions
int telCheck(char s[]);
void changeInfo();
void sort();
int emailCheck(char s[]);


int main()
{   
    system("chcp 65001"); /* cmd chcp 命令切换字符编码为 utf-8 以显示中文 */
    int cmd;
    while(1)
    {
        printf("\n");
        printf("\t\t\t\t******************************************");
        printf("\n");
        printf("\t\t\t\t      Welcome to the Address Book.");
        printf("\n");
        printf("\t\t\t\t******************************************");
        printf("\n");
        printf("\n");
        printf("\t\t\t\tOPTIONS\n");
        printf("\t\t\t\t1. add a contact\n");
        printf("\t\t\t\t2. delete a contact\n");
        printf("\t\t\t\t3. list the contacts\n");
        printf("\t\t\t\t4. search for a contact\n");
        printf("\t\t\t\t5. save the list\n");
        printf("\t\t\t\t6. load the list\n");
        printf("\t\t\t\t7. clear ALL\n");
        printf("\t\t\t\t8. modify someone's information\n");
        printf("\t\t\t\t0. cancel\n");
        printf("\n");
        printf("\t\t\t\tWhich do you want? :");
        scanf("%d", &cmd);//用户输入相应指令

        if (cmd == 0)
        {
            system("cls");
            printf("\n");
            printf("\t\t\t\t******************************************");
            printf("\n");
            printf("\t\t\t\t           Thanks for using.");
            printf("\n");
            printf("\t\t\t\t******************************************\n");
            break;
        }
        switch(cmd)
        {
            case 1: enter(); break;
            case 2: del(); break;
            case 3: list(); break;
            case 4: search(); break;
            case 5: save(); break;
            case 6: load(); break;
            case 7: deleteALL(); break;
            case 8: modify(); break;
            default:
                printf("\n\t\t\t\tYour option does not exist. Please choose again.\n");
                break;
        }
    }

    system("pause");
    return 0;
}


void enter()//1 录入
{
    if (cnt == 0) printf("\n\t\t\t\tThe book is empty.");
    entrance:
    printf("\n\n\t\t\t\tName:");
    scanf("%s",books[cnt].name);
    for (int i = 0; i < cnt; ++i)//利用for循环对联系人信息依次查找
    {
        if (strcmp(books[cnt].name, books[i].name) == 0)//此时查找到了该联系人
        {
            printf("\t\t\t\tThere is a contact with the name you just keyed in. You want to view or change his information, \n\t\t\t\tor maybe you happened to key in the WRONG name?\n");
            choose:
            printf("\t\t\t\tview(1) or change(2) or wrongName(3):");
            int flag;//flag为输入内容
            scanf("%d", &flag);
            if (flag == 1)//“查看”子功能
            {
            	printf("\n\t\t\t\tName: %s\n", books[i].name);
				printf("\t\t\t\tPhone: %s\n", books[i].tel);
				printf("\t\t\t\tCompany: %s\n", books[i].company);
				printf("\t\t\t\tE-mail: %s\n", books[i].email);
				printf("\t\t\t\tAddress: %s\n", books[i].add);
				printf("\t\t\t\tNote: %s\n", books[i].note);
           		printf("\n");
                system("pause");
                return;
			}else if (flag == 2)
            {
                changeInfo(i);
                return;
            }else if (flag == 3)
            {
                goto entrance;
            }else //键入非“1”“2”或“3”
            { 
                printf("\t\t\t\tThe option does not exist. ");
                printf("\n");
                return;
            }
        }
    }
    while (1)
    {
        printf("\t\t\t\tPhone: ");
        scanf("%s", books[cnt].tel);
        int result = telCheck(books[cnt].tel);
        if (!result)
        {
            printf("\t\t\t\tWRONG number. Please key in again!\n");
        }else
        {
            break;
        }
    }
    printf("\t\t\t\tCompany: ");
    scanf("%s",books[cnt].company);
    while (1)
    {
        printf("\t\t\t\tE-mail: ");
        scanf("%s",books[cnt].email);
        int result = emailCheck(books[cnt].email);
        if (!result)
        {
            printf("\t\t\t\tWRONG e-mail address. Please key in again!\n");
        }else
        {
            break;
        }
    }
    printf("\t\t\t\tAddress: ");
    scanf("%s",books[cnt].add);
    printf("\t\t\t\tNote: ");
    scanf("%s",books[cnt].note);
    printf("\n\t\t\t\tDone. Please key in 5 to save the list.\n");//提示用户保存，体现用户友好性
    ++cnt;//录入完成后通讯录数目+1
    sort();
}

void del()//2 删除
{
    char tName[20];
    printf("\t\t\t\tWho do you want to delete?");
    scanf("%s", tName);

    for (int i = 0; i < cnt; ++i)
    {
        if (strcmp(tName, books[i].name) == 0)
        {
            for (int j = i; j < cnt - 1; ++j)
            {
                strcpy(books[j].name, books[j + 1].name);
                strcpy(books[j].tel, books[j + 1].tel);
                strcpy(books[j].company, books[j + 1].company);
                strcpy(books[j].email, books[j + 1].email);
                strcpy(books[j].add, books[j + 1].add);
                strcpy(books[j].note, books[j + 1].note);
            }
            printf("\n");
            printf ("\t\t\t\tDone. Please key in 5 to save the list.\n");
            printf("\n");
            --cnt;
            break;
        }
        else if (i == cnt - 1){
            printf("\n");
            printf ("\t\t\t\t%sThe person does not exist.\n", tName);
            printf("\n");
        }
    }
}

void list()//3 显示
{
    if (cnt == 0)
    {
        printf("\t\t\t\tThe book is empty. Please add your contact or load the file first.\n");
    }else
    {
        for (int i = 0; i < cnt; ++i)
        {
            printf("\n");
            printf("\t\t\t\tContact %d:\n",i + 1);
            printf("\t\t\t\tName: %s\n",books[i].name);
            printf("\t\t\t\tPhone: %s\n",books[i].tel);
            printf("\t\t\t\tCompany: %s\n",books[i].company);
            printf("\t\t\t\tE-mail: %s\n",books[i].email);
            printf("\t\t\t\tAddress: %s\n",books[i].add);
            printf("\t\t\t\tNote: %s\n",books[i].note);
            printf("\n");
        }
    }
    system("pause");
}

void search()//4 查找
{
    char tName[20];
    printf("\t\t\t\tWho do you want to search for? :");
    scanf("%s", tName);
    printf("\n");
    for (int i = 0; i < cnt; ++i)
    {
        if (strcmp(tName, books[i].name) == 0)
        {
            printf("\n\t\t\t\tName: %s\n", books[i].name);
			printf("\t\t\t\tPhone: %s\n", books[i].tel);
			printf("\t\t\t\tCompany: %s\n", books[i].company);
			printf("\t\t\t\tE-mail: %s\n", books[i].email);
			printf("\t\t\t\tAddress: %s\n", books[i].add);
			printf("\t\t\t\tNote: %s\n", books[i].note);
            printf("\n");
            break;
        }
        else if (i == cnt - 1){
            printf ("\t\t\t\t%s does not exist.\n", tName);
            printf("\n");
        }
    }
    system("pause");
}

void save()//5 保存
{
    FILE *fp;
    if ((fp = fopen("Contact.txt", "w")) != NULL)
    {
        for (int i = 0; i < cnt; ++i){
            fprintf(fp, "%s\n",books[i].name);
            fprintf(fp, "%s\n",books[i].tel);
            fprintf(fp, "%s\n",books[i].company);
            fprintf(fp, "%s\n",books[i].email);
            fprintf(fp, "%s\n",books[i].add);
            fprintf(fp, "%s\n",books[i].note);
            fprintf(fp, "\n");
        }
        fclose(fp);
        system("cls");
        printf("\n");
        printf("\t\t\t\tDone.\n");
    }
    else
    {
        printf("\n");
        printf("\t\t\t\tFailed.\n");
    }
}

void load()//6 载入
{
    FILE *fp;
    if ((fp = fopen("Contact.txt", "r")) != NULL)
    {
        while (fscanf(fp, "%s %s %s %s %s %s", 
            books[cnt].name, books[cnt].tel, books[cnt].company, 
            books[cnt].email, books[cnt].add, books[cnt].note) == 6)
        {
            ++cnt;
        }
        fclose(fp);
        printf("\n");
        system("cls");
        printf("\t\t\t\tDone.\n");
    }
    else
    {
        printf("\n");
        printf("\t\t\t\tFailed.\n");
    }
}

void deleteALL(){//7 清除
    printf("\t\t\t\tThe whole list will be cleared. Are you sure?");
    printf("\t\t\t\tYou can only key in '1' to go on. : ");
    int flag;
    scanf("%d", &flag);
    if (flag == 1)
    {
        FILE *fp;
        if ((fp = fopen("Contact.txt", "w")) != NULL)
        {
           fclose(fp);
           printf("\t\t\t\tDone. Now the list has been cleared.\n");
        }else
        {
            printf("\t\t\t\tFailed.\n");
        }
    }
}

void modify(){//8 修改
    char tName[20];//即将输入的字符串
    int option;
    printf("\t\t\t\tWhose information do you want to modify? :");
    scanf("%s", tName);
    printf("\n");
    for (int i = 0; i < cnt; ++i)//利用for循环对联系人信息依次查找
    {
        if (strcmp(tName, books[i].name) == 0)//此时查找到了该联系人
        {
            changeInfo(i);
            break;
        }
        else if (i == cnt - 1){//遍历所有联系人未能找到输入的名字
            printf ("\t\t\t\t%s does not exist.\n", tName);
            printf("\n");
        }
    }
}

//other functions
int telCheck(char s[]){//检查输入的电话号码字符串是否均为数字
    int i;
    for (i = 0; s[i] != 0; i++)//出现非数字字符直接报错
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return ERROR;
        }
    }
    return OK;
}

void changeInfo(int i){
    int option;
    printf("\n");
    printf("\t\t\t\t1.Name\n");
    printf("\t\t\t\t2.Phone\n");
    printf("\t\t\t\t3.Company\n");
    printf("\t\t\t\t4.E-mail\n");
    printf("\t\t\t\t5.Address\n");
    printf("\t\t\t\t6.Note\n");
    printf("\t\t\t\t0.Cancel the part\n");
    printf("\t\t\t\tWhich do you want to modify? ");
    scanf("%d", &option);
    switch(option){
    case 0: break;
    case 1:
        printf("\t\t\t\tThe NAME is %s\n", books[i].name);
        printf("\t\t\t\tThe NAME will be: ");
        scanf("%s",books[i].name);
        return;
    case 2:
        printf("\t\t\t\tThe PHONE is %s\n", books[i].tel);

        while(1){
            int result;
            printf("\t\t\t\tThe PHONE will be: ");
            scanf("%s", books[i].tel);
            result = telCheck(books[i].tel);
            if(!result)
            {
                printf("\t\t\t\tWRONG number. Please key in again.\n");
            }else
            {
                break;
            }
        }
        return;
    case 3:
        printf("\t\t\t\tThe COMPANY is %s\n", books[i].company);
        printf("\t\t\t\tThe COMPANY will be: ");
        scanf("%s",books[i].company);
        return;
    case 4:
        printf("\t\t\t\tEhe E-MAIL is %s\n", books[i].email);
        
        while(1){
            int result;
            printf("\t\t\t\tThe E-MAIL will be: ");
            scanf("%s", books[i].email);
            result = telCheck(books[i].email);
            if(!result)
            {
                printf("\t\t\t\tWRONG e-mail address. Please key in again.\n");
            }else
            {
                break;
            }
        }
        return;
    case 5:
        printf("\t\t\t\tThe ADDRESS is %s\n", books[i].add);
        printf("\t\t\t\tThe ADDRESS will be: ");
        scanf("%s",books[i].add);
        return;
    case 6:
        printf("\t\t\t\tYou NOTED: %s\n", books[i].note);
        printf("\t\t\t\tYour new NOTE: ");
        scanf("%s",books[i].note);
        return;
    default:
        printf("\t\t\t\tWRONG option. Please choose again.");
        return;
    }
}

void sort(){//使用冒泡排序将已经存储的联系人按照名字的字母序排列
    int j, l;
    char temp[100];
    for ( j = 0; j < cnt - 1; j++)
    {
        for ( l = 0; l < cnt - 1 - j; l++)
        {
            if (strcmp(books[l].name, books[l+1].name) > 0)
            {
                strcpy(temp,books[l].name);
				strcpy(books[l].name,books[l+1].name);
				strcpy(books[l+1].name,temp);
				
				strcpy(temp,books[l].tel);
				strcpy(books[l].tel,books[l+1].tel);
				strcpy(books[l+1].tel,temp);
				
				strcpy(temp,books[l].company);
				strcpy(books[l].company,books[l+1].company);
				strcpy(books[l+1].company,temp);
				
				strcpy(temp,books[l].email);
				strcpy(books[l].email,books[l+1].email);
				strcpy(books[l+1].email,temp);
				
				strcpy(temp,books[l].add);
				strcpy(books[l].add,books[l+1].add);
				strcpy(books[l+1].add,temp);
				
				strcpy(temp,books[l].note);
				strcpy(books[l].note,books[l+1].note);
				strcpy(books[l+1].note,temp);
            }
        }
    }
}

int emailCheck(char s[]){
    int i, flag = 0;
    for ( i = 0; s[i] != 0 ; i++)
    {
        if (s[i] == '@')
        {
            flag = 1;
            return OK;
        }
    }
    if (!flag) return ERROR;
}