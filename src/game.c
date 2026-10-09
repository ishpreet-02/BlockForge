#include <stdio.h>
#include <time.h>

#include "game.h"
#include "board.h"
#include "piece.h"
#include "input.h"
#include "collision.h"
#include "score.h"

#define GRAVITY_INTERVAL_MS 500

void initialize_game() {
    printf("Initializing game components...\n");

    initialize_board();
    initialize_piece_system();
    initialize_score();
}

void run_game() {
    Piece current_piece;

    create_piece(&current_piece);
    spawn_piece(&current_piece);

    /* If spawn position is occupied, the game cannot start */
    if (check_collision(&current_piece)) {
        printf("\nGAME OVER!\n");
        return;
    }

    int running = 1;
    int game_over = 0;
    long long last_gravity_time = 0;

    initialize_input();
    enter_screen();

    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    last_gravity_time =
        (long long)start_time.tv_sec * 1000 +
        start_time.tv_nsec / 1000000;

    while (running) {
        clear_screen();

        printf("BLOCKFORGE\n");
        printf("Score: %d\n", get_score());
        printf("Lines: %d\n\n", get_lines_cleared());

        display_board_with_piece(&current_piece);

        char key = get_input();

        if (key == 'a') {
            move_left(&current_piece);
        } else if (key == 'd') {
            move_right(&current_piece);
        } else if (key == 'w') {
            rotate_piece(&current_piece);
        } else if (key == 's') {
            if (!move_down(&current_piece)) {
                lock_piece(&current_piece);

                int lines_cleared = clear_completed_lines();
                update_score(lines_cleared);

                create_piece(&current_piece);
                spawn_piece(&current_piece);

                /* If new piece collides immediately, game is over */
                if (check_collision(&current_piece)) {
                    game_over = 1;
                    running = 0;
                }
            }
        } else if (key == 'q') {
            running = 0;
        }

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        long long current_time_ms =
            (long long)current_time.tv_sec * 1000 +
            current_time.tv_nsec / 1000000;

        long long elapsed_time = current_time_ms - last_gravity_time;

        if (elapsed_time >= GRAVITY_INTERVAL_MS && running) {
            if (!move_down(&current_piece)) {
                lock_piece(&current_piece);

                int lines_cleared = clear_completed_lines();
                update_score(lines_cleared);

                create_piece(&current_piece);
                spawn_piece(&current_piece);

                /* If new piece collides immediately, game is over */
                if (check_collision(&current_piece)) {
                    game_over = 1;
                    running = 0;
                }
            }

            last_gravity_time = current_time_ms;
        }
    }

    shutdown_input();
    leave_screen();

    if (game_over) {
        printf("\n====================\n");
        printf("     GAME OVER!\n");
        printf("====================\n");
        printf("Score: %d\n", get_score());
        printf("Lines: %d\n", get_lines_cleared());
    }
}

void shutdown_game() {
    printf("\nGame ended.\n");
}
