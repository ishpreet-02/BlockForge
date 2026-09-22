#include <stdio.h>
#include "game.h"


int main()
{
    printf("Starting Tetris Engine...\n");

    initialize_game();

    run_game();

    shutdown_game();

    return 0;
}