#include "collision.h"
#include "board.h"


int check_collision(Piece *piece)
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


            if(board_col < 0 || board_col >= BOARD_COLS)
            {
                return 1;
            }


            if(board_row < 0 || board_row >= BOARD_ROWS)
            {
                return 1;
            }


            if(board[board_row][board_col] != 0)
            {
                return 1;
            }
        }
    }

    return 0;
}