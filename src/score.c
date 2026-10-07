#include "score.h"

static int score = 0;
static int total_lines_cleared = 0;

void initialize_score(void)
{
    score = 0;
    total_lines_cleared = 0;
}

void update_score(int lines_cleared)
{
    switch(lines_cleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
        default:
            break;
    }

    total_lines_cleared += lines_cleared;
}

int get_score(void)
{
    return score;
}

int get_lines_cleared(void)
{
    return total_lines_cleared;
}

