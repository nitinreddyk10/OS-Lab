/*
Create parent and child processes using fork(). In each process, define an array of integer using malloc. Before that take the size of the array from the user. Insert values in your array (size and array elements may be different for both processes).

In Parent Process:
(a) Print the array elements and their addresses
(b) Sort the array and print its values.

In Child Process:
(a) Print the array elements and their address
(b) Reverse the array and print its values.
NOTE: Ensure that first child process should terminate, then Parent Process should start taking input.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void printarrinfo(int *arr,int size)
{
    printf("Array elements:\n");
    for(int i=0;i<size;i++)
    {
        printf("Element[%d]: %d\t address:%p\n",i,arr[i],(void*)&arr[i]);
    }
}

void sortarr(int *arr,int size)
{
    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void reversearr(int *arr,int size)
{
    for(int i=0;i<size/2;i++)
    {
        int temp=arr[i];
        arr[i]=arr[size-i-1];
        arr[size-i-1]=temp;
    }
}


int main()
{
    pid_t child_pid = fork();
    if(child_pid == -1)
    {
        perror("Fork Failed");
        return 1;
    }
    
    if(child_pid==0)
    {
        int childsize;
        printf("Enter child array size: ");
        scanf("%d",&childsize);
        
        int *childarr=(int*)malloc(childsize* sizeof(int));
        if(childarr==NULL)
        {
            perror("Memory allocation failed");
            return 1;
        }
        
        printf("Enter %d elements for the child array:\n",childsize);
        for(int i=0;i<childsize;i++)
        {
            scanf("%d",&childarr[i]);
        }
        
        printf("\n Child Process: \n");
        printarrinfo(childarr,childsize);
        
        reversearr(childarr,childsize);
        printf("\nReversed array: \n");
        printarrinfo(childarr,childsize);
        exit(0);
    }
    else
    {
        wait(NULL);
        
        int parentsize;
        printf("Enter parent array size: ");
        scanf("%d",&parentsize);
        
        int *parentarr=(int*)malloc(parentsize* sizeof(int));
        if(parentarr==NULL)
        {
            perror("Memory allocation failed");
            return 1;
        }
        
        printf("Enter %d elements for the parent array:\n",parentsize);
        for(int i=0;i<parentsize;i++)
        {
            scanf("%d",&parentarr[i]);
        }
        
        printf("\n Parent Process: \n");
        printarrinfo(parentarr,parentsize);
        
        sortarr(parentarr,parentsize);
        printf("\nReversed array: \n");
        printarrinfo(parentarr,parentsize);
      
        free(parentarr);
    }
    
    return 0;
}