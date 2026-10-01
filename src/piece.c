#include <stdlib.h>
#include <time.h>

#include "piece.h"
#include "collision.h"

/*
 * Seven Tetromino shapes.
 *
 * Every piece is stored inside a 4x4 matrix.
 */
static const int piece_shapes[PIECE_COUNT][PIECE_SIZE][PIECE_SIZE] =
{
    /* I */
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    /* O */
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    /* T */
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    /* S */
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    /* Z */
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    /* J */
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    /* L */
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

/*
 * The bag contains one instance of every Tetromino.
 */
static PieceType piece_bag[PIECE_COUNT];

/*
 * Index of the next piece to take from the bag.
 */
static int bag_index = PIECE_COUNT;


/*
 * Initialize the random number generator.
 */
void initialize_piece_system(void)
{
    srand((unsigned int)time(NULL));

    bag_index = PIECE_COUNT;
}


/*
 * Shuffle the seven pieces using Fisher-Yates shuffle.
 */
static void refill_bag(void)
{
    for(int i = 0; i < PIECE_COUNT; i++)
    {
        piece_bag[i] = (PieceType)i;
    }

    for(int i = PIECE_COUNT - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        PieceType temp = piece_bag[i];
        piece_bag[i] = piece_bag[j];
        piece_bag[j] = temp;
    }

    bag_index = 0;
}


/*
 * Get the next Tetromino type from the bag.
 */
static PieceType get_next_piece_type(void)
{
    if(bag_index >= PIECE_COUNT)
    {
        refill_bag();
    }

    return piece_bag[bag_index++];
}


/*
 * Create a new Tetromino.
 */
void create_piece(Piece *piece)
{
    piece->type = get_next_piece_type();

    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            piece->shape[row][col] =
                piece_shapes[piece->type][row][col];
        }
    }
}


/*
 * Place the piece at the starting position.
 */
void spawn_piece(Piece *piece)
{
    piece->x = 3;
    piece->y = 0;
}


/*
 * Try to move the piece.
 *
 * Returns:
 * 1 -> movement successful
 * 0 -> movement rejected
 */
int try_move(Piece *piece, int dx, int dy)
{
    piece->x += dx;
    piece->y += dy;

    if(check_collision(piece))
    {
        piece->x -= dx;
        piece->y -= dy;

        return 0;
    }

    return 1;
}


/*
 * Move piece left.
 */
void move_left(Piece *piece)
{
    try_move(piece, -1, 0);
}


/*
 * Move piece right.
 */
void move_right(Piece *piece)
{
    try_move(piece, 1, 0);
}


/*
 * Move piece down.
 */
int move_down(Piece *piece)
{
    return try_move(piece, 0, 1);
}


/*
 * Rotate the piece 90 degrees clockwise.
 */
void rotate_piece(Piece *piece)
{
    /*
     * The O piece is symmetrical,
     * so rotation has no visible effect.
     */
    if(piece->type == PIECE_O)
    {
        return;
    }

    int rotated_shape[PIECE_SIZE][PIECE_SIZE];
    int original_shape[PIECE_SIZE][PIECE_SIZE];

    /*
     * Calculate the rotated matrix.
     */
    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            rotated_shape[row][col] =
                piece->shape[PIECE_SIZE - 1 - col][row];
        }
    }

    /*
     * Save the original shape and
     * temporarily apply the rotation.
     */
    for(int row = 0; row < PIECE_SIZE; row++)
    {
        for(int col = 0; col < PIECE_SIZE; col++)
        {
            original_shape[row][col] =
                piece->shape[row][col];

            piece->shape[row][col] =
                rotated_shape[row][col];
        }
    }

    /*
     * Reject the rotation if it causes
     * a collision with the board or blocks.
     */
    if(check_collision(piece))
    {
        for(int row = 0; row < PIECE_SIZE; row++)
        {
            for(int col = 0; col < PIECE_SIZE; col++)
            {
                piece->shape[row][col] =
                    original_shape[row][col];
            }
        }
    }
}
