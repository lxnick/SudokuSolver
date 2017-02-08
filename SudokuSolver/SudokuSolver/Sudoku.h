#pragma once

#include <list>

#define DIGITS	(9)
#define ELEMENTS			(DIGITS*DIGITS)
#define DEFAULT_POSSIBLE	(0x1FF)

typedef struct tagSUDOKU_BOARD
{
	char Pattern[ELEMENTS + 1];
	unsigned short PositionPossible[ELEMENTS];

	unsigned short RowPossible[DIGITS];
	unsigned short ColumnPossible[DIGITS];
	unsigned short GroupPossible[DIGITS];
}	SUDOKU_BOARD, *LPSUDOKU_BOARD;

typedef std::list<SUDOKU_BOARD>	SUDOKU_BOARD_LIST;

class CSudoku
{
public:
	CSudoku();
	~CSudoku();

public: 
	bool Init(char * pszPattern);

	int Solve();

private:

	bool IsFinal(LPSUDOKU_BOARD lpBoard);
	void PrintBoard(LPSUDOKU_BOARD lpBoard);
	bool Improve(LPSUDOKU_BOARD lpBoard, SUDOKU_BOARD_LIST* pGuess);

	bool UpdatePossible(int nPos, LPSUDOKU_BOARD lpBoard);

	bool CollectPossible(LPSUDOKU_BOARD lpBoard,int* nOffset, unsigned short * pnPossible);

	SUDOKU_BOARD_LIST	board_list;

private:

	
};

