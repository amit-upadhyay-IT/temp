#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<malloc.h>
using namespace std;
typedef struct inputlist
{
    int freq;
    char name;
}inputlist;
typedef struct huffman
{
    int freq;
    char name;
    huffman *lc,*rc;
}huffman;
typedef struct sortlist
{
    int freq;
    int flag;
    union opt
    {
        char name;
        huffman *add;
    }opt;
    sortlist *next;
}sortlist;
typedef struct encodestr
{
    char name;
    char encode[100];
}encodestr;
sortlist *update (sortlist *p)
{
    if(p==NULL)
        return NULL;
    sortlist *q,*r,*head;
    q=p->next;
    head=q;
    p->next=NULL;
    r=NULL;
    while(q!=NULL && p->freq > q->freq)
    {
        r=q;
        q=q->next;
    }
    if(r==NULL)
    {
        p->next=head;
        return p;
    }
    else
    {
        p->next=r->next;
        r->next=p;
        return head;
    }
}
int tabcount=0;
void preorder(huffman *p,int b, char *temp, encodestr *table)
{
    if (p==NULL)
        return;
    temp[b]='\0';
    if(p->lc==NULL && p->rc==NULL)
    {
        table[tabcount].name=p->name;
        strcpy(table[tabcount].encode,temp);
        tabcount++;
    }
    temp[b]='0';
    preorder(p->lc,b+1,temp,table);
    temp[b]='1';
    preorder(p->rc,b+1,temp,table);
    return;
}
void encoding(huffman *head, int n)
{
    int i;
    char str[100];
    printf("\nEnter The String :\t");
    fflush(stdin);
    scanf("%s",str);
    encodestr *table;
    table=(encodestr*)malloc(n*sizeof(encodestr));
    for(i=0;i<n;i++)
        table[i].encode[0]='\0';
    char temp[100];
    tabcount=0;
    preorder(head,0,temp,table);
    for(i=0;i<n;i++)
        //cout<<table[i].name<<" : "<<table[i].encode<<"\n";
        printf("%c : %s\n",table[i].name,table[i].encode);
    char encode[500];
    encode[0]='\0';
    int j,k;
    k=0;char ch;
    while(str[k]!='\n' && str[k]!='\0')
    {
        ch=str[k];
        for(i=0;i<n;i++)
        {
            if(table[i].name==ch)
            {
                strcat(encode,table[i].encode);
                break;
            }
        }
        if(i>=n)
        {
            printf("\n\n*****ERROR : Wrong String Entered*****\n\n");
            return;
        }
        k++;
    }
    printf("\n\n%s : %s",str,encode);
    return;
}
huffman *createtree(sortlist *list)
{
    huffman *rc, *lc, *p;
    p=lc=rc=NULL;
    int total;

    while(list!=NULL)
    {
        total=0;

        if(list->next==NULL)
        {
            return list->opt.add;
        }

        if(list->flag==0)
        {
            lc=(huffman*)malloc(sizeof(huffman));
            lc->freq=list->freq;
            lc->name=list->opt.name;
            lc->lc=NULL;
            lc->rc=NULL;
            total=list->freq;
        }
        else
        {
            lc=list->opt.add;
            total=list->freq;
        }
        list=list->next;

        if(list->flag==0)
        {
            rc=(huffman*)malloc(sizeof(huffman));
            rc->freq=list->freq;
            rc->name=list->opt.name;
            rc->lc=NULL;
            rc->rc=NULL;
            total=total+list->freq;
        }
        else
        {
            rc=list->opt.add;
            total=total+list->freq;
        }
        p=(huffman*)malloc(sizeof(huffman));
        p->freq=total;
        p->lc=lc;
        p->rc=rc;
        p->name=' ';

        list->freq=total;
        list->flag=1;
        list->opt.add=p;
        list=update(list);
    }
    return NULL;
}
void showtree(huffman *head)
{
    if(head==NULL)
        return;
    showtree(head->lc);
    printf("%d,%c\n",head->freq,head->name);
    showtree(head->rc);
    return;
}
void merge(inputlist *arr, int s, int m, int l)
{
    inputlist *temp;
    temp=(inputlist*)malloc((l-s+2)*sizeof(inputlist));
    int i,j,k;
    i=s;j=m+1;
    k=0;
    while(i<=m && j<=l)
    {
        if(arr[i].freq<=arr[j].freq)
        {
            temp[k]=arr[i];
            i++;k++;
        }
        else
        {
            temp[k]=arr[j];
            j++;k++;
        }
    }
    while(i<=m)
    {
        temp[k]=arr[i];
        i++;k++;
    }
    while(j<=l)
    {
        temp[k]=arr[j];
        j++;k++;
    }
    for(i=0;i<k;i++)
        arr[s+i]=temp[i];
    delete(temp);
    return;
}
void mergesort(inputlist *arr, int s, int l)
{
    if(l-s<=0)
        return;
    int m=s+(l-s)/2;
    mergesort(arr,s,m);
    mergesort(arr,m+1,l);
    merge(arr,s,m,l);
    return;
}
void traversal(char *temp, huffman *p)
{
    if(p->lc==NULL && p->rc==NULL)
    {
        printf("%c",p->name);
        return;
    }
    if(temp[tabcount]=='0')
    {
        tabcount++;
        traversal(temp,p->lc);
    }
    else
    {
        if(temp[tabcount]=='1')
        {
            tabcount++;
            traversal(temp,p->rc);
        }
        else
        {
            printf("\n\n*****ERROR : Invalid Input\n\n");
            return;
        }
    }
}
void decoding(huffman *head)
{
    tabcount =0;
    char *temp;
    temp=new char[100];
    printf("\n\nEnter Encoded String to be decoded :\t");
    scanf("%s",temp);
    printf("\n\n%s :\t",temp);
    while(temp[tabcount]=='0' || temp[tabcount]=='1')
        traversal(temp,head);
}
int main()
{
    int i,j,n;
    inputlist *inputarray;
    printf("\nEnter the no of students :\t");
    scanf("%d",&n);

    inputarray=(inputlist*)malloc(n*sizeof(inputlist));

    printf("\nEnter data of %d Students :",n);
    for(i=0;i<n;i++)
    {
        printf("\n\nData of %d Student :\n",i+1);
        printf("Name :\t",i+1);
        getchar();
        scanf("%c",&inputarray[i].name);
        printf("Freq :\t",i+1);
        scanf("%d",&inputarray[i].freq);
    }
    printf("\n\n*****Before*****\n\n");
    for(i=0;i<n;i++)
    {
        printf("\n\nName :\t%c",inputarray[i].name);
        printf("\nFreq :\t%d",inputarray[i].freq);
    }
    mergesort(inputarray,0,n-1);
    printf("\n\n*****After*****\n\n");
    for(i=0;i<n;i++)
    {
        printf("\n\nName :\t%c",inputarray[i].name);
        printf("\nFreq :\t%d",inputarray[i].freq);
    }

    sortlist *temp,*listhead,*p;
    temp=listhead=NULL;

    for(i=0;i<n;i++)
    {
        temp = (sortlist*)malloc(sizeof(sortlist));
        temp->freq=inputarray[i].freq;
        temp->flag=0;
        temp->opt.name=inputarray[i].name;
        temp->next=NULL;

        if(listhead==NULL)
        {
            listhead=temp;
            p=temp;
        }
        else
        {
            p->next=temp;
            p=temp;
        }
    }
    huffman *head;
    head=NULL;
    head=createtree(listhead);
    printf("\n\n");
    showtree(head);
    int ch;
    while(1)
    {
        printf("\n\n\n0. EXIT\n1. ENCODING\n2. DECODING\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 0:
            return 0;
        case 1:
            encoding(head,n);
            break;
        case 2:
            decoding(head);
            break;
        default:
            printf("Enter VALID Choice");
            break;
        }
    }
    return 0;
}
