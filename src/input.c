#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "input.h"


char get_input()
{
    struct termios old_settings;
    struct termios new_settings;

    char input;


    tcgetattr(STDIN_FILENO, &old_settings);


    new_settings = old_settings;


    new_settings.c_lflag &= ~(ICANON | ECHO);


    tcsetattr(
        STDIN_FILENO,
        TCSANOW,
        &new_settings
    );


    input = getchar();


    tcsetattr(
        STDIN_FILENO,
        TCSANOW,
        &old_settings
    );


    return input;
}   