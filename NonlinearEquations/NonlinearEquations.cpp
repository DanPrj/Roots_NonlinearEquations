// NonlinearEquations.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SearchRootBase.h"
#include "windows.h"
#include "stdio.h"
#include "math.h"
#include <iostream>
using namespace std;

using namespace SearchRoot;

#define _FUNCTION_NAME "getMethod"

typedef SearchRootBase* (*MYPROC)();

double func1(double x)
{
	return exp(x) - 5*x;
}

double func2(double x)
{
	return -pow(x,2) + pow(x,5) + pow(x,9);
}

double func3(double x)
{
	return exp(sin(x)) - x;
}

double func4(double x)
{
	return sin(cos(x)) + pow(x,2)/100.0;
}

double func5(double x)
{
	return log(fabs(x)) - pow(x,5);
}

int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE hinstLib; 
	MYPROC getMethod; 
	BOOL fFreeResult; 

	cout << "Methods:" << endl;
	cout << "	" << "1 - Dichotomy method" << endl;
	cout << "	" << "2 - Secant method" << endl;
	cout << "	" << "3 - Newtons method" << endl;

	int numMethod;
	
	while(1)
	{
		cout << endl << "Input the method number: ";
		cin >> numMethod;
		if(numMethod >= 1 && numMethod <= 3)
		{
			cout << "input success: method number " << numMethod << endl;
			break;
		}
		else
			cout << "input failure: please repeat " << numMethod << endl;
	}
		
	LPCWSTR str;
	switch(numMethod)
	{
	case 1:
		str = L"DichotomyMethod.dll";
		break;
	case 2:
		str = L"SecantMethod.dll";
		break;
	case 3:
		str = L"NewtonsMethod.dll";
		break;
	}
	hinstLib = LoadLibrary(str);

	// Если дескриптор допустимый, то попробуем получить
	// адрес функции.

	cout << endl << "Select function: " << endl;
	cout << "	" << "1: e^x - 5*x;			approx roots: 0.26, 2.52" << endl;
	cout << "	" << "2: -x^2 + x^5 + x^9;		approx roots: 0, 0.86" << endl;
	cout << "	" << "3: e^(sin(x)) - x;		approx roots: 2.219" << endl;
	cout << "	" << "4: sin(cos(x)) + x^2/100;	approx roots: -4.5, -1.6, 1.6, 4.5" << endl;
	cout << "	" << "5: ln(|x|) - x^5;		approx roots: -0.766" << endl;

	int funcNum;

	while(1)
	{
		cout << endl << "Input function number: ";
		cin >> funcNum;
		if(funcNum >= 1 && funcNum <= 5)
		{
			cout << "input success: function number " << funcNum << endl;
			break;
		}
		else
			cout << "input failure: please repeat " << numMethod << endl;
	}

	int N;
	double eps;
	double a, b;

	cout << endl << "Input interval [a,b]: " << endl;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	cout << endl << "Input maximum iterations count: ";
	cin >> N;
	cout << endl << "Input epsilum: ";
	cin >> eps;

	if (hinstLib != NULL) 
	{ 
		getMethod = (MYPROC) GetProcAddress(hinstLib, _FUNCTION_NAME); 

		// Если адрес функции правильный, то вызываем функцию.

		if (NULL != getMethod) 
		{
			SearchRootBase* m = getMethod(); 

			printf("Load method from dll success!");
			double root;
			switch(funcNum)
			{
			case 1:
				root = m->Solve(a, b, func1, N, eps);
				break;
			case 2:
				root = m->Solve(a, b, func2, N, eps);
				break;
			case 3:
				root = m->Solve(a, b, func3, N, eps);
				break;
			case 4:
				root = m->Solve(a, b, func4, N, eps);
				break;
			case 5:
				root = m->Solve(a, b, func5, N, eps);
				break;
			}
			
			cout << endl;
			cout << "	Results: " << endl;
			cout << "Root = " << root <<";" << endl;
			cout << "N = " << N <<";" << endl;
			cout << "Eps = " << eps << ";" << endl << endl;

			delete m;
		}

		// Освобождаем модуль DLL.
		
		fFreeResult = FreeLibrary(hinstLib); 
	} 
	else
		printf("Can not find library %s\n", argv[1]);


	return 0;
}

