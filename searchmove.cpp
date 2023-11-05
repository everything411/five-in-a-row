#include "define.h"
#include "function.h"
#include <cstring>
using namespace std;

int NegaScout(int depth, int alpha, int beta)
{
    int Count, i;
    unsigned char type;
    int a, b, t;
    int side;
    int score;
    // for test only
    //cause a bug
    /*
    if (depth > 0)
    {
        i = IsGameOver(CurPosition, depth);
        if (i != 0)
        {
            //m_cmBestMove.StonePos.x=
            return i; //已分胜负，返回极值
            //checkGameOver();
        }
    }
    */

    side = (m_nMaxDepth - depth) % 2; //计算当前节点的类型,极大0/极小1
    //fprintf(stderr, "side val %d\n", side);
    if (hash_flag)
    {
        score = LookUpHashTable(alpha, beta, depth, side);
        if (score != HASH_NOTFOUND)
            return score;
    }
    if (depth <= 0) //叶子节点取估值
    {
        score = Evaluate(CurPosition, side);
        EnterHashTable(exact, score, depth, side); //将估值存入置换表

        return score;
    }
    Count = CreatePossibleMove(CurPosition, depth, side);
    for (i = 0; i < Count; i++)
        m_MoveList[depth][i].Score = GetHistoryScore(&m_MoveList[depth][i]);

    MergeSort(m_MoveList[depth], Count, 0);
    int bestmove = -1;
    a = alpha;
    b = beta;

    int eval_is_exact = 0;

    for (i = 0; i < Count; i++)
    {
        type = MakeMove(&m_MoveList[depth][i], side);
        Hash_MakeMove(&m_MoveList[depth][i], CurPosition);
        t = -NegaScout(depth - 1, -b, -a); //递归搜索子节点，对第 1 个节点是全窗口，其后是空窗探测
        if (t > a && t < beta && i > 0)
        {
            //对于第一个后的节点,如果上面的搜索failhigh
            a = -NegaScout(depth - 1, -beta, -t); //re-search
            eval_is_exact = 1;                    //设数据类型为精确值
            if (depth == m_nMaxDepth)
                m_cmBestMove = m_MoveList[depth][i];
            bestmove = i;
        }
        Hash_UnMakeMove(&m_MoveList[depth][i], CurPosition);
        UnMakeMove(&m_MoveList[depth][i]);
        if (a < t)
        {
            eval_is_exact = 1;
            a = t;
            if (depth == m_nMaxDepth)
                m_cmBestMove = m_MoveList[depth][i];
        }
        if (a >= beta)
        {
            EnterHashTable(LowerBound, a, depth, side);
            EnterHistoryScore(&m_MoveList[depth][i], depth);
            return a;
        }
        b = a + 1; /* set new null window */
    }
    if (bestmove != -1)
        EnterHistoryScore(&m_MoveList[depth][bestmove], depth);
    if (eval_is_exact)
        EnterHashTable(exact, a, depth, side);
    else
        EnterHashTable(UpperBound, a, depth, side);

    return a;
}

void SearchAGoodMove(unsigned char position[][GRID_NUM], int Type)
{
    int Score;

    memcpy(CurPosition, position, GRID_COUNT);
    m_nMaxDepth = m_nSearchDepth;
    CalculateInitHashKey(CurPosition);
    ResetHistoryTable();
    Score = NegaScout(m_nMaxDepth, -20000, 20000);
    X = m_cmBestMove.StonePos.y;
    Y = m_cmBestMove.StonePos.x;
    MakeMove(&m_cmBestMove, Type);
    memcpy(position, CurPosition, GRID_COUNT);
}
