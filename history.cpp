#include "define.h"
#include <cstring>
using namespace std;
//将历史记录表中所有项目全置为初值
void ResetHistoryTable()
{
    memset(m_HistoryTable, 10, GRID_COUNT * sizeof(int));
}

//从历史得分表中取给定走法的历史得分
int GetHistoryScore(STONEMOVE *move)
{
    return m_HistoryTable[move->StonePos.x][move->StonePos.y];
}

//将一最佳走法汇入历史记录
void EnterHistoryScore(STONEMOVE *move, int depth)
{
    m_HistoryTable[move->StonePos.x][move->StonePos.y] += 2 << depth;
}
void CNegaScout_TT_HH()
{
    ResetHistoryTable();
}