#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "define.h"
#include "function.h"
using namespace std;

int main(int argc, char const *argv[])
{
	char input[64] = {0};
	
	init();
	clear();
	puts("This program will exit when it receives EOF.");
	puts("Please INPUT the computer\'s color");
	puts("Input: black -> Computer first");
	puts("Input: white -> Player first");
	puts("Command: move [column] [row]");
	puts("Command: unmove");
	while (true)
	{
		putchar('>');
		if (scanf("%s", input) == EOF)
			goto receiveEOF;
		player_color = WHITE;
		computer_color = BLACK;
		if (strcmp(input, "black") == 0) //电脑先手
		{
			first_flag = COMPUTER;
			break;
		}
		else if (strcmp(input, "white") == 0) //电脑后手
		{
			//player_color = BLACK;
			//computer_color = WHITE;
			first_flag = PLAYER;
			break;
		}
		else
		{
			puts("Invalid command");
			while (getchar() != '\n')
				;
		}
	}
	computer_init_wrapper();
	arg_handler(argc, argv);
	if (first_flag == COMPUTER)
	{
		computer_first_wrapper();
		update_backup();
	}
	clear();
	print();
	while (putchar('>'), ~scanf("%s", input))
	{
		if (strcmp(input, "move") == 0) //玩家落子
		{

			if (scanf("%d%d", &player_move.col, &player_move.row) != 2)
			{
				char ch;
				while ((ch = getchar()) != '\n')
					if (ch == EOF)
						goto receiveEOF;
				puts("Invalid INPUT!");
				continue;
			}
			if (!inboard_wrapper(player_move.row, player_move.col))
			{
				puts("Position NOT in board!");
				continue;
			}
			if (!isEmpty_wrapper(player_move.row, player_move.col))
			{
				puts("Position NOT empty!");
				continue;
			}
			update_backup();
			player_move_wrapper(player_move.row, player_move.col);
			//chessBoard[player_move.row][player_move.col] = player_color;
			clear();
			print_wrapper();
			checkGameOver_wrapper();
			//if (computer_move.moved == true)
			puts("Waiting the computer...");
			computerMove_wrapper(computer_color);
			clear();
			print_wrapper();
			checkGameOver_wrapper();
			validateBoard();

			//player_color = player_color == BLACK ? WHITE : BLACK;
		}
		else if (strcmp(input, "unmove") == 0)
		{
			unmove();
			clear();
			print();
			while (getchar() != '\n')
				;
		}
		else
		{
			puts("Invalid command");
			puts("Command: move [column] [row]");
			while (getchar() != '\n')
				;
		}
	}
receiveEOF:
	puts("Received EOF. Exit.");
	fputs("Received EOF. Exit.\n", fp);
	//system("/bin/bash");
	return 0;
}
