#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "board.h"
#include "piece.h"

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
                printf("[] ");
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

void display_board_with_piece(Piece *piece)
{
    printf("+--------------------+\n");


    for(int row = 0; row < BOARD_ROWS; row++)
    {
        printf("|");

        for(int col = 0; col < BOARD_COLS; col++)
        {
            int printed = 0;


            for(int pRow = 0; pRow < PIECE_SIZE; pRow++)
            {
                for(int pCol = 0; pCol < PIECE_SIZE; pCol++)
                {

                    if(piece->shape[pRow][pCol] == 1 &&
                       piece->y + pRow == row &&
                       piece->x + pCol == col)
                    {
                        printf("# ");
                        printed = 1;
                    }

                }
            }


            if(!printed)
            {
                printf(". ");
            }
        }

        printf("|\n");
    }


    printf("+--------------------+\n");
    printf("a/d: move  s: down  q: quit\033[K\n");
    printf("\033[J");
    fflush(stdout);
}

static void on_sigint(int sig)
{
    (void)sig;
    const char seq[] = "[?25h[?1049l";
    write(STDOUT_FILENO, seq, sizeof(seq) - 1);
    _exit(0);
}

void enter_screen(void)
{
    signal(SIGINT, on_sigint);
    printf("[?1049h[?25l[2J[H");
    fflush(stdout);
}

void leave_screen(void)
{
    printf("[?1049l[?25h");
    fflush(stdout);
}

void clear_screen(void)
{
    printf("[H");
}
