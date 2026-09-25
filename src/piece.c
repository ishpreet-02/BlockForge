#include "piece.h"


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

void move_left(Piece *piece)
{
    piece->x--;
}


void move_right(Piece *piece)
{
    piece->x++;
}


void move_down(Piece *piece)
{
    piece->y++;
}