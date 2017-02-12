#pragma once

#include <list>

#define DIGIT_COUNT	(9)
#define CELL_COUNT			(DIGIT_COUNT*DIGIT_COUNT)
#define UNIVERSAL_SET		(0x1FF)

typedef struct tagSUDOKU_BOARD
{
	char Pattern[CELL_COUNT + 1];					// For displaying
	unsigned short CellSet[CELL_COUNT];				// For Cell status tracking

	unsigned short RowSet[DIGIT_COUNT];			// Row possible set
	unsigned short ColumnSet[DIGIT_COUNT];		// Column possible set
	unsigned short BlockSet[DIGIT_COUNT];		// Block possible set
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

	bool IsSolved(char * pszPattern);

private:

	bool IsFinal(LPSUDOKU_BOARD lpBoard);
	void PrintBoard(LPSUDOKU_BOARD lpBoard);
	bool Improve(LPSUDOKU_BOARD lpBoard, SUDOKU_BOARD_LIST* pGuess);

	bool UpdatePossible(int nPos,int Bit, LPSUDOKU_BOARD lpBoard);

	bool CollectPossible(LPSUDOKU_BOARD lpBoard,int* nOffset, unsigned short * pnPossible);

	SUDOKU_BOARD_LIST	board_list;

private:

	
};

bool IsValid(char * pszPattern);