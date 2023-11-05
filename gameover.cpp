#include "define.h"
#include "function.h"
#include <cstdio>
#include <cstdlib>
using namespace std;
bool boardIsFull(void)
{
	for (int i = 0; i < GRID_NUM; i++)
		for (int j = 0; j < GRID_NUM; j++)
			if (m_RenjuBoard[i][j] == BLANK)
				return false;
	return true;
}
bool gameover(int player)
{
	int last_color;
	point_t last_move;
	if (player == PLAYER)
		last_move = player_move, last_color = player_color;
	else
		last_move = computer_move, last_color = computer_color;
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		count = 0;
		for (int j = -4 + i; j <= 0 + i; j++) //横
		{
			if (inboard(last_move.row, last_move.col + j) &&
				m_RenjuBoard[last_move.row][last_move.col + j] == last_color)
				count++;
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		count = 0;
		for (int j = -4 + i; j <= 0 + i; j++) //纵
		{
			if (inboard(last_move.row + j, last_move.col) &&
				m_RenjuBoard[last_move.row + j][last_move.col] == last_color)
				count++;
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		count = 0;
		for (int j = -4 + i; j <= 0 + i; j++) //主
		{
			if (inboard(last_move.row + j, last_move.col + j) &&
				m_RenjuBoard[last_move.row + j][last_move.col + j] == last_color)
				count++;
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		count = 0;
		for (int j = -4 + i; j <= 0 + i; j++) //副
		{
			if (inboard(last_move.row - j, last_move.col + j) &&
				m_RenjuBoard[last_move.row - j][last_move.col + j] == last_color)
				count++;
			else
				break;
		}
		if (count == 5)
		{
			return true;
		}
	}

	return false;
}
void checkGameOver(void) //检查是否游戏结束
{
	if (gameover(COMPUTER))
	{
		puts("COMPUTER WIN!");
		exit(0);
	}
	else if (gameover(PLAYER))
	{
		puts("PLAYER WIN!");
		exit(0);
	}
	else if (boardIsFull())
	{
		puts("The board is FULL! Exit...");
		exit(0);
	}
}
//for compact
/*
int IsGameOver(unsigned char position[][GRID_NUM], int nDepth)
{
	int score, i; //计算要下的棋子颜色
	//i = (m_nMaxDepth - nDepth) % 2;
	i = nDepth;
	score = Evaluate(position, i); //调用估值函数
	if (abs(score) > 8000)		   //如果估值函数返回极值，给定局面游戏结束
		return score;			   //返回极值
	return 0;					   //返回未结束
}
*/

//Big bug fix
void checkwin(void)
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			if (m_RenjuBoard[i][j] == NOSTONE)
			{
				m_RenjuBoard[i][j] = computer_color;
				computer_move.row = i;
				computer_move.col = j;
				computer_move.moved = true;
				if (gameover(COMPUTER))
				{
					//puts("GAMEOVER");
					computer_move.row++;
					computer_move.col++;
					fputs("Bug fix: checkwin() function activated\n", fp);
					fprintf(fp, "[move %d %d] -> computer move column %d row %d\n", j + 1, i + 1, j + 1, i + 1);
					clear();
					print();
					puts("COMPUTER WIN!");
					exit(0);
					//checkGameOver();
				}
				else
				{
					m_RenjuBoard[i][j] = NOSTONE;
				}
			}
		}
	}
}
// not a good solution
bool checkwin_again(void)
{
	for (int i = 0; i < GRID_NUM; i++)
	{
		for (int j = 0; j < GRID_NUM; j++)
		{
			if (m_RenjuBoard[i][j] == BLANK)
			{
				m_RenjuBoard[i][j] = player_color;
				player_move.row = i;
				player_move.col = j;
				//player_move.moved = true;
				if (gameover(PLAYER))
				{
					//puts("GAMEOVER");
					m_RenjuBoard[i][j] = computer_color;
					computer_move.row = i + 1;
					computer_move.col = j + 1;
					computer_move.moved = true;
					fputs("Bug fix: checkwin_again() function activated\n", fp);
					//fprintf(fp, "[move %d %d] -> computer move column %d row %d\n", j + 1, i + 1, j + 1, i + 1);
					//clear();
					//print();
					//puts("true!!!");
					//exit(0);
					return true;
					//puts("COMPUTER WIN!");
					//exit(0);
					//checkGameOver();
				}
				else
				{
					m_RenjuBoard[i][j] = NOSTONE;
				}
			}
		}
	}
	return false;
}