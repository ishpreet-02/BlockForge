#include <stdio.h>
#include "game.h"
#include "board.h"
#include "piece.h"
#include "input.h"

void initialize_game()
{
    printf("Initializing game components...\n");
    initialize_board();

    Piece current_piece;

    create_piece(&current_piece);
    spawn_piece(&current_piece);

    clear_screen();
    display_board_with_piece(&current_piece);
}

void run_game()
{
    Piece current_piece;


    create_piece(&current_piece);

    spawn_piece(&current_piece);


    int running = 1;


    while(running)
    {
        char key = get_input();


        if(key == 'a')
        {
            move_left(&current_piece);
        }


        else if(key == 'd')
        {
            move_right(&current_piece);
        }


        else if(key == 's')
        {
            move_down(&current_piece);
        }


        else if(key == 'q')
        {
            running = 0;
        }


        display_board_with_piece(&current_piece);
    }
}


void shutdown_game()
{
    printf("Closing Tetris Engine...\n");
}