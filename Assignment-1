#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct Node
{
    int uniqueID;
    char accName[25];
    int numofPost;
    int numofFollowing;
    int numofFollowers;
    char DateandTime[18];
    struct Node* next;
};
//this function takes file and file name and creates linked list than returns the linked list inside main function.
struct Node *initialiseMyAccount(FILE *inFile,char filename[])
{
    struct Node *temp,*head=NULL,*first,*last;
    char getch;
    char token[5];
    int count=0,i;

    inFile=fopen(filename,"r");
    if(inFile==NULL)
    {
        printf("The file cannot opened succesfully");
        exit(0);
    }

    getch=getc(inFile);
    while(getch != EOF)
    {
        if(getch=='\n')
        {
            count = count + 1;
        }
        getch=getc(inFile);
    }
    rewind(inFile);
    for(i=0;i<count;i++)
    {
        temp=(struct Node*)malloc(sizeof(struct Node));
        fscanf(inFile,"%d %c %[^;] %c %d %c %d %c %d %c %[^\n]",&temp->uniqueID,token,temp->accName,token,&temp->numofPost,token,&temp->numofFollowing,token,&temp->numofFollowers,token,temp->DateandTime);
        temp->next=NULL;
        
        if(head==NULL)
        {
            head = temp;
            first = last = temp;
        }
        else
        {
            last->next=temp;
            last=temp;
        }
    }
    fclose(inFile);
    return head;
}
//this function creates a file which has current time.this function is helps me for printing current data inside the list.
void currentTime()
{
    FILE *infile;
    infile=fopen("time.txt","w");
    time_t ti = time(NULL);
    struct tm t = *localtime(&ti);
    fprintf(infile,"%02d/%02d/%04d ",t.tm_mday,t.tm_mon+1,t.tm_year+1900);
    fprintf(infile,"%02d:%02d", t.tm_hour, t.tm_min);
    fclose(infile);
}
//this function adds new account inside the linked list.ß
void addAccount(struct Node **userAccount,char name[],int posts,int followers,int followings)
{
    FILE *time;
    int IDHolder;
    while((*userAccount) != NULL)
    {
        if(strcmp((*userAccount)->accName,name)==0)
        {
            printf("The account already exist!!\n");
            break;
        }
        IDHolder=(*userAccount)->uniqueID;
        userAccount=&(*userAccount)->next;
        if((*userAccount) == NULL)
        {
            time=fopen("time.txt","r");
            *userAccount=(struct Node*)malloc(sizeof(struct Node));
            strcpy((*userAccount)->accName,name);
            (*userAccount)->uniqueID=IDHolder+1;
            (*userAccount)->numofPost=posts;
            (*userAccount)->numofFollowers=followers;
            (*userAccount)->numofFollowing=followings;
            fscanf(time,"%[^\n]",(*userAccount)->DateandTime);
            (*userAccount)->next=NULL;
            userAccount=&(*userAccount)->next;
            fclose(time);
        }
    }
}
//this function search the given name from the user.
void searchAccount(struct Node **temp,char name[])
{
    int option;
    while((*temp) != NULL)
    {
        if(strcmp((*temp)->accName,name)==0)
        {
            printf("Account ID:%d\n",(*temp)->uniqueID);
            printf("Account name:%s\n",(*temp)->accName);
            printf("Number of posts:%d\n",(*temp)->numofPost);
            printf("Number of following:%d\n",(*temp)->numofFollowing);
            printf("Number of followers:%d\n",(*temp)->numofFollowers);
            printf("Date and Time:%s\n",(*temp)->DateandTime);
            option +=1;
        }
        temp=&(*temp)->next;
    }
    if(option==0)
    {
        printf("There is no account with this name in the list!!!!\n");
    }
}
//this function deletes the given unique ıd from the user.
void deleteAccount(struct Node **userAccount,int ID)
{
    int option=0;
    struct Node *tempPrev,*currentAcc;
    tempPrev=NULL;
    currentAcc=*userAccount;
    while(currentAcc!=NULL)
    {
        if(currentAcc->uniqueID==ID)
        {
            option+=1;
            if(tempPrev == NULL)
            {
                *userAccount = currentAcc->next;
            }
            else
            {
                tempPrev->next = currentAcc->next;
            }
        }
        tempPrev=currentAcc;
        currentAcc=currentAcc->next;
    }
    if(option==0)
    {
        printf("Account with ID %d does not exist.\n",ID);
    }
    else
    {
        printf("Account with ID %d has been deleted successfully.\n",ID);
    }
    
}
//prints all the data inside the list.
void printMyAccount(struct Node *temp)
{
    while(temp != NULL)
    {
        printf("Account ID:%d\nAccount name:%s\nNumber of posts:%d\nNumber of following:%d\nNumber of followers:%d\nDate and Time:%s\n\n",temp->uniqueID,temp->accName,temp->numofPost,temp->numofFollowing,temp->numofFollowers,temp->DateandTime);
        temp=temp->next;
        printf("-------------------------------\n");
    }
}
//overwrite the data inside the both neccessary files.
void OverwriteMyAccount(struct Node **userAccount,char filename[])
{
    FILE *infile;
    infile=fopen(filename,"w");
    if(infile==NULL)
    {
        printf("The file cannnot opened succesfully!");
        exit(0);
    }
    while((*userAccount) != NULL)
    {
        fprintf(infile,"%d %s %d %d %d %s\n",(*userAccount)->uniqueID,(*userAccount)->accName,(*userAccount)->numofPost,(*userAccount)->numofFollowing,(*userAccount)->numofFollowers,(*userAccount)->DateandTime);
        userAccount=&(*userAccount)->next;
    }
}
//menu
void menu()
{
    printf("------------MENU-------------\n");
    printf("1. Add a new Account\n");
    printf("2. Print My Account Info\n");
    printf("3. Search Account\n");
    printf("4. Delete Account\n");
    printf("5. Exit\n");
}
//menu for choose following or follower.
void opMenu()
{
    printf("(1) Add a following account\n");
    printf("(2) Add a follower account\n");
}

