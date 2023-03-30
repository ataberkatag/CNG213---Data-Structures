//I did this assignment in the vscode because i am using mac.
#include"ass3.c"

AVLTree readData(char**);
AVLTree insertPhoto(AVLTree,Details*,int);
void displayIndex(AVLTree);
void popularCountry(AVLTree);
void popularYear(AVLTree);
void menu();

int main(int argv,char *argc[])
{
    AVLTree t;
    int opSelect;
    t=readData(argc);
    menu();
    printf("Option:");
    scanf("%d",&opSelect);
    while(opSelect!=4)
    {
        switch(opSelect)
        {
            case 1://Display Tree
                displayIndex(t);
                break;
            case 2://Popular Country
                popularCountry(t);
                break;
            case 3://Popular Year
                popularYear(t);
                break;
            case 4://Exit
                break;
        }
        menu();
        printf("Option:");
        scanf("%d",&opSelect);
    }
}

void menu()
{
    printf("1. Display the full index of photos\n");
    printf("2. Display the photos of popular country\n");
    printf("3. Display the photos of popular year\n");
    printf("4. Exit\n");
}

AVLTree readData(char *input[])//Takes file name and reads data
{
    FILE *inFile;
    char *filename=input[1];
    
    inFile=fopen(filename,"r");
    if(inFile==NULL)
    {
        printf("The file cannot opened succesfully");
        exit(0);
    }

    char getch;
    int count=0;
    getch=getc(inFile);
    while(getch != EOF)
    {
        if(getch == '\n')
        {
            count = count + 1;
        }
        getch=getc(inFile);
    }
    rewind(inFile);

    Details inf[count+1];
    int i;
    char token[7];
    for(i=0;i<count+1;i++)
    {
        fscanf(inFile,"%[^,] %c %[^,] %c %[^,] %c %[^,] %c %[^,] %c %d",inf[i].Nphoto,token,inf[i].dimPhoto,token,inf[i].sPhoto,token,inf[i].cityN,token,inf[i].CountryN,token,&inf[i].yearP);
    }
    fclose(inFile);
    AVLTree photos_T;
    photos_T=CreateTree();
    photos_T=insertPhoto(photos_T,inf,count+1);

    return photos_T;
}

AVLTree insertPhoto(AVLTree Photos,Details inf[],int count)
{
    int i=0;
    for(i=0;i<count;i++){
        Photos=CreateAVLTree(inf,Photos,i);
    }
    return Photos;
}

void displayIndex(AVLTree t)
{
    DisplayTree(t);
}

void popularCountry(AVLTree t)//This function less complex than popular year because it just compare the sizes.
{
    AVLTree temp = t ;
    int max=0;
    if (temp==NULL)
        printf("\nError allocation");

    max=TraverseFindMax(temp);
    post_order_traversal(temp,max);
}

//This function more complex than popularCountry.It has lots of loops and helper functions.
//Because this function have to find all years inside the Avltree.This function have to compare all the years (include index nodes).
void popularYear(AVLTree t)
{
    int size_T=0,year=0,number=0,hold,maxYear;

    FindSize(t,&size_T);

    int year_A[size_T],i=0;

    storeYears(t,year_A,&i);

    int j=0;

    for(i=0;i<size_T;i++)
    {
        for(j=0;j<size_T;j++)
        {
            if(year_A[i]==year_A[j])
            {
                number=number+1;
            }
        }
        if(year<number)
        {
            year=number;
            hold=i;
        }
        number=0;
    }
    maxYear=year_A[hold];
    post_order_traversal(t,maxYear);
}

