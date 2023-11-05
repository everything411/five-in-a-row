#include <iostream>
#include "define.h"
using namespace std;
static void print_board(int i, int j)
{
	if (i == 1 && j == 1)
		printf(" ╔-");
	else if (i == 1 && j == 15)
		printf("-╗");
	else if (i == 15 && j == 1)
		printf(" ╚-");
	else if (i == 15 && j == 15)
		printf("-╝");
	else if (i == 1 && j != 15 && j != 1)
		printf("-┯-");
	else if (i == 15 && j != 15 && j != 1)
		printf("-┷-");
	else if (j == 1 && i != 15 && i != 1)
		printf(" ┠-");
	else if (j == 15 && i != 15 && i != 1)
		printf("-┨");
	else
		printf("-┼-");
}

void print(void)
{
	printf("   ");
	for (int j = 1; j < 16; j++)
		printf("%-3d", j);
	printf("column\n");

	if (first_flag == COMPUTER)
	{
		for (int i = 1; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (j == 0)
					printf("%2d", i);
				else if (m_RenjuBoard[i - 1][j - 1] == BLACK)
					printf(" ○ ");
				else if (m_RenjuBoard[i - 1][j - 1] == WHITE)
					printf(" ● ");
				else
					print_board(i, j);
			}
			printf("\n");
		}
		printf("row\n");
		printf("Search Depth is set to %d\n", m_nSearchDepth);
		if (computer_move.moved)
		{
			printf("Computer: [move %d %d]\nThe computer move at column %d row %d.\n",
				   computer_move.col, computer_move.row, computer_move.col, computer_move.row);
		}
	}
	else
	{
		for (int i = 1; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (j == 0)
					printf("%2d", i);
				else if (m_RenjuBoard[i - 1][j - 1] == WHITE)
					printf(" ○ ");
				else if (m_RenjuBoard[i - 1][j - 1] == BLACK)
					printf(" ● ");
				else
					print_board(i, j);
			}
			printf("\n");
		}
		printf("row\n");
		printf("Search Depth is set to %d\n", m_nSearchDepth);
		if (computer_move.moved)
		{
			printf("Computer: [move %d %d]\nThe computer move at column %d row %d.\n",
				   computer_move.col, computer_move.row, computer_move.col, computer_move.row);
		}
	}
}