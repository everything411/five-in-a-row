#include "define.h"
#include "function.h"
#include <cstring>
#include <unistd.h>
using namespace std;
int AnalysisLine(unsigned char *position, int GridNum, int StonePos)
{
    unsigned char StoneType;
    unsigned char AnalyLine[30];
    int nAnalyPos;
    int LeftEdge, RightEdge;
    int LeftRange, RightRange;

    if (GridNum < 5)
    {
        //数组长度小于5没有意义
        //fprintf(stderr, "len < 5\n");
        //printf("Something is wrong\n");
        //sleep(10);
        //exit(1);
        memset(m_LineRecord, ANALSISED, GridNum);
        return 0;
    }
    nAnalyPos = StonePos;
    memset(m_LineRecord, TOBEANALSIS, 30);
    memset(AnalyLine, 0x0F, 30);
    //将传入数组装入AnalyLine;
    memcpy(&AnalyLine, position, GridNum);
    GridNum--;
    StoneType = AnalyLine[nAnalyPos];
    LeftEdge = nAnalyPos;
    RightEdge = nAnalyPos;
    //算连续棋子左边界
    while (LeftEdge > 0)
    {
        if (AnalyLine[LeftEdge - 1] != StoneType)
            break;
        LeftEdge--;
    }

    //算连续棋子右边界
    while (RightEdge < GridNum)
    {
        if (AnalyLine[RightEdge + 1] != StoneType)
            break;
        RightEdge++;
    }
    LeftRange = LeftEdge;
    RightRange = RightEdge;
    //下面两个循环算出棋子可下的范围
    while (LeftRange > 0)
    {
        if (AnalyLine[LeftRange - 1] == !StoneType)
            break;
        LeftRange--;
    }
    while (RightRange < GridNum)
    {
        if (AnalyLine[RightRange + 1] == !StoneType)
            break;
        RightRange++;
    }
    //如果此范围小于4则分析没有意义
    /*
    if (RightRange - LeftRange < 4)
    {
        for (int k = LeftRange; k <= RightRange; k++)
            m_LineRecord[k] = ANALSISED;
        return false;
    }
    */
    //将连续区域设为分析过的,防止重复分析此一区域
    for (int k = LeftEdge; k <= RightEdge; k++)
        m_LineRecord[k] = ANALSISED;
    if (RightEdge - LeftEdge > 3)
    {
        //如待分析棋子棋型为五连
        m_LineRecord[nAnalyPos] = FIVE;
        return FIVE;
    }

    if (RightEdge - LeftEdge == 3)
    {
        //如待分析棋子棋型为四连
        bool Leftfour = false;
        if (LeftEdge > 0)
            if (AnalyLine[LeftEdge - 1] == NOSTONE)
                Leftfour = true; //左边有气

        if (RightEdge < GridNum)
        //右边未到边界
        {
            if (AnalyLine[RightEdge + 1] == NOSTONE)
            //右边有气
            {
                if (Leftfour == true)               //如左边有气
                    m_LineRecord[nAnalyPos] = FOUR; //活四
                else
                    m_LineRecord[nAnalyPos] = SFOUR; //冲四
            }
            else if (Leftfour == true)           //如左边有气
                m_LineRecord[nAnalyPos] = SFOUR; //冲四
            else if (Leftfour == true)           //如左边有气
                m_LineRecord[nAnalyPos] = SFOUR; //冲四
        }

        return m_LineRecord[nAnalyPos];
    }

    if (RightEdge - LeftEdge == 2)
    {
        //如待分析棋子棋型为三连
        bool LeftThree = false;

        if (LeftEdge > 1)
        {
            if (AnalyLine[LeftEdge - 1] == NOSTONE)
            { //左边有气
                if (LeftEdge > 1 && AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
                {
                    //左边隔一空白有己方棋子
                    m_LineRecord[LeftEdge] = SFOUR; //冲四
                    m_LineRecord[LeftEdge - 2] = ANALSISED;
                }
                else
                    LeftThree = true;
            }
        }

        if (RightEdge < GridNum)
            if (AnalyLine[RightEdge + 1] == NOSTONE)
                //右边有气
                if (RightEdge < GridNum - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
                {
                    //右边隔1个己方棋子
                    m_LineRecord[RightEdge] = SFOUR; //冲四
                    m_LineRecord[RightEdge + 2] = ANALSISED;
                }
                else if (LeftThree == true)          //如左边有气
                    m_LineRecord[RightEdge] = THREE; //活三
                else
                    m_LineRecord[RightEdge] = STHREE; //冲三
            else
            {
                if (m_LineRecord[LeftEdge] == SFOUR) //如左冲四
                    return m_LineRecord[LeftEdge];   //返回

                if (LeftThree == true)                //如左边有气
                    m_LineRecord[nAnalyPos] = STHREE; //眠三
            }
        else
        {
            if (m_LineRecord[LeftEdge] == SFOUR)  //如左冲四
                return m_LineRecord[LeftEdge];    //返回
            if (LeftThree == true)                //如左边有气
                m_LineRecord[nAnalyPos] = STHREE; //眠三
        }

        return m_LineRecord[nAnalyPos];
    }

    if (RightEdge - LeftEdge == 1)
    {
        //如待分析棋子棋型为二连
        bool Lefttwo = false;
        bool Leftthree = false;

        if (LeftEdge > 2)
        {
            if (AnalyLine[LeftEdge - 1] == NOSTONE)
            //左边有气
            {
                if (LeftEdge - 1 > 1 && AnalyLine[LeftEdge - 2] == AnalyLine[LeftEdge])
                {
                    if (AnalyLine[LeftEdge - 3] == AnalyLine[LeftEdge])
                    {
                        //左边隔2个己方棋子
                        m_LineRecord[LeftEdge - 3] = ANALSISED;
                        m_LineRecord[LeftEdge - 2] = ANALSISED;
                        m_LineRecord[LeftEdge] = SFOUR; //冲四
                    }
                    else if (AnalyLine[LeftEdge - 3] == NOSTONE)
                    {
                        //左边隔1个己方棋子
                        m_LineRecord[LeftEdge - 2] = ANALSISED;
                        m_LineRecord[LeftEdge] = STHREE; //眠三
                    }
                    else
                        Lefttwo = true;
                }
            }
        }

        if (RightEdge < GridNum - 2)
        {
            if (AnalyLine[RightEdge + 1] == NOSTONE)
            //右边有气
            {
                if (RightEdge + 1 < GridNum - 1 && AnalyLine[RightEdge + 2] == AnalyLine[RightEdge])
                    if (AnalyLine[RightEdge + 3] == AnalyLine[RightEdge])
                    {
                        //右边隔两个己方棋子
                        m_LineRecord[RightEdge + 3] = ANALSISED;
                        m_LineRecord[RightEdge + 2] = ANALSISED;
                        m_LineRecord[RightEdge] = SFOUR; //冲四
                    }
                    else if (AnalyLine[RightEdge + 3] == NOSTONE)
                    {
                        //右边隔 1 个己方棋子
                        m_LineRecord[RightEdge + 2] = ANALSISED;
                        m_LineRecord[RightEdge] = STHREE; //眠三
                    }
                    else
                    {
                        if (m_LineRecord[LeftEdge] == SFOUR) //左边冲四
                            return m_LineRecord[LeftEdge];   //返回

                        if (m_LineRecord[LeftEdge] == STHREE) //左边眠三
                            return m_LineRecord[LeftEdge];

                        if (Lefttwo == true)
                            m_LineRecord[nAnalyPos] = TWO; //返回活二
                        else
                            m_LineRecord[nAnalyPos] = STWO; //眠二
                    }
                else
                {
                    if (m_LineRecord[LeftEdge] == SFOUR) //冲四返回
                        return m_LineRecord[LeftEdge];

                    if (Lefttwo == true) //眠二
                        m_LineRecord[nAnalyPos] = STWO;
                }
            }
        }

        return m_LineRecord[nAnalyPos];
    }

    return 0;
}

//分析棋盘上某点在水平方向上的棋型
int AnalysisHorizon(unsigned char position[][GRID_NUM], int i, int j)
{
    //调用直线分析函数分析
    AnalysisLine(position[i], GRID_NUM, j);
    //拾取分析结果
    for (int s = 0; s < GRID_NUM; s++)
        if (m_LineRecord[s] != TOBEANALSIS)
            TypeRecord[i][s][0] = m_LineRecord[s];

    return TypeRecord[i][j][0];
}

//分析棋盘上某点在垂直方向上的棋型
int AnalysisVertical(unsigned char position[][GRID_NUM], int i, int j)
{
    unsigned char tempArray[GRID_NUM];
    //将垂直方向上的棋子转入一维数组
    for (int k = 0; k < GRID_NUM; k++)
        tempArray[k] = position[k][j];
    //调用直线分析函数分析
    AnalysisLine(tempArray, GRID_NUM, i);
    //拾取分析结果
    for (int s = 0; s < GRID_NUM; s++)
        if (m_LineRecord[s] != TOBEANALSIS)
            TypeRecord[s][j][1] = m_LineRecord[s];

    return TypeRecord[i][j][1];
}

//分析棋盘上某点在左斜方向上的棋型
int AnalysisLeft(unsigned char position[][GRID_NUM], int i, int j)
{
    unsigned char tempArray[GRID_NUM];
    int x, y;
    int k;
    if (i < j)
    {
        y = 0;
        x = j - i;
    }
    else
    {
        x = 0;
        y = i - j;
    }
    //将斜方向上的棋子转入一维数组
    for (k = 0; k < GRID_NUM; k++)
    {
        if (x + k > 14 || y + k > 14)
            break;
        tempArray[k] = position[y + k][x + k];
    }
    //调用直线分析函数分析
    AnalysisLine(tempArray, k, j - x);
    //拾取分析结果
    for (int s = 0; s < k; s++)
        if (m_LineRecord[s] != TOBEANALSIS)
            TypeRecord[y + s][x + s][2] = m_LineRecord[s];

    return TypeRecord[i][j][2];
}

//分析棋盘上某点在右斜方向上的棋型
int AnalysisRight(unsigned char position[][GRID_NUM], int i, int j)
{
    unsigned char tempArray[GRID_NUM];
    int x, y, realnum;
    int k;
    if (14 - i < j)
    {
        y = 14;
        x = j - 14 + i;
        realnum = 14 - i;
    }
    else
    {
        x = 0;
        y = i + j;
        realnum = j;
    }
    //将斜方向上的棋子转入一维数组
    for (k = 0; k < GRID_NUM; k++)
    {
        if (x + k > 14 || y - k < 0)
            break;
        tempArray[k] = position[y - k][x + k];
    }
    //调用直线分析函数分析
    AnalysisLine(tempArray, k, j - x);
    //拾取分析结果
    for (int s = 0; s < k; s++)
        if (m_LineRecord[s] != TOBEANALSIS)
            TypeRecord[y - s][x + s][3] = m_LineRecord[s];

    return TypeRecord[i][j][3];
}

int Evaluate(unsigned char position[][GRID_NUM], bool bIsWhiteTurn)
{
    //return wwww(position, bIsWhiteTurn);
    int ret_val;
    int i, j, k;
    unsigned char nStoneType;
    count++; //计数器累加

    //清空棋型分析结果
    memset(TypeRecord, TOBEANALSIS, sizeof(TypeRecord));
    memset(TypeCount, 0, sizeof(TypeCount));

    for (i = 0; i < GRID_NUM; i++)
        for (j = 0; j < GRID_NUM; j++)
        {
            if (position[i][j] != NOSTONE)
            {
                //如果水平方向上没有分析过
                if (TypeRecord[i][j][0] == TOBEANALSIS)
                    AnalysisHorizon(position, i, j);

                //如果垂直方向上没有分析过
                if (TypeRecord[i][j][1] == TOBEANALSIS)
                    AnalysisVertical(position, i, j);

                //如果左斜方向上没有分析过
                if (TypeRecord[i][j][2] == TOBEANALSIS)
                    AnalysisLeft(position, i, j);

                //如果右斜方向上没有分析过
                if (TypeRecord[i][j][3] == TOBEANALSIS)
                    AnalysisRight(position, i, j);
            }
        }

    //对分析结果进行统计,得到每种棋型的数量
    for (i = 0; i < GRID_NUM; i++)
        for (j = 0; j < GRID_NUM; j++)
            for (k = 0; k < 4; k++)
            {
                nStoneType = position[i][j];
                if (nStoneType != NOSTONE)
                {
                    switch (TypeRecord[i][j][k])
                    {
                    case FIVE: //五连
                        TypeCount[nStoneType][FIVE]++;
                        break;
                    case FOUR: //活四
                        TypeCount[nStoneType][FOUR]++;
                        break;
                    case SFOUR: //冲四
                        TypeCount[nStoneType][SFOUR]++;
                        break;
                    case THREE: //活三
                        TypeCount[nStoneType][THREE]++;
                        break;
                    case STHREE: //眠三
                        TypeCount[nStoneType][STHREE]++;
                        break;
                    case TWO: //活二
                        TypeCount[nStoneType][TWO]++;
                        break;
                    case STWO: //眠二
                        TypeCount[nStoneType][STWO]++;
                        break;
                    default:
                        break;
                    }
                }
            }

    //如果已五连,返回极值
    if (bIsWhiteTurn)
    {
        if (TypeCount[BLACK][FIVE])
        {
            return -9999;
        }
        if (TypeCount[WHITE][FIVE])
        {
            return 9999;
        }
    }
    else
    {
        if (TypeCount[BLACK][FIVE])
        {
            return 9999;
        }
        if (TypeCount[WHITE][FIVE])
        {
            return -9999;
        }
    }
    //两个冲四等于一个活四
    if (TypeCount[WHITE][SFOUR] > 1)
        TypeCount[WHITE][FOUR]++;
    if (TypeCount[BLACK][SFOUR] > 1)
        TypeCount[BLACK][FOUR]++;
    int WValue = 0, BValue = 0;

    if (bIsWhiteTurn) //轮到白棋走
    {
        if (TypeCount[WHITE][FOUR])
        {
            //return INF >> 1;
            return 9990; //活四,白胜返回极值
        }
        if (TypeCount[WHITE][SFOUR])
        {
            //return INF >> 2;
            return 9980; //冲四,白胜返回极值
        }
        if (TypeCount[BLACK][FOUR])
        {
            //return -(INF >> 3);
            return -9970; //白无冲四活四,而黑有活四,黑胜返回极值
        }
        if (TypeCount[BLACK][SFOUR] && TypeCount[BLACK][THREE])
        {
            //return -(INF >> 4);
            return -9960; //而黑有冲四和活三,黑胜返回极值
        }
        if (TypeCount[WHITE][THREE] && TypeCount[BLACK][SFOUR] == 0)
        {
            //return INF >> 5;
            return 9950; //白有活三而黑没有四,白胜返回极值
        }
        if (TypeCount[BLACK][THREE] > 1 && TypeCount[WHITE][SFOUR] == 0 && TypeCount[WHITE][THREE] == 0 && TypeCount[WHITE][STHREE] == 0)
        {
            //return -(INF >> 6);
            return -9940; //黑的活三多于一个,而白无四和三,黑胜返回极值
        }

        //fputs("Is White Turn No win\n", stderr);

        if (TypeCount[WHITE][THREE] > 1)
            WValue += 2000; //白活三多于一个,白棋价值加2000
        else
            //否则白棋价值加200
            if (TypeCount[WHITE][THREE])
            WValue += 200;
        if (TypeCount[BLACK][THREE] > 1)
            BValue += 500; //黑的活三多于一个,黑棋价值加500
        else
            //否则黑棋价值加100
            if (TypeCount[BLACK][THREE])
            BValue += 100;
        //每个眠三加10
        if (TypeCount[WHITE][STHREE])
            WValue += TypeCount[WHITE][STHREE] * 10;
        //每个眠三加10
        if (TypeCount[BLACK][STHREE])
            BValue += TypeCount[BLACK][STHREE] * 10;
        //每个活二加4
        if (TypeCount[WHITE][TWO])
            WValue += TypeCount[WHITE][TWO] * 4;
        //每个活二加4
        if (TypeCount[BLACK][STWO])
            BValue += TypeCount[BLACK][TWO] * 4;
        //每个眠二加1
        if (TypeCount[WHITE][STWO])
            WValue += TypeCount[WHITE][STWO];
        //每个眠二加1
        if (TypeCount[BLACK][STWO])
            BValue += TypeCount[BLACK][STWO];
    }
    else //轮到黑棋走
    {
        if (TypeCount[BLACK][FOUR])
        {
            //return INF >> 1;
            return 9990; //活四,黑胜返回极值
        }
        if (TypeCount[BLACK][SFOUR])
        {
            //return INF >> 2;
            return 9980; //冲四,黑胜返回极值
        }
        if (TypeCount[WHITE][FOUR])
            //return -(INF >> 3);
            return -9970; //活四,白胜返回极值

        if (TypeCount[WHITE][SFOUR] && TypeCount[WHITE][THREE])
            //return -(INF >> 4);
            return -9960; //冲四并活三,白胜返回极值

        if (TypeCount[BLACK][THREE] && TypeCount[WHITE][SFOUR] == 0)
            //return (INF >> 5);
            return 9950; //黑活三,白无四。黑胜返回极值

        if (TypeCount[WHITE][THREE] > 1 && TypeCount[BLACK][SFOUR] == 0 && TypeCount[BLACK][THREE] == 0 && TypeCount[BLACK][STHREE] == 0)
            //return -(INF >> 6);
            return -9940; //白的活三多于一个,而黑无四和三,白胜返回极值

        //fputs("Is Black Turn No win\n", stderr);

        //黑的活三多于一个,黑棋价值加2000
        if (TypeCount[BLACK][THREE] > 1)
            BValue += 2000;
        else
            //否则黑棋价值加200
            if (TypeCount[BLACK][THREE])
            BValue += 200;

        //白的活三多于一个,白棋价值加 500
        if (TypeCount[WHITE][THREE] > 1)
            WValue += 500;
        else
            //否则白棋价值加100
            if (TypeCount[WHITE][THREE])
            WValue += 100;

        //每个眠三加10
        if (TypeCount[WHITE][STHREE])
            WValue += TypeCount[WHITE][STHREE] * 10;
        //每个眠三加10
        if (TypeCount[BLACK][STHREE])
            BValue += TypeCount[BLACK][STHREE] * 10;

        //每个活二加4
        if (TypeCount[WHITE][TWO])
            WValue += TypeCount[WHITE][TWO] * 4;
        //每个活二加4
        if (TypeCount[BLACK][STWO])
            BValue += TypeCount[BLACK][TWO] * 4;

        //每个眠二加1
        if (TypeCount[WHITE][STWO])
            WValue += TypeCount[WHITE][STWO];
        //每个眠二加1
        if (TypeCount[BLACK][STWO])
            BValue += TypeCount[BLACK][STWO];
    }

    //加上所有棋子的位置价值
    for (i = 0; i < GRID_NUM; i++)
        for (j = 0; j < GRID_NUM; j++)
        {
            nStoneType = position[i][j];
            if (nStoneType != NOSTONE)
            {
                if (nStoneType == BLACK)
                    BValue += PosValue[i][j];
                else
                    WValue += PosValue[i][j];
            }
        }

    //返回估值
    if (!bIsWhiteTurn)
    {
        //fprintf(stderr, "Is Black Turn return %d\n", BValue - WValue);
        return BValue - WValue;
    }
    else
    {
        //fprintf(stderr, "Is White Turn return %d\n", WValue - BValue);
        return WValue - BValue;
    }
    /*
    if(bIsWhiteTurn)
        _exit(0);
    fprintf(stderr, "Is %d Turn return %d\n", bIsWhiteTurn, ret_val);
    return ret_val;
    */
}