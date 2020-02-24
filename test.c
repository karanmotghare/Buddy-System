#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef struct node
{
   // int lb;
    //int up;
    struct node *next;
}node_type;

typedef struct array
{
    node_type Nnode[11];
}array_list;


void allocate(int s,array_list *ptr);
void initialise_array(array_list *ptr);
void initialise_node(node_type *ptr);
void insert_at_node(node_type *ptr,int lb,int up);
void traverse(node_type *ptr);
int check(node_type *ptr);
void Remove(node_type *lptr);
void divide(node_type *ptr,node_type *lptr);
void create_node(node_type *lptr);

void deallocate(int s,array_list *ptr);
void merge(node_type *ptr,node_type *nptr);

/*void traverse(node_type *ptr)
{
    
    if(ptr!=NULL)
    {
        printf("%d %d\n",ptr->lb,ptr->up);
    }
}*/

void insert_at_node(node_type *ptr,int lb,int up)
{
    node_type *nptr;
    nptr=(node_type*)malloc(sizeof(node_type));
    nptr->next=NULL;
    //nptr->lb=lb;
    //nptr->up=up;
    
    ptr->next=nptr;

    
}

void initialise_node(node_type *ptr)
{
    ptr->next=NULL;
}

void initialise_array(array_list *ptr)
{
    int i=0;

    while (i<10)
    {
        initialise_node(&(ptr->Nnode[i]));
        i++;
    }

    insert_at_node(&(ptr->Nnode[10]),0,1023);
    
}

int check(node_type *ptr)
{
    if(ptr->next==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
}

void Remove(node_type *lptr)
{
    node_type *ptr,*prev;
    if(lptr!=NULL)
    {
        prev=NULL;
        ptr=lptr;
        while (ptr->next!=NULL)
        {
            prev=ptr;
            ptr=ptr->next;
        }
        if(prev!=NULL)
        {
            prev->next=NULL;
        }
        else
        {
            lptr=NULL;
        }
        free(ptr);
        
    }
}

void divide(node_type *ptr,node_type *lptr)
{
    node_type *div;
    div=ptr->next;
    ptr->next=NULL;
    free(div);
    div= (node_type*)malloc(sizeof(node_type)); 
    lptr->next=div;
    div->next=NULL;   
}

void create_node(node_type *lptr)
{
    node_type *nptr,*ptr;
    nptr=(node_type*)malloc(sizeof(node_type));
    nptr->next=NULL;
    ptr=lptr;
    if(lptr->next==NULL)
    {
        lptr->next=nptr;
    }
    else
    {
        while (ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=nptr;
        
    }
    
}

void allocate(int s,array_list *ptr)
{
    int flag=0;
    int count=0;
    int x = (int)ceil(log2(s));
    if(check(&(ptr->Nnode[x]))==1)
    {
        printf("memory allocated\n");
        Remove(&(ptr->Nnode[x]));
    }
    else 
    {
        x++;
        while (flag==0)
        {
            while (check(&(ptr->Nnode[x]))==0 && x<11)
            {
                x++;
                count++;
            }
            
            if(x==11)
            {
                printf("failed to allocate\n");
                flag=1;
            }
            else
            {
                divide(&(ptr->Nnode[x]),&(ptr->Nnode[x-1]));
                x=x-2;
                count--;
                while (count>0)
                {
                    create_node(&(ptr->Nnode[x]));
                    count--;
                    x--;
                }
                printf("memory allocated\n");
                flag=1;
            }   
        }  
    }    
}


void merge(node_type *ptr,node_type *nptr)
{
    node_type *lptr;
    lptr=ptr->next;
    if(lptr==NULL)
    {}
    else
    {
        if(lptr->next==NULL)
        {

        }
        else
        {
        
        lptr=ptr->next;
        ptr->next=NULL;
        free(lptr);
        create_node(nptr);
        }
    }
    
}

void deallocate(int s,array_list *ptr)
{
    int x = (int)ceil(log2(s));
    create_node(&(ptr->Nnode[x]));
    int i=0;
    while (i<10)
    {
        merge(&(ptr->Nnode[i]),&(ptr->Nnode[i+1]));
        i++;
    }
    printf("deallocated\n");
}


void main()
{
    array_list ptr;
    int array_allocation[10];

    initialise_array(&ptr);
    allocate(500,&ptr);
    allocate(40,&ptr);
    allocate(60,&ptr);
    deallocate(500,&ptr);
    deallocate(60,&ptr);
    deallocate(40,&ptr);
    for (int i = 0; i < 11; i++)
    {
        printf("%d\n",ptr.Nnode[i].next);
    }
    

}