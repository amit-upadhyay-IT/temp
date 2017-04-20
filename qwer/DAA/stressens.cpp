#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<process.h>
int * GetMemory(int n)
{
    return (int*)calloc((n*n),sizeof(int));
}
void input(int *matrix,int n,int sizeofstressens)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",matrix+i*sizeofstressens+j);
        }
    }
}
void Addition(int *MatrixA,int *MatrixB,int *MatrixC,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            MatrixC[i*n+j]=MatrixA[i*n+j]+MatrixB[i*n+j];
        }
    }
}
void Substraction(int *MatrixA,int *MatrixB,int *MatrixC,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            MatrixC[i*n+j]=MatrixA[i*n+j]-MatrixB[i*n+j];
        }
    }
}
void output(int *matrix,int n,int sizeofstressens)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%4d",*(matrix+i*sizeofstressens+j));
        }
        printf("\n");
    }
}
void Strassen(int *a,int *b,int *c,int size)
{
    if(size==1)
    {
        c[0]=a[0]*b[0];
        return;
    }
    int n=size/2;
    int *a11=GetMemory(n),*a12=GetMemory(n),*a21=GetMemory(n),*a22=GetMemory(n);
    int *c11=GetMemory(n),*c12=GetMemory(n),*c21=GetMemory(n),*c22=GetMemory(n);
    int *b11=GetMemory(n),*b12=GetMemory(n),*b21=GetMemory(n),*b22=GetMemory(n);
    int *p1=GetMemory(n),*p2=GetMemory(n),*p3=GetMemory(n),*p4=GetMemory(n),*p5=GetMemory(n),*p6=GetMemory(n),*p7=GetMemory(n);
    int *IntermediateA=GetMemory(n);
    int *IntermediateB=GetMemory(n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            a11[i*n + j] = a[i*size + j];
            a12[i*n + j] = a[i*size + j + n];
            a21[i*n + j] = a[(i+n)*size + j];
            a22[i*n + j] = a[(i+n)*size + j + n];
            b11[i*n + j] = b[i*size + j];
            b12[i*n + j] = b[i*size + j + n];
            b21[i*n + j] = b[(i+n)*size + j];
            b22[i*n + j] = b[(i+n)*size + j + n];
        }
    }

    Addition(a11, a22, IntermediateA, n);               //a11+a22
    Addition(b11, b22, IntermediateB, n);               //b11+b22
    Strassen(IntermediateA, IntermediateB, p1, n);      //p1=(a11+a22)*(b11+b22)
    Addition(a21, a22, IntermediateA, n);               //a21+a22
    Strassen(IntermediateA, b11, p2, n);                //p2=(a21+a22)*b11
    Substraction(b12, b22, IntermediateB, n);           //(b12-b22)
    Strassen(a11, IntermediateB, p3, n);                //p3=a11*(b12-b22)
    Substraction(b21, b11, IntermediateA, n);           //(b21-b11)
    Strassen(a22, IntermediateA, p4, n);                //p4=a22*(b21-b11)
    Addition(a11, a12, IntermediateA, n);               //a11+a12
    Strassen(b22, IntermediateA, p5, n);                //p5=b22*(a11+a12)
    Substraction(a21, a11, IntermediateA, n);           //a21-a11
    Addition(b11, b12, IntermediateB,n);                //b11+b12
    Strassen(IntermediateA, IntermediateB, p6, n);      //p6=(a21-a11)*(b11+b12)
    Substraction(a12, a22, IntermediateA, n);           //a12-a22
    Addition(b21, b22, IntermediateB, n);               //b21+b22
    Strassen(IntermediateA, IntermediateB, p7, n);      //p7=(a12-a22)*(b21+b22)


    Addition(p3, p5, c12, n);                           //c12=p3+p5
    Addition(p2, p4, c21, n);                           //c21=p2+p4
    Addition(p1, p4, IntermediateA,n);                  //p1+p4
    Addition(IntermediateA, p7, IntermediateB, n);      //p1+p4+p7
    Substraction(IntermediateB, p5, c11, n);            //c11=p1+p4-p5+p7
    Addition(p1, p3, IntermediateA, n);                 //p1+p3
    Addition(IntermediateA, p6, IntermediateB, n);      //p1+p3+p6
    Substraction(IntermediateB, p2, c22, n);            //c22=p1+p3-p2+p6

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            c[i*size+j]=c11[i*n+j];
            c[i*size+j+n]=c12[i*n+j];
            c[(i+n)*size+j]=c21[i*n+j];
            c[(i+n)*size+j+n]=c22[i*n+j];
        }
    }
    free(a11);free(a22);free(a21);free(a12);
    free(b11);free(b22);free(b21);free(b12);
    free(c11);free(c22);free(c21);free(c12);
    free(p1);free(p2);free(p3);free(p4);free(p5);free(p6);free(p7);
    free(IntermediateA);free(IntermediateB);
}
void Multiply(int *MatrixA,int *MatrixB,int *MatrixC,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                MatrixC[i*n+j] += MatrixA[i*n+k] * MatrixB[k*n+j];
            }
        }
    }
}
int *Free(int *matrix)
{
    if (matrix!=NULL)
        free(matrix);
    return NULL;
}
int main()
{
    int n=0,sizeofstressens=0;
    int *MatrixA=NULL,*MatrixB=NULL,*MatrixC=NULL;
    while(1)
    {
        printf("\nEnter your Choice :\n0. Exit\n1. Enter Matrices\n2. Display Matrices\n3. Brute Multiplication\n4. Stressens Multiplication\n");
        int ch;
        scanf("%d",&ch);
        system("cls");
        switch(ch)
        {
        case 0:
            return 0;
        case 1:
            MatrixA=Free(MatrixA);
            MatrixB=Free(MatrixB);

            int n;
            printf("\nEnter Size of 2-D Array :\t");
            scanf("%d",&n);
            if(n>0)
            {
                sizeofstressens=(ceil(log2(n)));
                sizeofstressens=(1<<sizeofstressens);

                MatrixA=GetMemory(sizeofstressens);
                MatrixB=GetMemory(sizeofstressens);

                printf("\nEnter Matrix A :\n");
                input(MatrixA,n,sizeofstressens);
                printf("\nEnter Matrix B :\n");
                input(MatrixB,n,sizeofstressens);
            }
            else
                printf("\nEnter Valid Size\n");
            break;
        case 2:
            if(n>0)
            {
                printf("\nMatrix A :\n");
                output(MatrixA,n,sizeofstressens);
                printf("\nMatrix B :\n");
                output(MatrixB,n,sizeofstressens);
            }
            else
                printf("\nEnter Valid Size\n");
            break;
        case 3:
            if(n>0)
            {
                MatrixC=GetMemory(sizeofstressens);
                Multiply(MatrixA,MatrixB,MatrixC,sizeofstressens);
                printf("\nMatrix A :\n");
                output(MatrixA,n,sizeofstressens);
                printf("\nMatrix B :\n");
                output(MatrixB,n,sizeofstressens);
                printf("\nMatrix C :\n");
                output(MatrixC,n,sizeofstressens);
                MatrixC=Free(MatrixC);
            }
            else
                printf("\nEnter Valid Size\n");
            break;
        case 4:
            if(n>0)
            {
                MatrixC=GetMemory(sizeofstressens);
                Strassen(MatrixA,MatrixB,MatrixC,sizeofstressens);
                printf("\nMatrix A :\n");
                output(MatrixA,n,sizeofstressens);
                printf("\nMatrix B :\n");
                output(MatrixB,n,sizeofstressens);
                printf("\nMatrix C : Stressens :\n");
                output(MatrixC,n,sizeofstressens);
                MatrixC=Free(MatrixC);
            }
            else
                printf("\nEnter Valid Size\n");
            break;
        default :
            printf("\nINVALID CHOICE\n");
            break;
        }
    }
    MatrixA = Free(MatrixA);
	MatrixB = Free(MatrixB);
	return 0;
}
