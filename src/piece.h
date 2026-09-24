#ifndef PIECE_H
#define PIECE_H


#define PIECE_SIZE 4


typedef struct
{
    int shape[PIECE_SIZE][PIECE_SIZE];

    int x;
    int y;

} Piece;


void create_piece(Piece *piece);

void spawn_piece(Piece *piece);


#endif