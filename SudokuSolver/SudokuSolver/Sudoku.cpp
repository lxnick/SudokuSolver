#include "stdafx.h"
#include "Sudoku.h"

int	COLUMN_OFFSET[DIGITS][DIGITS] =
{
	{ 0, 9,18,27,36,45,54,63,72 },
	{ 1,10,19,28,37,46,55,64,73 },
	{ 2,11,20,29,38,47,56,65,74 },
	{ 3,12,21,30,39,48,57,66,75 },
	{ 4,13,22,31,40,49,58,67,76 },
	{ 5,14,23,32,41,50,59,68,77 },
	{ 6,15,24,33,42,51,60,69,78 },
	{ 7,16,25,34,43,52,61,70,79 },
	{ 8,17,26,35,44,53,62,71,80 },
};

int	ROW_OFFSET[DIGITS][DIGITS] =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8 },
	{ 9,10,11,12,13,14,15,16,17 },
	{ 18,19,20,21,22,23,24,25,26 },
	{ 27,28,29,30,31,32,33,34,35 },
	{ 36,37,38,39,40,41,42,43,44 },
	{ 45,46,47,48,49,50,51,52,53 },
	{ 54,55,56,57,58,59,60,61,62 },
	{ 63,64,65,66,67,68,69,70,71 },
	{ 72,73,74,75,76,77,78,79,80 },
};

int	GROUP_OFFSET[DIGITS][DIGITS] =
{
	{ 0, 1, 2, 9,10,11,18,19,20 },
	{ 3, 4, 5,12,13,14,21,22,23 },
	{ 6, 7, 8,15,16,17,24,25,26 },
	{ 27,28,29,36,37,38,45,46,47 },
	{ 30,31,32,39,40,41,48,49,50 },
	{ 33,34,35,42,43,44,51,52,53 },
	{ 54,55,56,63,64,65,72,73,74 },
	{ 57,58,59,66,67,68,75,76,77 },
	{ 60,61,62,69,70,71,78,79,80 },
};

int POSITION_ROW[ELEMENTS] =
{
	0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,
};

int POSITION_COLUMN[ELEMENTS] =
{
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
	0,1,2,3,4,5,6,7,8,
};

int POSITION_GROUP[ELEMENTS] =
{
	0, 0, 0, 1, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 1, 2, 2, 2,
	0, 0, 0, 1, 1, 1, 2, 2, 2,
	3, 3, 3, 4, 4, 4, 5, 5, 5,
	3, 3, 3, 4, 4, 4, 5, 5, 5,
	3, 3, 3, 4, 4, 4, 5, 5, 5,
	6, 6, 6, 7, 7, 7, 8, 8, 8,
	6, 6, 6, 7, 7, 7, 8, 8, 8,
	6, 6, 6, 7, 7, 7, 8, 8, 8,
};


unsigned short PATTERN_MASK[DIGITS] =
{
	1,2,4,8,16,32,64,128,256,
};

unsigned short BIT_COUNT[DEFAULT_POSSIBLE + 1] = 
{
	0, 1, 1, 

};

CSudoku::CSudoku()
{
	for (int i = 0; i <= DEFAULT_POSSIBLE; i++)
	{
		int bit_count = 0;

		for (int j = 0; j < DIGITS; j++)
		{
			if (i & (1 << j))
				bit_count++;
		}

		BIT_COUNT[i] = bit_count;
	}
}

CSudoku::~CSudoku()
{

}

bool CSudoku::Init(char * pszPattern)
{
	SUDOKU_BOARD	board;
	for (int i = 0; i < ELEMENTS; i++)
	{
		char ch = *pszPattern++;
		if (ch >= '1' && ch <= '9')
		{
			board.Pattern[i] = ch;
			board.PositionPossible[i] = 0;
		}
		else
		{
			board.Pattern[i] = ' ';
			board.PositionPossible[i] = DEFAULT_POSSIBLE;
		}
	}

	board.Pattern[ELEMENTS] = '\0';

	for (int i = 0; i < DIGITS; i++)
	{
		if (!CollectPossible(&board, &ROW_OFFSET[i][0], &board.RowPossible[i]))
			return false;

		if (!CollectPossible(&board, &COLUMN_OFFSET[i][0], &board.ColumnPossible[i]))
			return false;

		if (!CollectPossible(&board, &GROUP_OFFSET[i][0], &board.GroupPossible[i]))
			return false;
	}

	board_list.push_back(board);

	return true;
}

bool CSudoku::CollectPossible(LPSUDOKU_BOARD lpBoard, int* nOffset, unsigned short * pnPossible)
{
	unsigned short symbol_found = 0;

	for (int i = 0; i < DIGITS; i++)
	{
		char ch = lpBoard->Pattern[ *nOffset ++ ];

		if (ch >= '1' && ch <= '9')
		{
			unsigned short bit = 1 << (ch - '1');
			if (symbol_found & bit )
				return false;
			else
				symbol_found |= bit;
		}
	}

	*pnPossible = DEFAULT_POSSIBLE ^ symbol_found;
	return true;
}

bool CSudoku::IsFinal(LPSUDOKU_BOARD lpBoard)
{
	for (int i = 0; i < ELEMENTS; i++)
		if (lpBoard->PositionPossible[i] != 0)
			return false;

	return true;
}

