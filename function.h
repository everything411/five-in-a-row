#ifndef _FUNCTION_
#define _FUNCTION_
#include "define.h"
bool checkwin_again(void);
void checkwin(void);
void handler(int);
void print(void);
void checkGameOver(void);
void validateBoard(void);
bool inboard(int a, int b);
void clear(void);
bool isEmpty(int x, int y);
void unmove(void);
void update_backup(void);
void arg_handler(int argc, char const *argv[]);

int analyse_Line(unsigned char *position, int GridNum, int StonePos);
int analyse_Right(unsigned char position[][GRID_NUM], int i, int j);
int analyse_Left(unsigned char position[][GRID_NUM], int i, int j);
int analyse_Vertical(unsigned char position[][GRID_NUM], int i, int j);
int analyse_Horizon(unsigned char position[][GRID_NUM], int i, int j);
int Evaluate(unsigned char position[][GRID_NUM], bool IsWhiteTurn);
int AddMove(int nToX, int nToY, int nPly);
int CreatePossibleMove(unsigned char position[][GRID_NUM], int nPly, int nSide);
void MergeSort(move_step_t *source, int n, bool direction);
void MergePass(move_step_t *source, move_step_t *target, const int s, const int n, const bool direction);
void Merge_A(move_step_t *source, move_step_t *target, int l, int m, int r);
void Merge(move_step_t *source, move_step_t *target, int l, int m, int r);
int nega_search(int depth, int alpha, int beta);
void get_best_step(unsigned char position[][GRID_NUM], int Type);
void UnMakeMove(move_step_t *move);
unsigned char MakeMove(move_step_t *move, int type);
// wrapper
void player_move_wrapper(int row, int col);
void computerMove_wrapper(int color);
void print_wrapper(void);
void computer_first_wrapper(void);
void computer_init_wrapper(void);
int isEmpty_wrapper(int row, int col);
int inboard_wrapper(int row, int col);
void checkGameOver_wrapper(void);
void init(void);
#endif