#include <stdio.h>
#include "game.h"
#include "board.h"

void initialize_game()
{
    printf("Initializing game components...\n");

    initialize_board();

    display_board();
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