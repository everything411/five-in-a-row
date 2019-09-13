#include "define.h"

unsigned char MakeMove(move_step_t *move, int type)
{
    curr_pos[move->StonePos.y][move->StonePos.x] = type;
    return 0;
}

void UnMakeMove(move_step_t *move)
{
    curr_pos[move->StonePos.y][move->StonePos.x] = NOSTONE;
}