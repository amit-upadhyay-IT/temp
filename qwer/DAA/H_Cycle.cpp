#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

void print(int arr[], int n)
{
	int i;
    for (i = 0; i < n; i++)
        printf(" %d --> ", arr[i]+1);
    printf(" %d ", arr[0]+1);
    printf("\n");
}


void nextIndex(int **g, int x[], int k, int n)
{
        if(k>=n)
         return;
	int i,j;
	while(1)
	{
		x[k] = (x[k]+1)%n;
		if(x[k] == 0)
			return ;
		if(g[x[k-1]][x[k]] == 1)
		{
			for(i=0;i<k;i++)
				if(x[i] == x[k])
					break;
			if(i == k)
			{
				if(((k<n-1) ||( (k == n-1)) && (g[x[n-1]][x[0]] == 1)))
					return ;
			}
		}
	}
}


void Cycle(int **g, int n)
{
	int count=0;
	int k=1;
	int *x=(int*)calloc(n,sizeof(int));
	while(k != 0)
	{
	   // printf("\nI am here\n");
		nextIndex(g,x,k,n);
		if(x[k] == 0 || k>=n)
			k--;
		else
		{
			if(k == n-1)
			{
				printf("\n\nsolution number is %d :\n",++count);
				print(x,n);
			}
			k++ ;
		}
	}
	printf("Total number of solutions are %d :\n",count);
}

int main()
{
	int n,**p,ch;
       while(1)
         {
			cout<<"\n\nOptions : \nExit       : 0\nInput      : 1\nFind Cycle : 2\n";
			scanf("%d",&ch);
			switch(ch)
			{
			  	   case 1 :
						int i, u ,v;
						printf("\nEnter No of VERTICES : ");
						scanf("%d",&n);
						while(n<2)
						{
							printf("Wrong Input try again : \n");
							scanf("%d",&n);
						}
						p=(int**)calloc(n,sizeof(int *));
						for(i=0;i<n;i++)
							p[i]=(int *)calloc(n,sizeof(int));
						printf("Enter 0 0 to stop :\n");
						while(1)
						{
							scanf("%d%d",&u,&v);
                            if(u==0&&v==0) break;
                            p[u-1][v-1]=1;
                            p[v-1][u-1]=1;
						}
						break;
				case 2 :
						Cycle(p,n);
						break;
				case 0 :
						return 0;
		}
	}
	return 0;
}
