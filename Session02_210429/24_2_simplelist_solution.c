/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct listnode
{
    int data;
    struct listnode *next;
} listnode;

listnode *listnode_new(int data)
{
    listnode *x = malloc(sizeof(listnode));
    x->data = data;
    x->next = NULL;
}

typedef struct list
{
    listnode *head;
    listnode *tail;
} list;

list *list_new(void)
{
    list *x = malloc(sizeof(list));
    printf("created new list\n");
    x->head = NULL;
    x->tail = NULL;
    return x;
}

void list_append(list *x, int data)
{
    listnode *newnode = listnode_new(data);
    if(x->head == NULL)
    {
        x->head = newnode;
        x->tail = newnode;
    }
    else
    {
        x->tail->next = newnode;
        x->tail = newnode;
    }
}

void list_prepend(list *x, int data)
{
    listnode *newnode = listnode_new(data);
    if(x->head == NULL)
    {
        x->head = newnode;
        x->tail = newnode;
    }
    else
    {
        listnode *tmp = x->head;
        x->head = newnode;
        x->head->next = tmp;
    }
}

void list_print(list *x)
{
    listnode* current = x->head;
    while(current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main()
{
    list *mylist = list_new();
    list_append(mylist, 2);
    list_append(mylist, 5);
    list_append(mylist, 6);
    list_append(mylist, 5);
    list_prepend(mylist, 511);
    list_print(mylist);
    
    return 0;
}
