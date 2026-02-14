#include "raylib.h"

struct position{
    int x,y;
};

struct rawTetromino {
    int tiles[16];
    struct Color color;
};

struct tetromino {
    struct rawTetromino raw;
    struct position pos;
};

struct rawTetromino * getPool();