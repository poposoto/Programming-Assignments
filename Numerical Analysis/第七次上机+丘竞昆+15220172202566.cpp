#include <stdio.h>
#include <math.h>

void newton(auto f, auto fp, double x0, double e1, double e2, double delta, int m)
{
	int k = 0;
	double f0 = f(x0), fp0 = fp(x0);
	double x1, f1, fp1;
	
	n2:
		x1 = x0 - f0 / fp0;
		f1 = f(x1);
		fp1 = fp(x1);
	
	n3:
		if (fabs(f1) < e1) goto n7;
		else goto n4;
	
	n4:
		if (fabs(x1) < delta) goto n5;
		else goto n6;
	
	n5:
		if (fabs(x1 - x0) < e2) goto n7;
		else goto n8;
	
	n6:
		if (fabs(x1 - x0) / fabs(x1) < e2) goto n7;
		else goto n8;
	
	n7:
		printf("NEWTON METHOD COMPUTATION SUCCEEDED, x* = %.16f, k = %d\n", x1 , k);
		goto end;
	
	n8:
		if (k == m) printf("NEWTON METHOD COMPUTATION FAILED\n");
		else {
			x0 = x1;
			f0 = f1;
			fp0 = fp1;
			k = k + 1;
			goto n2;
		}
	
	end:
		;
}

void steffensen(auto f, double x0, double e1, double e2, double delta, int m)
{
	int k = 0;
	double f0 = f(x0), ft0 = f(x0 + f0);
	double x1, f1, ft1;
	
	n2:
		x1 = x0 - f0 * f0 / (ft0 - f0);
		f1 = f(x1);
		ft1 = f(x1 + f1);
	
	n3:
		if (fabs(f1) < e1) goto n7;
		else goto n4;
	
	n4:
		if (fabs(x1) < delta) goto n5;
		else goto n6;
	
	n5:
		if (fabs(x1 - x0) < e2) goto n7;
		else goto n8;
	
	n6:
		if (fabs(x1 - x0) / fabs(x1) < e2) goto n7;
		else goto n8;
	
	n7:
		printf("STEFFENSEN METHOD COMPUTATION SUCCEEDED, x* = %.16f, k = %d\n", x1 , k);
		goto end;
	
	n8:
		if (k == m) printf("STEFFENSEN METHOD COMPUTATION FAILED\n");
		else {
			x0 = x1;
			f0 = f1;
			ft0 = ft1;
			k = k + 1;
			goto n2;
		}
	
	end:
		;
}

void secant(auto f, double x0, double x1, double e1, double e2, double delta, int m)
{
	int k = 0;
	double f0 = f(x0), f1 = f(x1);
	double x2, f2;
	
	n2:
		x2 = x1 - (x1 - x0) / (f1 - f0) * f1;
		f2 = f(x2);
	
	n3:
		if (fabs(f2) < e1) goto n7;
		else goto n4;
	
	n4:
		if (fabs(x2) < delta) goto n5;
		else goto n6;
	
	n5:
		if (fabs(x2 - x1) < e2) goto n7;
		else goto n8;
	
	n6:
		if (fabs(x2 - x1) / fabs(x2) < e2) goto n7;
		else goto n8;
	
	n7:
		printf("SECANT METHOD COMPUTATION SUCCEEDED, x* = %.16f, k = %d\n", x2 , k);
		goto end;
	
	n8:
		if (k == m) printf("SECANT METHOD COMPUTATION FAILED\n");
		else {
			x0 = x1;
			x1 = x2;
			f0 = f1;
			f1 = f2;
			k = k + 1;
			goto n2;
		}
	
	end:
		;
}

int main(int argc, char *argv[])
{
	auto function = [](double x)->double{ return x*x*x*x*x - 18 * x*x*x*x + 122 * x*x*x - 380 * x*x + 525 * x - 250; };
	auto derivative = [](double x)->double{ return 5 * x*x*x*x - 72 * x*x*x + 366 * x*x - 760 * x + 525; };
	newton(function, derivative, 0.5, 1e-8, 1e-8, 1e-10, 1e5);
	steffensen(function, 1.5, 1e-8, 1e-8, 1e-10, 1e5);
	secant(function, 5.5, 4.5, 1e-8, 1e-8, 1e-10, 1e5);
}
