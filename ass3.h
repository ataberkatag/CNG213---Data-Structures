#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1



typedef struct photo Details; 
struct photo//helper Structer
{
    char Nphoto[25];
    char dimPhoto[15];
    char sPhoto[10];
    char cityN[25];
    char CountryN[25];
	int yearP; 
};

struct insideNode
{
    char name_Photo[25];
    char dimension_Photo[15];
    char size_Photo[10];
    char city[25];
    char Country[25];
	int year;
    struct insideNode *next;
};


typedef struct Node *AVLTree;
struct Node
{
    char namePhoto[30];
    char dimension_Photo[15];
    char size_Photo[10];
    char city[25];
    char Country[25];
	int year;
	AVLTree left;
	AVLTree right;
	int height;
    int size;
    struct insideNode *head;
    struct insideNode *index;
};

struct insideNode *CreateNode(Details*,int);
void SearchAVLTree(AVLTree,int);
AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree);
AVLTree CreateAVLTree(Details*, AVLTree, int);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
void DisplayTree(AVLTree);
int AVLTreeHeight(AVLTree);
int TraverseFindMax(AVLTree);
void post_order_traversal(AVLTree,int);
void FindSize(AVLTree,int*);
void storeYears(AVLTree,int *,int *);
int Max(int, int);