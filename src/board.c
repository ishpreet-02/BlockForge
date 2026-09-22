#include <stdio.h>
#include "board.h"


int board[BOARD_ROWS][BOARD_COLS];


void initialize_board()
{
    for(int row = 0; row < BOARD_ROWS; row++)
    {
        for(int col = 0; col < BOARD_COLS; col++)
        {
            board[row][col] = 0;
        }
    }
}


void display_board()
{
    printf("+");

    for(int col = 0; col < BOARD_COLS; col++)
    {
        printf("--");
    }

    printf("+\n");


    for(int row = 0; row < BOARD_ROWS; row++)
    {
        printf("|");

        for(int col = 0; col < BOARD_COLS; col++)
        {
            if(board[row][col] == 0)
            {
                printf(". ");
            }
            else
            {
                printf("# ");
            }
        }

        printf("|\n");
    }


    printf("+");

    for(int col = 0; col < BOARD_COLS; col++)
    {
        printf("--");
    }

    printf("+\n");
}