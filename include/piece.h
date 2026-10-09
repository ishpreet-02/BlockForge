#ifndef PIECE_H
#define PIECE_H
#define PIECE_SIZE 4
#define PIECE_COUNT 7

typedef enum
{
    PIECE_I,
    PIECE_O,
    PIECE_T,
    PIECE_S,
    PIECE_Z,
    PIECE_J,
    PIECE_L
} PieceType;

typedef struct
{
    int shape[PIECE_SIZE][PIECE_SIZE];

    int x;
    int y;
    PieceType type;

} Piece;


void create_piece(Piece *piece);

void spawn_piece(Piece *piece);

void move_left(Piece *piece);

void move_right(Piece *piece);

int move_down(Piece *piece);

int try_move(Piece *piece, int dx, int dy);

void rotate_piece(Piece *piece);

void initialize_piece_system(void);

#endif
