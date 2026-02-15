#include "raylib.h"
#include "string.h"

struct position{
    int x,y;
};

struct rawTetromino {
    const char * name;
    int width;
    int height;
    int tiles[9];
    struct Color color;
};

struct tetromino {
    struct rawTetromino raw;
    struct position pos;
};

struct rawTetromino ** getPool();
struct rawTetromino ** getRotationPool();
void changeTetrominoRawByName(char * rotatedPiece, struct tetromino * piece);