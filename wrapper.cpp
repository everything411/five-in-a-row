#include "function.h"
#include "define.h"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;
void computer_init_wrapper(void)
{
    /*
    if (computer_color == WHITE)
    {
        fputs("Player first\n", fp);
        m_nSearchDepth = 4; //喵~
    }
    else
    {
        fputs("Computer first\n", fp);
        m_nSearchDepth = 4; //嗷!
    }
    */
    hash_flag = 0;
    m_nSearchDepth = 4; //嗷!
    memset(m_RenjuBoard, BLANK, sizeof(m_RenjuBoard));
    fprintf(fp, "Depth %d\n", m_nSearchDepth);
    fprintf(fp, "hashutils is %s\n", hash_flag ? "ON" : "OFF");
}
void player_move_wrapper(int row, int col)
{
    m_RenjuBoard[row - 1][col - 1] = player_color;
    //player_move.row = row;
    //player_move.col = col;
    fprintf(fp, "[move %d %d] -> player move column %d row %d\n", col, row, col, row);
}
void computerMove_wrapper(int color)
{
    checkwin();
    if (!checkwin_again())
    {
        int ori_depth = m_nSearchDepth;
        m_nUserStoneColor = player_color;
        CNegaScout_TT_HH();
        CTranspositionTable();
        SearchAGoodMove(m_RenjuBoard, computer_color);
        _CTranspositionTable();
        /*
    if (m_RenjuBoard[X][Y] != NOSTONE)
    {
        printf("%d %d", Y, X);
        puts("The computer Eat a STONE!");
        puts("Exit!!!");
        exit(1);
    }
    */
        m_RenjuBoard[X][Y] = computer_color;

        if (color != -1 && (PosValue[X][Y] < 2))
        {
            m_RenjuBoard[X][Y] = NOSTONE;
            fprintf(fp, "computer try to move column %d row %d\n", Y + 1, X + 1);
            fprintf(fp, "Bug Fix: Search Depth is set to 2\n");
            m_nSearchDepth = 2;
            computerMove_wrapper(-1);
            m_nSearchDepth = ori_depth;
            fprintf(fp, "Bug Fix: Search Depth is set to %d\n", m_nSearchDepth);
            //fprintf(fp, "[move %d %d] -> computer move column %d %d\n", Y, X, Y, X);
            return;
        }
        computer_move.row = X + 1;
        computer_move.col = Y + 1;
        computer_move.moved = true;
    }

    fprintf(fp, "[move %d %d] -> computer move column %d row %d\n", Y + 1, X + 1, Y + 1, X + 1);
}
void print_wrapper(void)
{
    print();
}
void computer_first_wrapper(void)
{
    m_RenjuBoard[7][7] = computer_color;
    computer_move.row = 8;
    computer_move.col = 8;
    computer_move.moved = true;
    fprintf(fp, "[move %d %d] -> computer move column %d row %d\n", 8, 8, 8, 8);
}
int isEmpty_wrapper(int row, int col)
{
    return isEmpty(row - 1, col - 1);
}
int inboard_wrapper(int row, int col)
{
    return inboard(row - 1, col - 1);
}
void checkGameOver_wrapper(void)
{
    player_move.row--;
    player_move.col--;
    computer_move.row--;
    computer_move.col--;
    checkGameOver();
    player_move.row++;
    player_move.col++;
    computer_move.row++;
    computer_move.col++;
}
