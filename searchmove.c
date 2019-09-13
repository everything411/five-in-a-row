#include "define.h"
#include "function.h"
#include <string.h>
#include <time.h>

int nega_search(int depth, int alpha, int beta)
{
    int Count, i;
    unsigned char type;
    int a, b, t;
    int side;
    int score;

    side = (max_depth - depth) % 2;
    if (depth <= 0) //叶子节点取估值
    {
        score = Evaluate(curr_pos, side);
        /*
        if (debug)
        {
            printf("count %d score %d\n", debug);
        }
        */
        return score;
    }
    Count = CreatePossibleMove(curr_pos, depth, side);
    MergeSort(MoveList[depth], Count, 0);
    int bestmove = -1;
    a = alpha;
    b = beta;

    int eval_is_exact = 0;

    for (i = 0; i < Count; i++)
    {
        type = MakeMove(&MoveList[depth][i], side);
        t = -nega_search(depth - 1, -b, -a);
        if (t > a && t < beta && i > 0)
        {
            a = -nega_search(depth - 1, -beta, -t);
            eval_is_exact = 1;
            if (depth == max_depth)
                best_choice = MoveList[depth][i];
            bestmove = i;
        }
        UnMakeMove(&MoveList[depth][i]);
        if (a < t)
        {
            eval_is_exact = 1;
            a = t;
            if (depth == max_depth)
                best_choice = MoveList[depth][i];
        }
        if (a >= beta)
        {
            return a;
        }
        b = a + 1;
    }

    return a;
}

void get_best_step(unsigned char position[][GRID_NUM], int Type)
{
    static clock_t _time = 0;

    //int Score;

    memcpy(curr_pos, position, GRID_COUNT);
    max_depth = search_depth;
    //Score = nega_search(max_depth, -200000, 200000);
    nega_search(max_depth, -200000, 200000);
    X = best_choice.StonePos.y;
    Y = best_choice.StonePos.x;
    MakeMove(&best_choice, Type);
    memcpy(position, curr_pos, GRID_COUNT);
    search_time = clock() - _time;
    _time = clock();
    return;
}
