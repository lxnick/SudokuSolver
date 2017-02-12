// SudokuSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sudoku.h"
#include "Windows.h"

char Quest1[] =
{
	'6','X','X','X','X','X','4','X','5',
	'X','X','8','2','X','X','X','X','X',
	'X','X','X','X','X','X','X','X','X',
	'X','X','X','X','X','6','X','1','X',
	'4','X','7','X','X','X','X','X','X',
	'X','X','X','1','X','X','X','2','X',
	'X','X','6','X','X','X','7','8','X',
	'X','X','X','X','5','4','X','X','X',
	'X','X','X','9','X','X','X','X','X',
};

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf("QueryPerformanceFrequency failed!\n");

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


int main()
{
	CSudoku sudoku;

	FILETIME fileTime;
	GetSystemTimeAsFileTime(&fileTime);

	StartCounter();


	for (int i = 0; i < 100; i++)
	{
		sudoku.Init(Quest1);


		sudoku.Solve();
	}


//	cout << GetCounter() << "\n";
	printf(" Solvd in %2.4f ms", GetCounter() / 100);
//	cout << GetCounter() << "\n";
	//	sudoku_board.so


    return 0;
}

