#ifndef _DEFINE_
#define _DEFINE_
#define _LINUX_
//#define _WINDOWS_
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#define COMPUTER 0
#define PLAYER 1
#define INF 0x3F3F3F3F
#define GRID_NUM 15
/* evaluate defines */
#define STWO 1			//眠二
#define STHREE 2		//眠三
#define SFOUR 3			//冲四
#define TWO 4			//活二
#define THREE 5			//活三
#define FOUR 6			//活四
#define FIVE 7			//五连
#define NOTYPE 11		//未定义
#define ANALSISED 255   //已分析过的
#define TO_BE_ANALSIS 0 //已分析过的
#define GRID_COUNT 225  //棋盘上交点总数
#define BLACK 0			//黑棋用0表示
#define WHITE 1			//白棋用1表示
#define NOSTONE 2		//没有棋子
//compact defines
#define BLANK NOSTONE
#define IsValidPos inboard
/* evaluate defines */
/* struct defines */
typedef struct point
{
	/*
	int x;
	int y;
	*/
	int row;
	int col;
	bool moved;
} point_t;
typedef struct __stoneposition
{
	unsigned char x;
	unsigned char y;
} stone_pos_t;
typedef struct _stonemove
{
	stone_pos_t StonePos;
	int Score;
} move_step_t;
/*
typedef struct __point
{
	int x;
	int y;
} __point_t;
typedef struct __stoneposition
{
	unsigned char x;
	unsigned char y;
} stone_pos_t;
*/
/*
typedef enum __ENTRY_TYPE
{
	exact,
	LowerBound,
	UpperBound
} ENTRY_TYPE;



//棋子位置
typedef struct _stoneposition
{
	unsigned char x;
	unsigned char y;
} STONEPOS;
*/
/*
typedef struct _movestone
{
	unsigned char nRenjuID;
	__point_t ptMovePoint;
} MOVESTONE;
//走法
*/

/* struct defines */
extern int chessBoard[GRID_NUM][GRID_NUM];
extern int backupBoard[GRID_NUM][GRID_NUM];
extern int TypeRecord[GRID_NUM][GRID_NUM][4];
extern int TypeCount[2][20];
extern int move_count;
extern unsigned char curr_pos[GRID_NUM][GRID_NUM];
extern move_step_t best_choice;
extern int search_depth;
extern int max_depth;
extern unsigned char ChessBoard[GRID_NUM][GRID_NUM];
extern int Player_color;
extern int X, Y;
extern move_step_t TargetBuff[225];
extern int debug;
extern move_step_t MoveList[10][225];
extern unsigned char LineRecord[30];
extern int PosValue[GRID_NUM][GRID_NUM];
extern clock_t search_time;
extern long long count;
extern FILE *fp;
extern int first_flag;
extern int player_color, computer_color;
extern point_t player_move, computer_move;
#endif