//main
int main()
{
    FILE *inFile;
    struct Node **Following,**Followers;
    Followers=(struct Node**)malloc(sizeof(struct Node*));
    Following=(struct Node**)malloc(sizeof(struct Node*));

    char filename1[]="following.txt";
    char filename2[]="followers.txt";
    char nameofACC[25];
    int accID,opSelect,numofPOSTS,numofFOLLOWERS,numofFOLLOWİNGS,opMenuSel;

    *Following=initialiseMyAccount(inFile,filename1);
    printf("The following.txt file has been loaded successfully\n\n");
    *Followers=initialiseMyAccount(inFile,filename2);
    printf("The followers.txt file has been loaded successfully\n\n");

    menu();
    printf("Enter your option:");
    scanf("%d",&opSelect);
    while(opSelect != 5)
    {
        switch(opSelect)
        {
            case 1://Adding account
                currentTime();
                opMenu();
                printf("Enter your option:");
                scanf("%d",&opMenuSel);
                printf("Enter name of the account:");
                scanf("%s",nameofACC);
                printf("Enter number of posts:");
                scanf("%d",&numofPOSTS);            
                printf("Enter number of followers:");
                scanf("%d",&numofFOLLOWERS);
                printf("Enter number of following:");
                scanf("%d",&numofFOLLOWİNGS);
                switch(opMenuSel)
                {
                    case 1://following case.
                        addAccount(Following,nameofACC,numofPOSTS,numofFOLLOWERS,numofFOLLOWİNGS);
                        printf("The account has been added to following list!!\n");
                        break;
                    case 2://followers case.
                        addAccount(Followers,nameofACC,numofPOSTS,numofFOLLOWERS,numofFOLLOWİNGS);
                        printf("The account has been added to follwers list!!\n");
                        break;
                }
                break;
            case 2://prints user account.
                opMenu();
                printf("Enter your option:");
                scanf("%d",&opMenuSel);
                switch(opMenuSel)
                {
                    case 1://prints following.
                        printf("-------My following list------\n");
                        printMyAccount(*Following);
                        break;
                    case 2://printf follower.
                        printf("-------My followers list------\n");
                        printMyAccount(*Followers);
                        break;
                }
                break;
            case 3://this asks to user a name than searches it inside the list
                opMenu();
                printf("Enter your option:");
                scanf("%d",&opMenuSel);
                printf("Enter Account Name:");
                scanf("%s",nameofACC);
                switch(opMenuSel)
                {
                    case 1://following case.
                        searchAccount(Following,nameofACC);
                        break;
                    case 2://followers case.
                        searchAccount(Followers,nameofACC);
                        break;
                }
                break;
            case 4://this case deletes the account with given ID from the user.
                opMenu();
                printf("Enter your option:");
                scanf("%d",&opMenuSel);
                printf("Enter account ID:");
                scanf("%d",&accID);
                switch(opMenuSel)
                {
                    case 1://following case.
                        deleteAccount(Following,accID);
                        break;
                    case 2://followers case.
                        deleteAccount(Followers,accID);
                        break;
                }
                break;
        }
        printf("\n");
        menu();
        printf("Enter your option:");
        scanf("%d",&opSelect);
    }
    printf("Goodbye!!!\n\n");
    printf("The following.txt has been updated successfully\n");
    printf("The follower.txt has been updated successfully\n");
    OverwriteMyAccount(Following,filename1);
    OverwriteMyAccount(Followers,filename2);
    free(Followers);
    free(Following);
    return 0;
}
