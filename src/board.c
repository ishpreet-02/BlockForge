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


            /*
             * First check whether the active piece
             * occupies this board position.
             */
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
                        break;
                    }
                }

                if(printed)
                {
                    break;
                }
            }


            /*
             * If the active piece does not occupy
             * this position, display the locked board.
             */
            if(!printed)
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
        }

        printf("|\n");
    }


    printf("+--------------------+\n");
    printf("a/d: move  w: rotate  s: down  q: quit\033[K\n");

    printf("\033[J");

    fflush(stdout);
}


/*
 * Permanently store the active piece inside board[][].
 */
void lock_piece(Piece *piece)
{
    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            if(piece->shape[row][col] == 0)
            {
                continue;
            }

            int board_row = piece->y + row;
            int board_col = piece->x + col;

            if(board_row >= 0 && board_row < BOARD_ROWS &&
               board_col >= 0 && board_col < BOARD_COLS)
            {
                board[board_row][board_col] = 1;
            }
        }
    }
}


static void on_sigint(int sig)
{
    (void)sig;

    const char seq[] = "\033[?25h\033[?1049l";

    write(STDOUT_FILENO, seq, sizeof(seq) - 1);

    _exit(0);
}


void enter_screen(void)
{
    signal(SIGINT, on_sigint);

    printf("\033[?1049h\033[?25l\033[2J\033[H");

    fflush(stdout);
}


void leave_screen(void)
{
    printf("\033[?25h\033[?1049l");

    fflush(stdout);
}


void clear_screen(void)
{
    printf("\033[H");
}
