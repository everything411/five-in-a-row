#include "define.h"

unsigned char MakeMove(STONEMOVE *move, int type)
{
    CurPosition[move->StonePos.y][move->StonePos.x] = type;
    return 0;
}

void UnMakeMove(STONEMOVE *move)
{
    CurPosition[move->StonePos.y][move->StonePos.x] = NOSTONE;
}