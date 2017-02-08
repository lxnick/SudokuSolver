// SudokuSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sudoku.h"
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


int main()
{
	CSudoku sudoku;

	sudoku.Init(Quest1);
	sudoku.Solve();
//	sudoku_board.so

    return 0;
}

