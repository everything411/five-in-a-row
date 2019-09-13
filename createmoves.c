#include "define.h"
#include "function.h"
#include <stdlib.h>

void Merge(move_step_t *source, move_step_t *target, int l, int m, int r)
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

void Merge_A(move_step_t *source, move_step_t *target, int l, int m, int r)
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
void MergePass(move_step_t *source, move_step_t *target, const int s, const int n, const bool direction)
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

void MergeSort(move_step_t *source, int n, bool direction)
{
    int s = 1;
    while (s < n)
    {
        MergePass(source, TargetBuff, s, n, direction);
        s += s;
        MergePass(TargetBuff, source, s, n, direction);
        s += s;
    }
}

int AddMove(int nToX, int nToY, int nPly)
{
    MoveList[nPly][move_count].StonePos.x = nToX;
    MoveList[nPly][move_count].StonePos.y = nToY;

    move_count++;
    MoveList[nPly][move_count].Score = PosValue[nToY][nToX]; //使用位置价值表评估当前走法的价值
    return move_count;
}

int CreatePossibleMove(unsigned char position[][GRID_NUM], int nPly, int nSide)
{
    int i, j;
    move_count = 0;
    for (i = 0; i < GRID_NUM; i++)
        for (j = 0; j < GRID_NUM; j++)
        {
            if (position[i][j] == (unsigned char)NOSTONE)
                AddMove(j, i, nPly);
        }

    MergeSort(MoveList[nPly], move_count, 0);

    return move_count; //返回合法走法个数
}

