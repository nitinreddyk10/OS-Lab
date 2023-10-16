/*
Write a program where you create 3 threads. Consider two global matrix M1 and M2 of size 3 x 3. Perform addition, subtraction and multiplication in individual thread and store in matrix A[3][3], S[3][3] and M[3][3]. Print the individual matrix values (M1 and M2) and computed matrix of addition, subtraction, multiplication operation in the main function . Once all thread process will be completed, then only main function will execute.
*/

//CS21B2028

#include <pthread.h>
#include <stdio.h>

//Global matrices declaration
int M1[3][3]={{1,1,1},{2,2,2},{3,3,3}};
int M2[3][3]={{1,1,1},{2,2,2},{3,3,3}};

int A[3][3],S[3][3],M[3][3];

//Function to add matrices using thread 1
void *thread_fn_add(void * arg)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
          A[i][j]=M1[i][j]+M2[i][j];
        }
    }
    
    
}
//Function to sub matrices using thread 2
void *thread_fn_sub(void *arg)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
          S[i][j]=M1[i][j]-M2[i][j];
        }
    }
    
}
//Function to mul matrices using thread 3
void *thread_fn_mul(void *arg)
{
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
          M[i][j]=0;
          for(int k=0;k<3;k++)
          {
              M[i][j]+=M1[i][k]*M2[k][j];
          }
        }
    }
    
}
int main()
{
    //creation of threads
    pthread_t ta,tb,tc;
    pthread_create(&ta,NULL,&thread_fn_add,NULL);
    pthread_create(&tb,NULL,&thread_fn_sub,NULL);
    pthread_create(&tc,NULL,&thread_fn_mul,NULL);

 //parent waits until all threads finish execution
   pthread_join(ta,NULL);
   pthread_join(tb,NULL);
   pthread_join(tc,NULL);
   
   
   
   //printing the results
   printf("Matrix  M1:\n");
   for(int i=0;i<3;i++)
   {
       for(int j=0;j<3;j++)
       {
           printf("%d",M1[i][j]);
       }
       printf("\n");
   }
   
    printf("Matrix M2:\n");
   for(int i=0;i<3;i++)
   {
       for(int j=0;j<3;j++)
       {
           printf("%d",M2[i][j]);
       }
       printf("\n");
   }
   
   printf("Additon Matrix :\n");
   for(int i=0;i<3;i++)
   {
       for(int j=0;j<3;j++)
       {
           printf("%d",A[i][j]);
       }
       printf("\n");
   }
   printf("Substraction Matrix :\n");
   for(int i=0;i<3;i++)
   {
       for(int j=0;j<3;j++)
       {
           printf("%d",S[i][j]);
       }
       printf("\n");
   }
   printf("Multiplication Matrix :\n");
   for(int i=0;i<3;i++)
   {
       for(int j=0;j<3;j++)
       {
           printf("%d",M[i][j]);
       }
       printf("\n");
   }
   
return 0;
}