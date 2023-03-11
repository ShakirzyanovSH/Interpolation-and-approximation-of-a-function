#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

const
	double a = 0;
	double b = 1;
	int n = 11;

double f(double x)
{
	return exp(x)-x;
}

double Factorial(int a) {
    double rs=1;
    int i;
    for(i=1;i<=a;i++) rs *= i;
    return rs;
}

double Uq(int j, double q) {
      int i;
      double rs=1;
      for (i=0;i<=j;i++) rs *= (q-i);
      return rs;
}


double Newton(double t, double x[11], double y[11]) {
    int i,j,k,p;
    double h,q,r;
    double px;
    double dy[11][11];

    h = 0.1;
    for (i=0;i<n-1;i++) dy[0][i] = y[i+1]-y[i];

    for (j=1;j<n;j++) {
    	for (i=0;i<n-j;i++) dy[j][i] = dy[j-1][i+1]-dy[j-1][i];
    }

    q = (t-x[0])/h;
    px = y[0];
    for (j=0;j<n-1;j++) {
        px += Uq(j,q)*dy[j][0]/Factorial(j+1);
    }
    return px;
}

double Lagrange(double t, double x[11], double y[11])
{
	int i,j;
	double px=0;
	double q;

	for(i=0;i<n;i++)
	{
		q=1;
		for(j=0;j<n;j++) if(i!=j) q *= (t-x[j])/(x[i]-x[j]);		
		px += y[i]*q;	
	}		
	return px; 
}


int main()
{
	double x1,x2;
	double Px1, Px2;
	double h=0.1;
	int i;
	double x[n];
	double y[n];

	printf(" Polynomial construction interval [%-4.1lf %-4.1lf] ",a,b);
	printf(" Initial mesh \n");
	printf("    x           y    \n");
	
	for(i=0;i<n;i++)
	{
		x[i] = a + i*h;
		y[i] = f(x[i]);
		printf("   %-6.2lf   %-6.2lf \n",x[i],y[i]);		
	}
	printf("\n Enter point x1 of interpolation: ");
	scanf("%lf",&x1);
	printf(" Enter point x2 of interpolation: ");
	scanf("%lf",&x2);

	Px1 = Lagrange(x1,x,y);
	Px2 = Lagrange(x2,x,y);

	printf("\n 1. Construction of the Lagrange polynomial. \n");

	printf(" Value at points x1 and x2: \n");
	printf(" Ð(õ1) = %lf \n", Px1);
	printf(" Accuracy |P(x1) - f(x1)| = %-4.1e \n",fabs(f(x1)-Px1));
	printf(" Ð(õ2) = %lf \n", Px2);
	printf(" Accuracy |P(x2) - f(x2)| = %-4.1e \n",fabs(f(x2)-Px2));

	Px1 = Newton(x1,x,y);
	Px2 = Newton(x2,x,y);

	printf("\n 2. Construction of the Newton polynomial. \n");
	printf(" Value at points x1 and x2: \n");
	printf(" Ð(õ1) = %lf \n", Px1);
	printf(" Accuracy |P(x1) - f(x1)| = %-4.1e \n",fabs(f(x1)-Px1));
	printf(" Ð(õ2) = %lf \n", Px2);
	printf(" Accuracy |P(x2) - f(x2)| = %-4.1e \n",fabs(f(x2)-Px2));

	getch();
	return 0;
}
