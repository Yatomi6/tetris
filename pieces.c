#include "pieces.h"

struct rawTetromino J = {
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        0, 1, 0,
        0, 1, 1
    },
    .color = ORANGE
};

struct rawTetromino L = {
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        0, 1, 0,
        1, 1, 0
    },
    .color = BLUE
};

struct rawTetromino * pool[] = {&L, &J};

struct rawTetromino ** getPool()
{
    return pool;
}