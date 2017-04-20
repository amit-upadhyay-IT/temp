#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define INF 99999;
using namespace std;

//done
typedef struct node
{
	int **adj;
}node;


//done
node* allocate_memory(node *w,int n)
{
	int i,j;
	w=(node*)calloc(n,sizeof(node));
	for(i=0;i<n;i++)
		w[i].adj=(int**)calloc(n,sizeof(int*));
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			w[i].adj[j]=(int*)calloc(n,sizeof(int));
	return w;
}


void free_memory(node *w,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			free(w[i].adj[j]);
		free(w[i].adj);
	}
	free(w);
}

void printSolution(node *w,int n)
{
	int i,j,k;
	for(k=0;k<n;k++)
	{
		cout<<"\nT : "<<k<<"\n";
	        for(j=0;j<n;j++)
			{   cout<<"\t";
     			for(i=0;i<n;i++)
					printf("%7d ",w[k].adj[j][i]);
			printf("\n\n");
			}
	}
	free_memory(w,n);
}


void war_insert(node *w,int n,int flag)
{
	int r,c,ch;
	cout<<"Enter Start and End Vrtx : \n";
	while(1)
	{
		cin>>r>>c;
		if((r<1 || r>n) || (c<1||c>n))
         cout<<"Wrong Input\n";
		else
        {
		 if(w[0].adj[r-1][c-1]==1)
		 printf("Repeated Entry\n");
		 else
         {
          	w[0].adj[r-1][c-1]=1;
            if(flag==1)
             w[0].adj[c-1][r-1]=1;
         }
		}
 		 printf("\nExit : 0\nMORE : 1\n");
		 cin>>ch;

		 if(ch==0)
         return ;
	}
}
void warSolution(node *w,int n)
{
	int i,j,k;
	for(k=1;k<=n;k++)
	{
		for(j=0;j<n;j++)
		{
			for(i=0;i<n;i++)
			{
				if(w[k-1].adj[i][j]||(w[k-1].adj[i][k-1]&&w[k-1].adj[k-1][j]))
				w[k].adj[i][j]=1;
			}
		}
	}
cout<<"\n\nSolution : \n";
printSolution(w,n);
}
void floyd_insert(node *f,int n,int flag)
{
	int r,c,ch,data,i,j;
	cout<<"Enter Start and End Vrtx : Data \n";
    while(1)
	{
	    cin>>r>>c>>data;
		if(r<1&&r>n||c<1&&c>n || data<0)
          cout<<"Wrong Input\n";
		else
        {
         if(f[0].adj[r-1][c-1]!=0)
		   printf("Repeated Entry\n");
		 else
         {
         	f[0].adj[r-1][c-1]=data;
            if(flag==1)
             f[0].adj[c-1][r-1]=data;
         }
        }
		 printf("\nExit : 0\nMORE : 1\n");
		 cin>>ch;
		 if(ch==0)
          break;
    }

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(f[0].adj[i][j]==0)
			f[0].adj[i][j]=INF;
		}
	}
}
void floydSolution(node *f,int n)
{
	int i,j,k;
	for(k=1;k<=n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(f[k-1].adj[i][j]>(f[k-1].adj[i][k-1]+f[k-1].adj[k-1][j]))
 				 	f[k].adj[i][j]=f[k-1].adj[i][k-1]+f[k-1].adj[k-1][j];
				else
   					f[k].adj[i][j]=f[k-1].adj[i][j];
			}
		}
	}
	printSolution(f,n);
}
int main()
{

int n,ch;
node *w,*f;
	while(1)
	{
		cout<<"\n\nOptions : \nExit      : 0\nWarshall  : 1\nFloyd     : 2\n";
		cin>>ch;
		switch(ch)
		{
            case 0:
                return 0;
			case 1:
					cout<<"\nEnter N : ";
					cin>>n;
					w=allocate_memory(w,n+1);
					cout<<"\nFor Directed Graph   : 0\nFor Undirected Graph : 1\n";
					cin>>ch;
					if(ch==0)
					 war_insert(w,n,0);
					else
                     war_insert(w,n,1);

					warSolution(w,n);
					break;
			case 2:
					cout<<"\nEnter N : ";
					cin>>n;
					f=allocate_memory(f,n+1);
					cout<<"\nFor Directed Graph   : 0\nFor Undirected Graph : 1\n";
					cin>>ch;
					if(ch==0)
					 floyd_insert(f,n,0);
					else
                     floyd_insert(f,n,1);

					floydSolution(f,n);
					break;
		}
	}
return 0;
}
