#include <stdio.h>
#include "game.h"
#include "board.h"
#include "piece.h"

void initialize_game()
{
    printf("Initializing game components...\n");
    initialize_board();

    Piece current_piece;

    create_piece(&current_piece);
    spawn_piece(&current_piece);
    display_board_with_piece(&current_piece);
}

void run_game()
{
    printf("Game loop started...\n");

    int running = 1;


    while(running)
    {
        printf("Game frame running...\n");

        running = 0;
    }
}


void shutdown_game()
{
    printf("Closing Tetris Engine...\n");
}