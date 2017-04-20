#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define INF 999999



using namespace std;


typedef struct node
{
int cost,level,**RCM,ver_no;
struct node *parent;

node()
{
  cost=0;
  level=0;
  RCM=NULL;
  parent=NULL;
  ver_no=0;
}

}node;

typedef struct link_list
{
  node *data;
  struct link_list *next;

  link_list()
  {
   data=NULL;
   next=NULL;
  }
}link_list;



link_list *add_dead(link_list *dead,node *C)
{
  link_list *p;
  p=new link_list;
  p->data=C;
  p->next=dead;
    return p;

}

link_list * add_live(link_list *live,node *C)
{
  int i,j,k;
  link_list *p,*q,*r;
  p=new link_list;
  p->data=C;
  p->next=NULL;

  if(live==NULL)
    return p;
  q=live;
  r=NULL;

  while(q!=NULL)
  {
    if(q->data->cost >= C->cost )
        break;
        r=q;
        q=q->next;
  }

  if(r==NULL)
  {
    p->next=live;
    return p;
  }
  else
  {
    p->next=r->next;
    r->next=p;
    return live;
  }
}

void copy_mat(node *A,int **mat,int no)
{
   int i,j,k,l;
   A->RCM=new int*[no];
   for(i=0;i<no;i++)
    A->RCM[i]=new int[no];

   for(i=0;i<no;i++)
   {
     for(j=0;j<no;j++)
       A->RCM[i][j]=mat[i][j];
   }
}

void init_sol(int *arr,node *A)
{
    while(A!=NULL)
    {
      arr[A->level]=A->ver_no;
      A=A->parent;
    }
}


void print_mat(int **mat,int no)
{
  int i,j;

  for(i=0;i<no;i++)
  {
    for(j=0;j<no;j++)
    {
      if(mat[i][j]==INF)
        printf("  ~  ");
      else
        printf("%5d",mat[i][j]);
    }
        cout<<"\n\n";
  }
}

void CRCM(node *A,int no)
{
  int i,j,k,l,m;
  for(i=0;i<no;i++)
  {
    m=INF;
    for(j=0;j<no;j++)
    {
      if(A->RCM[i][j]<m)
        m=A->RCM[i][j];
    }
    if(m!=0 && m!=INF)
    {
      for(j=0;j<no;j++)
      {
        if(A->RCM[i][j]!=INF)
            A->RCM[i][j]=A->RCM[i][j]-m;
      }
        A->cost=A->cost+m;
    }
  }

  for(i=0;i<no;i++)
  {
    m=INF;
    for(j=0;j<no;j++)
    {
      if(A->RCM[j][i]<m)
        m=A->RCM[j][i];
    }
    if(m!=0 && m!=INF)
    {
      for(j=0;j<no;j++)
      {
        if(A->RCM[j][i]!=INF)
            A->RCM[j][i]=A->RCM[j][i]-m;
      }
        A->cost=A->cost+m;
    }
  }

  printf("C^() : %d\n",A->cost);
  cout<<"\nMatrix : \n";
  print_mat(A->RCM,no);
  cout<<"\n\n";
}

int main()
{
  int i,j,k,l,no,*sol,upper,wt,x,y;
  link_list *live,*dead;
  node *E,*C,*ans;
  upper=INF;
  live=NULL;
  dead=NULL;
  cout<<"\nEnter the Node : ";
  cin>>no;

   sol=new int[no]();

  node *init;
  init=new node;
  init->cost=0;
  init->level=0;
  init->ver_no=0;
  init->parent=NULL;
  init->RCM=new int*[no];
  for(i=0;i<no;i++)
    init->RCM[i]=new int[no]();

  cout<<"\nEnter The Graph : ";
  while(1)
  {
     cout<<"Start  : ";
     cin>>x;
     cout<<"End    : ";
     cin>>y;
     cout<<"Weight  : ";
     cin>>wt;
     init->RCM[x-1][y-1]=wt;
     init->RCM[y-1][x-1]=wt;

     cout<<"\nExit : 0\nMORE : 1\n";
     cin>>i;
     if(i==0)
        break;
  }

  for(i=0;i<no;i++)
  {
    for(j=0;j<no;j++)
        if(init->RCM[i][j]==0) init->RCM[i][j]=INF;
  }

  cout<<"\nEnterd Matrix : \n";
  print_mat(init->RCM,no);
   cout<<"\n\n";
  CRCM(init,no);

  E=init;

  while(1)
  {
    if(E->cost<upper)
    {
      init_sol(sol,E);
      for(i=0;i<no;i++)
      {
         for(j=0;j<=E->level;j++)
         {
           if(sol[j]==i)
            break;
         }

          if(j>E->level && E->RCM[E->ver_no][i]<INF)
          {
            C=new node;
            C->level=E->level+1;
            C->parent=E;
            C->ver_no=i;
            copy_mat(C,E->RCM,no);
            C->cost=E->cost+E->RCM[E->ver_no][i];

            for(j=0;j<no;j++)
            {
              C->RCM[E->ver_no][j]=INF;
              C->RCM[j][i]=INF;
            }

            C->RCM[i][0]=INF;

            CRCM(C,no);

            if(C->level==no-1 && init->RCM[i][0])
            {
               if(upper>C->cost)
               {
                 ans=C;
                 upper=C->cost;
               }
            }
            else
                live=add_live(live,C);
         }
       }
       dead=add_dead(dead,E);
     }

    if(live==NULL)
        break;
    else
    {
      E=live->data;
      live=live->next;
    }
  }

if(ans!=NULL)
{
    init_sol(sol,ans);
    cout<<"\nSolution Present :\n";
    cout<<"Cost of ans node : "<<ans->cost<<"\npath :    ";

	for(i=0;i<no;i++)
        printf("%d->",sol[i]+1);
        cout<<"1\n\n";
}
else
    cout<<"\nNo Solution Present \n";

return 0;
}
