#ifndef BOARD_H
#define BOARD_H
#define BOARD_ROWS 20
#define BOARD_COLS 10

#include "piece.h"


void initialize_board();

void display_board();

void display_board_with_piece(Piece *piece);

void clear_screen();


#endif