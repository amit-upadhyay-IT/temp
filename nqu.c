#include<stdio.h>
#include<stdlib.h>

int k;

int mod(n)
{
    if(n>=0)
        return n;
    else
        return -n;
}

int isplace(int*sol,int k)
{
    int i;

    for(i=0;i<k;i++)
    {
        if((sol[k]==sol[i]) || (mod(k-i)==mod(sol[k]-sol[i])))
            return 0;
    }
    return 1;
}

void print(int*sol,int n)
{
    int k,i,j;

    for(i=0;i<=n;i++)
    {
        k=sol[i];

        for(j=0;j<=n;j++)
        {
                if(j!=k)
                    printf("- ");
                else
                    printf("Q ");
        }
        printf("\n");
    }
}

void recursive(int*sol,int row,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        sol[row]=i;
        if(isplace(sol,row))
        {
            if(row==n-1)
            {
                k++;
                printf("\n%dth sol is::\n",k);
                print(sol,n-1);
                printf("\n");
            }
            else
                recursive(sol,row+1,n);
        }
    }


}

void main()
{
    int n,k;
    int* sol,i,j;
    int ch;
    int row=0;

    printf("no. of queens you want to place\n");
    scanf("%d",&n);
    sol=(int*)malloc(n*sizeof(int));

    for(i=0;i<n;i++)
        sol[i]=-1;

    printf("enter choice::\n1 for iterative\n2 for recursive\n");
    scanf("%d",&ch);
    if(ch==1)
    {

    k=0;
    j=0;

    while(k!=-1)
    {
        sol[k]++;
        if(sol[k]<=n-1)
        {
            if(isplace(sol,k))
            {
                if(k==(n-1))
                {
                    j++;
                    printf("\n%dth sol is::\n",j);
                    print(sol,k);
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
    }


    else
    {
        for(i=0;i<n;i++)
        sol[i]=-1;
        recursive(sol,row,n);
    }




}
