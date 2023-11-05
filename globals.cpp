#include "define.h"
#include <cstdio>
using namespace std;
int m_HistoryTable[GRID_NUM][GRID_NUM];        //历史得分表
STONEMOVE m_TargetBuff[225];                   //排序用的缓冲队列
unsigned int m_nHashKey32[15][10][9];          //32位随机树组，用以生成32位哈希值
unsigned long long m_ulHashKey64[15][10][9];   //64位随机树组，用以生成64位哈希值
HashItem *m_pTT[10];                           //置换表头指针
unsigned int m_HashKey32;                      //32位哈希值
long long m_HashKey64;                         //64 位哈希值
STONEMOVE m_MoveList[10][225];                 //用以记录走法的数组
unsigned char m_LineRecord[30];                //存放AnalysisLine分析结果的数组
int TypeRecord[GRID_NUM][GRID_NUM][4];         //存放全部分析结果的数组,有三个维度,用于存放水平、垂直、左斜、右斜 4 个方向上所有棋型分析结果
int TypeCount[2][20];                          //存放统记过的分析结果的数组
int m_nMoveCount;                              //此变量用以记录走法的总数
unsigned char CurPosition[GRID_NUM][GRID_NUM]; //搜索时用于当前节点棋盘状态的数组
STONEMOVE m_cmBestMove;                        //记录最佳走法的变量

int m_nMaxDepth;                                //当前搜索的最大搜索深度
unsigned char m_RenjuBoard[GRID_NUM][GRID_NUM]; //棋盘数组，用于显示棋盘
int m_nUserStoneColor;                          //用户棋子的颜色
int X, Y; //AI输出落子位置
int PosValue[GRID_NUM][GRID_NUM] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
        {0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
        {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

//全局变量,用以统计估值函数的执行遍数
int count = 0;
FILE *fp;
point_t computer_move;
point_t player_move;
int computer_color;
int player_color;
int chessBoard[GRID_NUM][GRID_NUM];
int backupBoard[GRID_NUM][GRID_NUM];
int first_flag;
int m_nSearchDepth;                             //最大搜索深度
int hash_flag;