#ifndef _FUNCTION_
#define _FUNCTION_
#include "define.h"
/*
//走法生成器
void createMoves(int player);
//估值核心
int evaluate(int color); //估值算法，返回估值
//招法执行器
void makeMove(struct point node, int color);   //执行招法
void unMakeMove(struct point node, int color); //撤销招法
//搜索核心
int searchGoodmove(int player); //搜索核心
//utils

*/
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
//int wwww(unsigned char position[][GRID_NUM], bool bIsWhiteTurn);
//void LoadBoard(const char **);
//void computerMove(int color);

int AnalysisLine(unsigned char *position, int GridNum, int StonePos);
int AnalysisRight(unsigned char position[][GRID_NUM], int i, int j);
int AnalysisLeft(unsigned char position[][GRID_NUM], int i, int j);
int AnalysisVertical(unsigned char position[][GRID_NUM], int i, int j);
int AnalysisHorizon(unsigned char position[][GRID_NUM], int i, int j);
int Evaluate(unsigned char position[][GRID_NUM], bool bIsWhiteTurn);
int AddMove(int nToX, int nToY, int nPly);
int CreatePossibleMove(unsigned char position[][GRID_NUM], int nPly, int nSide);
void MergeSort(STONEMOVE *source, int n, bool direction);
void MergePass(STONEMOVE *source, STONEMOVE *target, const int s, const int n, const bool direction);
void Merge_A(STONEMOVE *source, STONEMOVE *target, int l, int m, int r);
void Merge(STONEMOVE *source, STONEMOVE *target, int l, int m, int r);
void EnterHistoryScore(STONEMOVE *move, int depth);
int GetHistoryScore(STONEMOVE *move);
void ResetHistoryTable();
int NegaScout(int depth, int alpha, int beta);
void SearchAGoodMove(unsigned char position[][GRID_NUM], int Type);
int IsGameOver(unsigned char position[][GRID_NUM], int nDepth);
void UnMakeMove(STONEMOVE *move);
unsigned char MakeMove(STONEMOVE *move, int type);
void _CSearchEngine();
void InitializeHashKey();
void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo);
int LookUpHashTable(int alpha, int beta, int depth, int TableNo);
void Hash_UnMakeMove(STONEMOVE *move, unsigned char CurPosition[][GRID_NUM]);
void Hash_MakeMove(STONEMOVE *move, unsigned char CurPosition[][GRID_NUM]);
void CalculateInitHashKey(unsigned char CurPosition[][GRID_NUM]);
long long rand64();
int rand32();
void CTranspositionTable();
void _CTranspositionTable();
void CNegaScout_TT_HH();

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