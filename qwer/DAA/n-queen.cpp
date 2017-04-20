#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int abs(int n)
{
    return n>0 ? n:-n;
}
int isplace(int *sol, int k)
{
    for(int i=0;i<k;i++)
    {
        if(sol[k]==sol[i] || abs(k-i)==abs(sol[k]-sol[i]))
            return 0;
    }
    return 1;
}
void print(int *sol,int n)
{
    int i,j;
    printf("\nSolution :\n");
    for(i=0;i<n;i++)
        printf(" ---");
    printf("\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(j==sol[i])
                printf("|.Q.");
            else
                printf("|   ");
            if(j==n-1)
                printf("|");
        }
        printf("\n");
        for(j=0;j<n;j++)
            printf(" ---");
        printf("\n");
    }
}

void queenR(int*sol,int row,int n ,int*c)
{
    int i;

    for(i=0;i<n;i++)
    {
       sol[row]=i;

       if(isplace(sol,row))
       {
           if(row==n-1)
           {
               print(sol,n);
               *c=*c+1;
           }

           else
                queenR(sol,row+1,n,c);
       }
    }
//    return k;
}

int queenI(int *sol,int n)
{
    int j,k;
    j=0;k=0;
    while(k!=-1)
    {
    	sol[k]++;
        if(sol[k]<n)
        {
            if(isplace(sol,k))
            {
                if(k==n-1)
                {
                    print(sol,n);
                    j++;
                }
                else
                    k++;
            }
        }
        else
        {
            sol[k]=-1;
            k--;
        }
	}
    return j;
}
int main()
{
    int *sol,n,i,j,k,ch,count;
    int* c;
    *c=0;
    while(1)
    {
        printf("\n\nEnter Size of chess Board : Enter -1 to Exit :\t");
        scanf("%d",&n);
        if(n==-1) return 0;
        sol=(int*)malloc(n*sizeof(int));
        for(i=0;i<n;i++)
            sol[i]=-1;
        printf("Enter Choice :\n0. Exit\n1. Iterative\n2. Recursive\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 0:
            return 0;
        case 1:
            count=queenI(sol,n);
            printf("Total No. of Solutions : %d",count);
            break;
        case 2:
            queenR(sol,0,n,c);
            printf("Total No. of Solutions : %d",*c);
            break;
        default :
            printf("\nEnter VALID choice\n");
        }
    }
    return 0;
}
