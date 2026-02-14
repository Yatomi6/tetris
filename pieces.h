#include "raylib.h"

struct position{
    int x,y;
};

struct rawTetromino {
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