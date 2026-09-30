#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

#include "input.h"


static struct termios original_settings;
static int input_initialized = 0;


/*
 * Configure the terminal so that:
 *
 * 1. Input is received character-by-character.
 * 2. Typed characters are not displayed.
 */
void initialize_input(void)
{
    if(input_initialized)
    {
        return;
    }

    tcgetattr(STDIN_FILENO, &original_settings);

    struct termios new_settings = original_settings;

    new_settings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    input_initialized = 1;
}


/*
 * Restore the terminal to its original state.
 */
void shutdown_input(void)
{
    if(!input_initialized)
    {
        return;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original_settings);

    input_initialized = 0;
}


/*
 * Check for keyboard input without blocking
 * the game loop.
 *
 * Returns:
 *
 * 'a', 'd', 's', 'q' etc. → key pressed
 * '\0'                    → no key pressed
 */
char get_input(void)
{
    fd_set input_set;

    struct timeval timeout;

    FD_ZERO(&input_set);
    FD_SET(STDIN_FILENO, &input_set);


    /*
     * Wait for at most 50 milliseconds.
     *
     * This allows the game to continue running
     * even when the player does not press a key.
     */
    timeout.tv_sec = 0;
    timeout.tv_usec = 50000;


    int result = select(
        STDIN_FILENO + 1,
        &input_set,
        NULL,
        NULL,
        &timeout
    );


    if(result > 0 && FD_ISSET(STDIN_FILENO, &input_set))
    {
        return getchar();
    }


    return '\0';
}