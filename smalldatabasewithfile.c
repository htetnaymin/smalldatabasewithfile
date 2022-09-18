#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

void insert();
void append();
void reload();
void writedata();
void search();
void update();
int checker();
int uid[MAX];
int id=0;
char uname[MAX][MAX];
char username[MAX];
char upass[MAX][MAX];
char password[MAX];
int uamount[MAX];
int amount=0;
int uage[MAX];
int age=0;
char ulocat[MAX][MAX];
char location[MAX];
int myindex=0;
int cuindex=0;
char temp[MAX];
int countforreload=0;
int option=0;
FILE *f;

int main()
{
    reload();
    printf("1.insert,2.search,3.update,0.exit");
    scanf("%d",&option);
    switch (option)
    {
        case 0:
            exit(0);
        case 1:
            insert();
            break;
        case 2:
            search();
            break;
        case 3:
            update();
            break;
        default:
            main();
            break;
    }
    main();
//    reload();
//    insert();
//    reload();
//    strcpy(upass[0],"HNM");
    return 0;
}
void insert()
{
    for (int i = 0; i < MAX; ++i)
    {
        if(uid[i]==0)
        {
            myindex=i;
            if(i!=0)
            {
                if(uid[i-1]>0)
                {
                    uid[i]=uid[i-1]+1;
                }
            }
            else
            {
                uid[i]=1;
            }
            break;
        }
    }
    printf("Enter Your username : ");
    fflush(stdin);
    fgets(uname[myindex],sizeof(username),stdin);
    printf("Enter Your password : ");
    fflush(stdin);
    fgets(upass[myindex],sizeof(password),stdin);
    int m;
    printf("Enter money amount : ");
    scanf("%d",&uamount[myindex]);
    printf("Enter age : ");
    scanf("%d",&uage[myindex]);
    printf("Enter location : ");
    fflush(stdin);
    fgets(ulocat[myindex],sizeof(location),stdin);

    for (int j = 0; j < MAX; ++j)
    {
        int condition=0;
        if(uname[myindex][j]=='\n')
        {
            uname[myindex][j]='\0';
            condition=condition+1;
        }
        if(upass[myindex][j]=='\n')
        {
            upass[myindex][j]='\0';
            condition=condition+1;
        }
        if(ulocat[myindex][j]=='\n')
        {
            ulocat[myindex][j]='\0';
            condition=condition+1;
        }
        if(condition==3)
        {
            break;
        }
    }
    append();
}
void append()
{
    f=fopen("database.txt","r");
    if(f==NULL)
    {
        fclose(f);
        f=fopen("database.txt","w");
    }
    fclose(f);
    f=fopen("database.txt","a");
    fprintf(f,"%d|%s|%s|%d|%d|%s\n",uid[myindex],uname[myindex],upass[myindex],uamount[myindex],uage[myindex],ulocat[myindex]);
    fclose(f);
}
void reload()
{
    char checkeof;
    char temp1[MAX];
    int k=0;
    int oldj=0;
    f=fopen("database.txt","r");
    checkeof=fgetc(f);
    if(f==NULL || checkeof==EOF)
    {
        fclose(f);
        return;
    }
    ungetc(checkeof,f);
    for (int i = 0; i < 100; ++i)
    {
        fscanf(f,"%[^\n]s",&temp);
        k=0;
        oldj=0;
        for (int j = 0; j < MAX; ++j)
        {
            temp1[j]='\0';
        }
        for (int j = oldj;; ++j)
        {
            if (temp[j] == '|') {
                oldj = j + 1;
                break;
            }
            temp1[j] = temp[j];
        }
        uid[i]=atoi(temp1);
        k=0;
        for (int j = oldj;; ++j)
        {
            if (temp[j] == '|') {
                oldj = j + 1;
                break;
            }
            uname[i][k] = temp[j];
            k++;
        }
        k=0;
        for (int j = oldj;; ++j)
        {
            if (temp[j] == '|') {
                oldj = j + 1;
                break;
            }
            upass[i][k] = temp[j];
            k++;
        }
        for (int j = 0; j < MAX; ++j)
        {
            temp1[j]='\0';
        }
        k=0;
        for (int j = oldj;; ++j)
        {
            if (temp[j] == '|') {
                oldj = j + 1;
                break;
            }
            temp1[k] = temp[j];
            k++;
        }
        uamount[i]=atoi(temp1);
        for (int j = 0; j < MAX; ++j)
        {
            temp1[j]='\0';
        }
        k=0;
        for (int j = oldj;; ++j)
        {
            if (temp[j] == '|') {
                oldj = j + 1;
                break;
            }
            temp1[k] = temp[j];
            k++;
        }
        uage[i]=atoi(temp1);
        k=0;
        for (int j = oldj;; ++j)
        {
            if (temp[j] == '\0') {
                oldj = j + 1;
                break;
            }
            ulocat[i][k] = temp[j];
            k++;
        }
        fgetc(f);
        checkeof=fgetc(f);
        if(checkeof==EOF)
        {
            fclose(f);
            return ;
        }

        ungetc(checkeof,f);
    }
    fclose(f);
}
void writedata()
{
    f=fopen("database.txt","r");
    if(f==NULL)
    {
        fclose(f);
        f=fopen("database.txt","w");
    }
    fclose(f);
    f=fopen("database.txt","w");
    fclose(f);
    f=fopen("database.txt","a");
    int numforwritedata=0;
    for (int i = 0; i < MAX; ++i)
    {
        if(uid[i]==0)
        {
            numforwritedata=i;
            break;
        }
    }
    for (int i = 0; i < numforwritedata; ++i)
    {
        fprintf(f,"%d|%s|%s|%d|%d|%s\n",uid[i],uname[i],upass[i],uamount[i],uage[i],ulocat[i]);
    }
}
void search()
{
    printf("Enter username to search : ");
    fflush(stdin);
    fgets(username,sizeof(username),stdin);
    int numforsearch=0;
    for (int i = 0; i < MAX; ++i)
    {
        if(uid[i]==0)
        {
            numforsearch=i;
            break;
        }
    }
    for (int i = 0; i < numforsearch; ++i)
    {
        if(checker(username,uname[i]))
        {
            printf("%d|%s|%s|%d|%d|%s\n",uid[i],uname[i],upass[i],uamount[i],uage[i],ulocat[i]);
            return;
        }
    }
    printf("Username not found!\n");
}
int checker(char input[], char check[])
{
    int i, result = 1;
    for (i = 0; i< 100; i++)
    {
        if(input[i]=='\n' && check[i]=='\0')
        {
            if(strlen(check)==0)
            {
                return 0;
            }
            return result;
        }
        if (input[i] != check[i])
        {
            result = 0;
            return result;
        }
    }
    return result;
}
void update()
{
    printf("Enter your username : ");
    fflush(stdin);
    fgets(username,sizeof(username),stdin);
    int numforsearch=0;
    for (int i = 0; i < MAX; ++i)
    {
        if(uid[i]==0)
        {
            numforsearch=i;
            break;
        }
    }
    for (int i = 0; i < numforsearch; ++i)
    {
        if (checker(username, uname[i]))
        {
            printf("%d|%s|%s|%d|%d|%s\n",uid[i],uname[i],upass[i],uamount[i],uage[i],ulocat[i]);
            myindex=i;
        }
    }
    opt:
    printf("1.update username\n2.update password\n3.update amount\n4.update age\n5.update location\n0.return");
    scanf("%d",&option);
    switch (option)
    {
        case 0:
            return;
        case 1:
            printf("Enter username to update : ");
            fflush(stdin);
            fgets(username,sizeof(username),stdin);
            strcpy(uname[myindex],username);
            break;
        case 2:
            printf("Enter password to update : ");
            fflush(stdin);
            fgets(password,sizeof(password),stdin);
            strcpy(upass[myindex],password);
            break;
        case 3:
            printf("Enter amount to update : ");
            scanf("%d",amount);
            uamount[myindex]=amount;
            break;
        case 4:
            printf("Enter age to update : ");
            scanf("%d",age);
            uage[myindex]=age;
            break;
        case 5:
            printf("Enter location to update : ");
            fflush(stdin);
            fgets(location,sizeof(location),stdin);
            strcpy(ulocat[myindex],location);
            break;
        default:
            printf("Not option found!\n");
            goto opt;
            break;
    }
    for (int j = 0; j < MAX; ++j)
    {
        if(uname[myindex][j]=='\n')
        {
            uname[myindex][j]='\0';
        }
        if(upass[myindex][j]=='\n')
        {
            upass[myindex][j]='\0';
        }
        if(ulocat[myindex][j]=='\n')
        {
            ulocat[myindex][j] = '\0';
        }
    }
    writedata();
}
