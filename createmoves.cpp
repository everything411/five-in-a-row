#include "define.h"
#include "function.h"
#include <unistd.h>
#include <cstdlib>
using namespace std;
//对走法队列从小到大排序
//STONEMOVE* source原始队列
//STONEMOVE* target目标队列
//合并source[l…m]和 source[m +1…r]至target[l…r]
void Merge(STONEMOVE *source, STONEMOVE *target, int l, int m, int r)
{
    //从小到大排序
    int i = l;
    int j = m + 1;
    int k = l;
    while (i <= m && j <= r)
        if (source[i].Score <= source[j].Score)
            target[k++] = source[i++];
        else
            target[k++] = source[j++];
    if (i > m)
        for (int q = j; q <= r; q++)
            target[k++] = source[q];
    else
        for (int q = i; q <= m; q++)
            target[k++] = source[q];
}

void Merge_A(STONEMOVE *source, STONEMOVE *target, int l, int m, int r)
{
    //从大到小排序
    int i = l;
    int j = m + 1;
    int k = l;
    while (i <= m && j <= r)
        if (source[i].Score >= source[j].Score)
            target[k++] = source[i++];
        else
            target[k++] = source[j++];
    if (i > m)
        for (int q = j; q <= r; q++)
            target[k++] = source[q];
    else
        for (int q = i; q <= m; q++)
            target[k++] = source[q];
}

//合并大小为 S 的相邻子数组
//direction 是标志,指明是从大到小还是从小到大排序
void MergePass(STONEMOVE *source, STONEMOVE *target, const int s, const int n, const bool direction)
{
    int i = 0;
    while (i <= n - 2 * s)
    {
        //合并大小为 s的相邻二段子数组
        if (direction)
            Merge(source, target, i, i + s - 1, i + 2 * s - 1);
        else
            Merge_A(source, target, i, i + s - 1, i + 2 * s - 1);
        i = i + 2 * s;
    }
    if (i + s < n) //剩余的元素个数小于2s
    {
        if (direction)
            Merge(source, target, i, i + s - 1, n - 1);
        else
            Merge_A(source, target, i, i + s - 1, n - 1);
    }
    else
        for (int j = i; j <= n - 1; j++)
            target[j] = source[j];
}

void MergeSort(STONEMOVE *source, int n, bool direction)
{
    int s = 1;
    while (s < n)
    {
        MergePass(source, m_TargetBuff, s, n, direction);
        s += s;
        MergePass(m_TargetBuff, source, s, n, direction);
        s += s;
    }
}

//在m_MoveList中插入一个走法
//nToX是目标位置横坐标
//nToY是目标位置纵坐标
//nPly是此走法所在的层次
int AddMove(int nToX, int nToY, int nPly)
{
    m_MoveList[nPly][m_nMoveCount].StonePos.x = nToX;
    m_MoveList[nPly][m_nMoveCount].StonePos.y = nToY;

    m_nMoveCount++;
    m_MoveList[nPly][m_nMoveCount].Score = PosValue[nToY][nToX]; //使用位置价值表评估当前走法的价值
    return m_nMoveCount;
}

int CreatePossibleMove(unsigned char position[][GRID_NUM], int nPly, int nSide)
{
    int i, j;
    m_nMoveCount = 0;
    for (i = 0; i < GRID_NUM; i++)
        for (j = 0; j < GRID_NUM; j++)
        {
            if (position[i][j] == (unsigned char)NOSTONE)
                AddMove(j, i, nPly);
        }

    //使用历史启发类中的静态归并排序函数对走法队列进行排序
    //这是为了提高剪枝效率
    //        CHistoryHeuristic history;
    MergeSort(m_MoveList[nPly], m_nMoveCount, 0);

    return m_nMoveCount; //返回合法走法个数
}

