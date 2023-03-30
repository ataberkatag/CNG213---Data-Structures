#include"ass3.h"


struct insideNode *CreateNode(Details inf[ ],int i)
{
    struct insideNode *temp,*head=NULL,*first,*last;
    temp=(struct insideNode*)malloc(sizeof(struct insideNode));
    if (temp==NULL)
    {
        printf("Out of memory!!!");
        exit(1);
    }
    strcpy(temp->name_Photo,inf[i].Nphoto);
    strcpy(temp->dimension_Photo,inf[i].dimPhoto);
    strcpy(temp->size_Photo,inf[i].sPhoto);
    strcpy(temp->city,inf[i].cityN);
    strcpy(temp->Country,inf[i].CountryN);
    temp->year=inf[i].yearP;
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
    return head;
}

AVLTree CreateTree(void)
{
    return NULL;
}

AVLTree MakeEmptyTree(AVLTree t)
{
	if (t != NULL)
	{
		MakeEmptyTree(t->left);
		MakeEmptyTree(t->right);
		free(t);
	}
	return NULL;
}

AVLTree CreateAVLTree(Details inf[], AVLTree t,int i)
{
	int n;
	//printf("BUNUN AQ=%d",i);
	//printf("%s %s %s %s %s %d\n",inf[i].Nphoto,inf[i].dimPhoto,inf[i].sPhoto,inf[i].cityN,inf[i].CountryN,inf[i].yearP);
	if (t == NULL )
	{
		//printf("Control NULL\n");
		/*Create and return a one-node tree */
		t = (AVLTree)malloc(sizeof(struct Node));
		if (t == NULL)
			printf("Out of memory space!!!\n");
		else
		{
			strcpy(t->namePhoto,inf[i].Nphoto);
			strcpy(t->dimension_Photo,inf[i].dimPhoto);
			strcpy(t->size_Photo,inf[i].sPhoto);
			strcpy(t->city,inf[i].cityN);
			strcpy(t->Country,inf[i].CountryN);
			t->year = inf[i].yearP;  t->height = 0; t->size=0;
			t->left = t->right = NULL;
			t->head = (struct insideNode*)malloc(sizeof(struct insideNode));
			t->index = t->head;
			t->index->next = NULL;
			//printf("%s %s %s %s %s %d\n",t->namePhoto,t->dimension_Photo,t->size_Photo,t->city,t->Country,t->year);
		}
	}
	else if (strcmp(inf[i].CountryN,t->Country)<0 )
	{
		//printf("Control left");
		t->left = CreateAVLTree(inf, t->left,i);

		if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2){
		    if (strcmp(inf[i].CountryN,t->Country)<0)
            {
		    	t = SingleRotateWithLeft(t);
            }
		    else
            {
		    	t = DoubleRotateWithLeft(t);
            }
        }
	}
	else if (strcmp(inf[i].CountryN,t->Country)>0 )
	{
		//printf("Control Right");
		t->right = CreateAVLTree(inf, t->right,i);
		if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2){
		    if (strcmp(inf[i].CountryN,t->Country)<0)
            {
			    t = SingleRotateWithRight(t);
            }
		    else
            {
			    t = DoubleRotateWithRight(t);
            }
        }
	}
	else if(strcmp(inf[i].CountryN,t->Country)==0)
	{	
		t->size++;
		t->index->next=CreateNode(inf,i);
		t->index=t->index->next;
	}

	t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
	return t;
}

int TraverseFindMax(AVLTree t)//HElper.this function traverse the tree until it finds the bigger index size
{
    int max=0;
	if (t != NULL)
	{
		TraverseFindMax(t->left);
        if(max<t->size)
        {
            max=t->size;
        }
		TraverseFindMax(t->right);
	}
	return max;
}

void FindSize(AVLTree t,int *size)//This works for finding number of nodes inside the AVLtree
{
    if(t!=NULL)
	{
		*size=*size+t->size+1;
		FindSize(t->right,size);
		FindSize(t->left,size);
	}
}

void storeYears(AVLTree t,int years[4],int *i)//We are taking the year from avltree and store them inside a array
{
	if(t!=NULL)
	{
		storeYears(t->left,years,i);
		if(t->head->next != NULL){
			t->index=t->head->next;
			while(t->index != NULL)
			{
				years[*i]=t->index->year;
				*i=*i+1;
				t->index=t->index->next;
			}
		}
		years[*i]=t->year;
		*i=*i+1;
		storeYears(t->right,years,i);
	}
}

void post_order_traversal(AVLTree t,int num) {//Helper for traversal while searching the tree with max
    if(t != NULL){
        post_order_traversal(t->left,num);
        post_order_traversal(t->right,num);
        if(t->size == num || t->year == num)
        {
			printf("%s %s %s %s %s %d \n",t->namePhoto,t->dimension_Photo,t->size_Photo,t->city,t->Country,t->year);
			if(t->head->next != NULL)
			{
				t->index=t->head->next;
				while(t->index!=NULL)
				{
					printf("%s %s %s %s %s %d\n",t->index->name_Photo,t->index->dimension_Photo,t->index->size_Photo,t->index->city,t->index->Country,t->index->year);
					t->index=t->index->next;
				}
			}
        }
    }
}

void DisplayTree(AVLTree t)
{
	if (t != NULL)
	{
		DisplayTree(t->left);
		printf("%s %s %s %s %s %d \n",t->namePhoto,t->dimension_Photo,t->size_Photo,t->city,t->Country,t->year);
		if(t->head->next != NULL)
		{
			t->index=t->head->next;
			while(t->index!=NULL)
			{
				printf("%s %s %s %s %s %d\n",t->index->name_Photo,t->index->dimension_Photo,t->index->size_Photo,t->index->city,t->index->Country,t->index->year);
				t->index=t->index->next;
			}
		}
		DisplayTree(t->right);
	}
}

int AVLTreeHeight(AVLTree t)
{
	if (t == NULL)
		return -1;
	else
		return t->height;
}

AVLTree SingleRotateWithLeft(AVLTree k2)
{
	AVLTree temp;
	
	temp=k2->left;
	k2->left=temp->right;
	temp->right=k2;
	k2->height=Max(AVLTreeHeight(k2->left),AVLTreeHeight(k2->right))+1;
    temp->height=Max(AVLTreeHeight(temp->left),AVLTreeHeight(temp->right))-1;
	return (temp);	
}

AVLTree SingleRotateWithRight(AVLTree k1)
{
	AVLTree temp;
	
	temp=k1->right;
	k1->right=temp->left;
	temp->left=k1;
	k1->height=Max(AVLTreeHeight(k1->left),AVLTreeHeight(k1->right))+1;
    temp->height=Max(AVLTreeHeight(temp->left),AVLTreeHeight(temp->right))-1;
	return (temp);	
}

AVLTree DoubleRotateWithLeft(AVLTree k3)
{
	k3->left=SingleRotateWithRight(k3->left);
	k3=SingleRotateWithLeft(k3);
	return(k3);
}

AVLTree DoubleRotateWithRight(AVLTree k3)
{
	k3->right=SingleRotateWithLeft(k3->right);
	k3=SingleRotateWithRight(k3);
	return(k3);
}

int Max(int x, int y)
{
	if (x >= y)
		return x;
	else
		return y;
}