bool CSudoku::UpdatePossible(int nPos, LPSUDOKU_BOARD lpBoard)
{
	int row = POSITION_ROW[nPos];
	int column = POSITION_COLUMN[nPos];
	int group = POSITION_GROUP[nPos];

	if (!CollectPossible(lpBoard, &ROW_OFFSET[row][0], &lpBoard->RowPossible[row]))
		return false;

	if (!CollectPossible(lpBoard,&COLUMN_OFFSET[column][0], &lpBoard->ColumnPossible[column]))
		return false;

	if (!CollectPossible(lpBoard, &GROUP_OFFSET[group][0], &lpBoard->GroupPossible[group]))
		return false;

	return true;
}

void CSudoku::PrintBoard(LPSUDOKU_BOARD lpBoard)
{
	printf("---------\n");
	for (int i = 0; i < ELEMENTS; i += DIGITS)
		printf("%c%c%c%c%c%c%c%c%c\n",
			lpBoard->Pattern[i + 0],
			lpBoard->Pattern[i + 1],
			lpBoard->Pattern[i + 2],
			lpBoard->Pattern[i + 3],
			lpBoard->Pattern[i + 4],
			lpBoard->Pattern[i + 5],
			lpBoard->Pattern[i + 6],
			lpBoard->Pattern[i + 7],
			lpBoard->Pattern[i + 8]
		);

	for (int i = 0; i < ELEMENTS; i++)
	{
		if (lpBoard->PositionPossible[i] == 0)
			if (lpBoard->Pattern[i] == ' ')
				printf("Error\n");
	}

}

int Step = 0;
bool CSudoku::Improve(LPSUDOKU_BOARD lpBoard, SUDOKU_BOARD_LIST* pGuess)
{
	printf("Step = %d\n", Step);
	Step++;

	bool bImprove = false;


	for (int i = 0; i < ELEMENTS; i++)
	{
		if (lpBoard->PositionPossible[i] == 0)
			continue;

		unsigned short raw_possible = lpBoard->RowPossible[POSITION_ROW[i]];
		unsigned short column_possible = lpBoard->ColumnPossible[POSITION_COLUMN[i]];
		unsigned short group_possible = lpBoard->GroupPossible[POSITION_GROUP[i]];
		unsigned short position_possible = raw_possible & column_possible & group_possible;

		if (position_possible == lpBoard->PositionPossible[i])
			continue;

		if (position_possible == 0)
			return false;

///		PrintBoard(lpBoard);
		lpBoard->PositionPossible[i] = position_possible;
//		PrintBoard(lpBoard);

		if (BIT_COUNT[position_possible] != 1)
			continue;

		// Find only solved item ( only 1 bit is true )
		for (int j = 0; j < DIGITS; j++)
		{
			if (position_possible == PATTERN_MASK[j])
			{
				bImprove = true;
				lpBoard->Pattern[i] = j + '1';
				lpBoard->PositionPossible[i] = 0;

				printf("Set %d to %c\n", i, lpBoard->Pattern[i]);
				UpdatePossible(i, lpBoard);
			}
		}
	}

	if (bImprove)
		return true;

	int min_possible = DIGITS;
	int min_position = 0;
	for (int i = 0; i < ELEMENTS; i++)
	{
		if (lpBoard->PositionPossible[i] == 0)
			continue;

		int bit_count = BIT_COUNT[lpBoard->PositionPossible[i]];

		if (BIT_COUNT[lpBoard->PositionPossible[i]] < min_possible)
		{
			min_possible = BIT_COUNT[lpBoard->PositionPossible[i]];
			min_position = i;
		}
	}

	if (min_possible == DIGITS)
	{
		// It should be a final 
		SUDOKU_BOARD board = *lpBoard;
		pGuess->push_back(board);
		return false;
	}

	char possible_char[DIGITS];
	char * possible_char_ptr = possible_char;
	for (int i = 0; i < DIGITS; i++)
	{
		if (lpBoard->PositionPossible[min_position] & (1 << i))
		{
			*possible_char_ptr = '1' + i;
			possible_char_ptr ++;
		}
	}


	for (int i = 0; i < min_possible; i++)
	{
		SUDOKU_BOARD board = *lpBoard;
		board.Pattern[min_position] = possible_char[i];
		board.PositionPossible[min_position] = 0;

		printf("Guess %d to %c\n", min_position, possible_char[i]);

		if (board.Pattern[0] != '6')
			printf("Board Head %c\n", board.Pattern[0] );

		UpdatePossible(min_position, &board);

		pGuess->push_back(board);
	}

	return false;
}

int CSudoku::Solve()
{
	int nSolveCount = 0;

	if (board_list.size() == 1)
	{
		SUDOKU_BOARD	start = board_list.front();
		PrintBoard(&start);
	}

	while (board_list.size() != 0)
	{
		SUDOKU_BOARD	board = board_list.front();
		board_list.pop_front();

		SUDOKU_BOARD_LIST guess_list;

		PrintBoard(&board);
		if (IsFinal(&board))
		{
			printf("\nSolved");
			PrintBoard(&board);

			nSolveCount++;
			continue;
		}

		while (Improve(&board, &guess_list))
		{
			printf("\nImprove");
			PrintBoard(&board);
		}
	
		board_list.splice(board_list.end(), guess_list);

	}

	return nSolveCount;
}