#include <stdio.h>
#include <time.h>

#include "game.h"
#include "board.h"
#include "piece.h"
#include "input.h"

#define GRAVITY_INTERVAL_MS 500


void initialize_game()
{
    printf("Initializing game components...\n");

    initialize_board();
}


void run_game()
{
    Piece current_piece;

    create_piece(&current_piece);
    spawn_piece(&current_piece);


    int running = 1;

    long long last_gravity_time = 0;


    initialize_input();
    enter_screen();

    struct timespec start_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    last_gravity_time =
        (long long)start_time.tv_sec * 1000 +
        start_time.tv_nsec / 1000000;


    while(running)
    {
        clear_screen();
        display_board_with_piece(&current_piece);

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
            /*
             * Manual soft drop.
             *
             * If the piece cannot move down,
             * lock it and spawn another piece.
             */
            if(!move_down(&current_piece))
            {
                lock_piece(&current_piece);

                create_piece(&current_piece);
                spawn_piece(&current_piece);
            }
        }
        else if(key == 'q')
        {
            running = 0;
        }


        /*
         * -----------------------------
         * AUTOMATIC GRAVITY
         * -----------------------------
         */

        struct timespec current_time;

        clock_gettime(CLOCK_MONOTONIC, &current_time);


        long long current_time_ms =
            (long long)current_time.tv_sec * 1000 +
            current_time.tv_nsec / 1000000;


        long long elapsed_time =
            current_time_ms - last_gravity_time;


        /*
         * Has enough time passed for the
         * piece to fall automatically?
         */
        if(elapsed_time >= GRAVITY_INTERVAL_MS)
        {
            /*
             * Try to move the piece down.
             */
            if(!move_down(&current_piece))
            {
                /*
                 * The piece cannot move down.
                 * Therefore lock it.
                 */
                lock_piece(&current_piece);


                /*
                 * Create and spawn the next piece.
                 */
                create_piece(&current_piece);
                spawn_piece(&current_piece);
            }


            /*
             * Reset gravity timer.
             */
            last_gravity_time = current_time_ms;
        }
    }


    shutdown_input();

    leave_screen();
}


void shutdown_game()
{
    printf("\nGame ended.\n");
}