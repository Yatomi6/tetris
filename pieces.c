#include "pieces.h"

struct rawTetromino leftL = {
    .tiles = {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0
    },
    .color = MAROON
};

struct rawTetromino * pool = {&leftL};

struct rawTetromino * getPool()
{
    return pool;
}