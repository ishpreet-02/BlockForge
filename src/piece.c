#include "piece.h"
#include "collision.h"


void create_piece(Piece *piece)
{
    int default_piece[PIECE_SIZE][PIECE_SIZE] =
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };


    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            piece->shape[row][col] = default_piece[row][col];
        }
    }


    piece->x = 3;
    piece->y = 0;
}


void spawn_piece(Piece *piece)
{
    piece->x = 3;
    piece->y = 0;
}


int try_move(Piece *piece, int dx, int dy)
{
    piece->x += dx;
    piece->y += dy;


    if(check_collision(piece))
    {
        piece->x -= dx;
        piece->y -= dy;

        return 0;
    }


    return 1;
}


void move_left(Piece *piece)
{
    try_move(piece, -1, 0);
}


void move_right(Piece *piece)
{
    try_move(piece, 1, 0);
}


int move_down(Piece *piece)
{
    return try_move(piece, 0, 1);
}


void rotate_piece(Piece *piece)
{
    int rotated_shape[PIECE_SIZE][PIECE_SIZE];

    /*
     * Rotate the piece 90 degrees clockwise.
     *
     * Formula:
     *
     * rotated[row][col] =
     *     original[PIECE_SIZE - 1 - col][row]
     */
    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            rotated_shape[row][col] =
                piece->shape[PIECE_SIZE - 1 - col][row];
        }
    }


    /*
     * Temporarily apply the rotation.
     */
    int original_shape[PIECE_SIZE][PIECE_SIZE];

    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            original_shape[row][col] = piece->shape[row][col];

            piece->shape[row][col] = rotated_shape[row][col];
        }
    }


    /*
     * If rotation causes a collision,
     * restore the original shape.
     */
    if(check_collision(piece))
    {
        for(int row = 0; row < PIECE_SIZE; row++)
        {
            for(int col = 0; col < PIECE_SIZE; col++)
            {
                piece->shape[row][col] =
                    original_shape[row][col];
            }
        }
    }
}
