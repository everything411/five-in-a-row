#ifndef _DEFINE_
#define _DEFINE_
#define _LINUX_
#define COMPUTER 0
#define PLAYER 1
//#include <cstdio>
//using namespace std;
/*
#define BLANK 0 //空白点
#define BLACK 1 //黑方
#define WHITE 2 //白方
*/
#define INF 0x3F3F3F3F
#define GRID_NUM 15
#include <cstdio>
typedef struct point
{
	int row;
	int col;
	bool moved;
} point_t;
enum ENTRY_TYPE
{
	exact,
	LowerBound,
	UpperBound
};
typedef struct HASHITEM
{
	long long checksum;	//64位校验码
	ENTRY_TYPE entry_type; //数据类型
	short depth;		   //取得此值时的层次
	short eval;			   //节点的值
} HashItem;

typedef struct Node
{
	int x;
	int y;
} POINT;

//用以表示棋子位置的结构
typedef struct _stoneposition
{
	unsigned char x;
	unsigned char y;
} STONEPOS;

typedef struct _movestone
{
	unsigned char nRenjuID;
	POINT ptMovePoint;
} MOVESTONE;
//这个结构用以表示走法

typedef struct _stonemove
{
	STONEPOS StonePos; //棋子位置
	int Score;		   //走法的分数
} STONEMOVE;
extern int chessBoard[GRID_NUM][GRID_NUM];
extern int backupBoard[GRID_NUM][GRID_NUM];
extern int player_color, computer_color;
extern point_t player_move, computer_move;
#define IsValidPos inboard
/* evaluate defines */
#define STWO 1		  //眠二
#define STHREE 2	  //眠三
#define SFOUR 3		  //冲四
#define TWO 4		  //活二
#define THREE 5		  //活三
#define FOUR 6		  //活四
#define FIVE 7		  //五连
#define NOTYPE 11	 //未定义
#define ANALSISED 255 //已分析过的
#define TOBEANALSIS 0 //已分析过的
/* evaluate defines */

#define GRID_COUNT 225 //棋盘上交点总数
#define BLACK 0		   //黑棋用0表示
#define WHITE 1		   //白棋用1表示
#define NOSTONE 2	  //没有棋子
#define BLANK NOSTONE
//这组宏定义了用以代表几种棋型的数字
#define HASH_NOTFOUND 66666
extern int m_HistoryTable[GRID_NUM][GRID_NUM];		   //历史得分表
extern STONEMOVE m_TargetBuff[225];					   //排序用的缓冲队列
extern unsigned int m_nHashKey32[15][10][9];		   //32位随机树组，用以生成32位哈希值
extern unsigned long long m_ulHashKey64[15][10][9];	//64位随机树组，用以生成64位哈希值
extern HashItem *m_pTT[10];							   //置换表头指针
extern unsigned int m_HashKey32;					   //32位哈希值
extern long long m_HashKey64;						   //64 位哈希值
extern STONEMOVE m_MoveList[10][225];				   //用以记录走法的数组
extern unsigned char m_LineRecord[30];				   //存放AnalysisLine分析结果的数组
extern int TypeRecord[GRID_NUM][GRID_NUM][4];		   //存放全部分析结果的数组,有三个维度,用于存放水平、垂直、左斜、右斜 4 个方向上所有棋型分析结果
extern int TypeCount[2][20];						   //存放统记过的分析结果的数组
extern int m_nMoveCount;							   //此变量用以记录走法的总数
extern unsigned char CurPosition[GRID_NUM][GRID_NUM];  //搜索时用于当前节点棋盘状态的数组
extern STONEMOVE m_cmBestMove;						   //记录最佳走法的变量
extern int m_nSearchDepth;							   //最大搜索深度
extern int m_nMaxDepth;								   //当前搜索的最大搜索深度
extern unsigned char m_RenjuBoard[GRID_NUM][GRID_NUM]; //棋盘数组，用于显示棋盘
extern int m_nUserStoneColor;						   //用户棋子的颜色
extern int X, Y;									   //AI输出落子位置
//extern int SL;										   //胜利标记
extern int PosValue[GRID_NUM][GRID_NUM]; //位置重要性价值表,此表从中间向外,越往外价值越低
extern int count;
extern FILE *fp;
extern int first_flag;
extern int hash_flag;
#endif
