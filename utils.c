#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <time.h>
#include "define.h"
#include "function.h"

void arg_handler(int argc, char const *argv[])
{
    if (argc == 1)
    {
        return;
    }
    else
    {
        int val = atoi(argv[1]);
        if (val >= 2)
        {
            search_depth = val;
        }
        fprintf(fp, "Override default search depth.\nSearch depth is set to %d\n", search_depth);
    }
}
void init(void)
{
    fp = fopen("test.log", "a+");
    time_t curr_time;
    time(&curr_time);
    fputs(ctime(&curr_time), fp);
    signal(SIGINT, handler);
}
void handler(int signal)
{
    fputs("SIGINT received. Exit.\n", fp);
    exit(1);
}
/*
void getshell(void)
{
    puts("Get Shell!");
    system("/bin/bash");
}
*/
bool inboard(int row, int col)
{
    return row >= 0 && row < GRID_NUM && col >= 0 && col < GRID_NUM;
}
bool isEmpty(int row, int col)
{
    return ChessBoard[row][col] == BLANK;
}

void clear(void)
{
#ifdef _WINDOWS_
    system("cls");
#endif
#ifdef _LINUX_
    //fputs("Debug ON\n", stderr);
    //fputs("\x1b\x5b\x48\x1b\x5b\x32\x4a\x1b\x5b\x33\x4a", stdout);
    system("clear");
#endif
}
void validateBoard(void)
{
    int black_cnt = 0;
    int white_cnt = 0;
    for (int i = 0; i < GRID_NUM; i++)
    {
        for (int j = 0; j < GRID_NUM; j++)
        {
            black_cnt += ChessBoard[i][j] == BLACK;
            white_cnt += ChessBoard[i][j] == WHITE;
        }
    }

    if (!(abs(black_cnt - white_cnt) < 2))
    {
        puts("The computer Eat a STONE!");
        puts("Exit!!!");
        exit(1);
    }

    assert(abs(black_cnt - white_cnt) < 2);
}
void unmove(void)
{
    puts("Function Not Implemented");
    //memcpy(chessBoard, backupBoard, sizeof(chessBoard));
}
void update_backup(void)
{
    ;
    //memcpy(backupBoard, chessBoard, sizeof(chessBoard));
}
/*
void LoadBoard(const char **name)
{
    FILE *fp;
    if ((fp = fopen(name[1], "r")) != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                fscanf(fp, "%hhu", &m_RenjuBoard[i][j]);
            }
        }
    }
    else
    {
        perror(name[0]);
        exit(0);
    }
}
*/