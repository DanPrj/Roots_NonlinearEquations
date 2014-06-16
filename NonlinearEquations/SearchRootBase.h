#pragma once

#ifdef SEARCHROOTSDLL_EXPORTS
#define SEARCHROOTSDLL_API __declspec(dllexport) 
#else
#define SEARCHROOTSDLL_API __declspec(dllimport) 
#endif

namespace SearchRoot
{
	class SearchRootBase
	{
	public:

		virtual double Solve( double a, double b, double (*func)(double), int& N, double& eps ) = 0;
		
	};
}
