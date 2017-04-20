#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>


int *allocate(int *x,int n)
{
    x=(int *)calloc(n*n,sizeof(int));
    return x;
}

int *enter_matrix(int *x,int n,int size_new)
{
    //x=(int *)calloc(n*n,sizeof(int));
    for(int i=0 ; i<n ; i++)
        for(int j=0 ; j<n ; j++)
            scanf("%d",&x[i*size_new+j]);
    return x;
}

int *traditional_mult(int *x,int *y,int *z,int n)
{
    z=(int *)calloc(n*n,sizeof(int));
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            z[i*n+j]=0;
            for(int k=0 ; k<n ; k++)
            {
                z[i*n+j]+=( x[i*n+k] ) * ( y[k*n+j] );
            }
        }
    }
    return z;
}

void add(int *x,int *y,int *z,int n)
{
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            z[i*n+j] = x[i*n+j] + y[i*n+j];
        }
    }
}

void sub(int *x,int *y,int *z,int n)
{
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            z[i*n+j] = x[i*n+j] - y[i*n+j];
        }
    }
}


void strassen(int *x,int *y,int *z,int n)
{

    if(n==1)
    {
        z[0]=x[0]*y[0];
        return;
    }

    int size=n/2;
    int *a11=allocate(a11,size);       int *a12=allocate(a12,size);       int *a21=allocate(a21,size);       int *a22=allocate(a22,size);
    int *b11=allocate(b11,size);       int *b12=allocate(b12,size);       int *b21=allocate(b21,size);       int *b22=allocate(b22,size);
    int *c11=allocate(c11,size);       int *c12=allocate(c12,size);       int *c21=allocate(c21,size);       int *c22=allocate(c22,size);
    int *p1=allocate(p1,size);         int *p2=allocate(p2,size);         int *p3=allocate(p3,size);         int *p4=allocate(p4,size);
    int *p5=allocate(p5,size);         int *p6=allocate(p6,size);         int *p7=allocate(p7,size);

    int *temp1=allocate(temp1,size);
    int *temp2=allocate(temp2,size);

    for(int i=0 ; i<size; i++)
    {
        for(int j=0 ; j<size ; j++)
        {
            a11[i*size+j]=x[i*n+j];
            a12[i*size+j]=x[i*n+j+size];
            a21[i*size+j]=x[(i+size)*n+j];
            a22[i*size+j]=x[(i+size)*n+j+size];
            b11[i*size+j]=y[i*n+j];
            b12[i*size+j]=y[i*n+j+size];
            b21[i*size+j]=y[(i+size)*n+j];
            b22[i*size+j]=y[(i+size)*n+j+size];
        }
    }

    add(a11, a22, temp1, size);	// a11 + a22
	add(b11, b22, temp2, size);	// b11 + b22
	strassen(temp1, temp2, p1, size);		// p1 = (a11+a22) * (b11+b22)
	add(a21, a22, temp1, size);	// a21 + a22
	strassen(temp1, b11, p2, size);			// p2 = (a21+a22) * (b11)
	sub(b12, b22, temp2, size); 	// b12 - b22
	strassen(a11, temp2, p3, size);			// p3 = (a11) * (b12 - b22)
	sub(b21, b11, temp2, size); 	// b21 - b11
	strassen(a22, temp2, p4, size);			// p4 = (a22) * (b21 - b11)
	add(a11, a12, temp1, size);	// a11 + a12
	strassen(temp1, b22, p5, size);			// p5 = (a11+a12) * (b22)
	sub(a21, a11, temp1, size); 	// a21 - a11
	add(b11, b12, temp2, size);	// b11 + b12
	strassen(temp1, temp2, p6, size);		// p6 = (a21-a11) * (b11+b12)
	sub(a12, a22, temp1, size); 	// a12 - a22
	add(b21, b22, temp2, size);	// b21 + b22
	strassen(temp1, temp2, p7, size);		// p7 = (a12-a22) * (b21+b22)
	add(p3, p5, c12, size);			// c12 = p3 + p5
	add(p2, p4, c21, size);			// c21 = p2 + p4
	add(p1, p4, temp1, size);		// p1 + p4
	add(temp1, p7, temp2, size);// p1 + p4 + p7
	sub(temp2, p5, c11, size);	// c11 = p1 + p4 - p5 + p7
	add(p1, p3, temp1, size);		// p1 + p3
	add(temp1, p6, temp2, size);// p1 + p3 + p6
	sub(temp2, p2, c22, size);


    for(int i=0 ; i<size ; i++)
    {
        for(int j=0 ; j<size ; j++)
        {
            z[i*n+j]=c11[i*size+j];
            z[i*n+j+size]=c12[i*size+j];
            z[(i+size)*n+j]=c21[i*size+j];
            z[(i+size)*n+j+size]=c22[i*size+j];
        }
    }

    free(a11); free(a12); free(a21); free(a22);
	free(b11); free(b12); free(b21); free(b22);
	free(c11); free(c12); free(c21); free(c22);
	free(p1); free(p2); free(p3); free(p4);
	free(p5); free(p6); free(p7); free(temp1);
	free(temp2);

}

void display(int *x,int n,int size_new)
{
    for(int i=0 ; i<n; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            printf("%d\t",x[i*size_new+j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    int size_new=0;
    char ch;
    int *x,*y,*z;
    x=NULL;
    y=NULL;
    z=NULL;

    do
    {
        printf("***** MENU *****\n");
        printf("1.Enter Matrix\n2.Display\n3.Traditional Multiplication\n4.Strassen's Multiplication\n0.Exit\n");
        printf("Your Choice: ");
        scanf(" %c",&ch);
        switch(ch)
        {
            case '1' :  free(x);
                        free(y);
                        free(z);
                        printf("Enter matrix size: ");
                        scanf("%d",&n);
                        size_new=(ceil(log2(n)));
                        size_new=(1 << size_new);
                        //printf("sixenew= %d\n",size_new);
                        x=allocate(x,size_new);
                        y=allocate(y,size_new);
                        z=allocate(z,size_new);
                        printf("Enter Matrix A: \n");
                        x=enter_matrix(x,n,size_new);
                        printf("Enter Matrix B: \n");
                        y=enter_matrix(y,n,size_new);
                        break;

            case '2' :  printf("Matrix A:\n");
                        display(x,n,size_new);
                        printf("Matrix B:\n");
                        display(y,n,size_new);
                        break;

            case '3' :  printf("Matrix A:\n");
                        display(x,n,size_new);
                        printf("Matrix B:\n");
                        display(y,n,size_new);
                        printf("Traditional:\n");
                        z=traditional_mult(x,y,z,size_new);
                        display(z,n,size_new);
                        break;

            case '4' :  printf("Matrix A:\n");
                        display(x,n,size_new);
                        printf("Matrix B:\n");
                        display(y,n,size_new);
                        printf("Strassen's:\n");
                        strassen(x,y,z,size_new);
                        display(z,n,size_new);
                        break;

            case '0' :  break;
        }

    }while(ch!='0');

}





