#include "pieces.h"

struct rawTetromino J = {
    .name = "J",
    .width = 3,
    .height = 3,
    .tiles = {
        1, 0, 0,
        1, 1, 1,
        0, 0, 0
    },
    .color = ORANGE
};

struct rawTetromino J90 = {
    .name = "J90",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 1,
        0, 1, 0,
        0, 1, 0
    },
    .color = ORANGE
};

struct rawTetromino J180 = {
    .name = "J180",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 0,
        1, 1, 1,
        0, 0, 1
    },
    .color = ORANGE
};

struct rawTetromino J270 = {
    .name = "J270",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        0, 1, 0,
        1, 1, 0
    },
    .color = ORANGE
};

struct rawTetromino L = {
    .name = "L",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 1,
        1, 1, 1,
        0, 0, 0
    },
    .color = BLUE
};

struct rawTetromino L90 = {
    .name = "L90",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        0, 1, 0,
        0, 1, 1
    },
    .color = BLUE
};
struct rawTetromino L180 = {
    .name = "L180",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 0,
        1, 1, 1,
        1, 0, 0
    },
    .color = BLUE
};
struct rawTetromino L270 = {
    .name = "L270",
    .width = 3,
    .height = 3,
    .tiles = {
        1, 1, 0,
        0, 1, 0,
        0, 1, 0
    },
    .color = BLUE
};

struct rawTetromino T = {
    .name = "T",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        1, 1, 1,
        0, 0, 0
    },
    .color = PURPLE
};
struct rawTetromino T90 = {
    .name = "T90",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        0, 1, 1,
        0, 1, 0
    },
    .color = PURPLE
};
struct rawTetromino T180 = {
    .name = "T180",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 0,
        1, 1, 1,
        0, 1, 0
    },
    .color = PURPLE
};
struct rawTetromino T270 = {
    .name = "T270",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        1, 1, 0,
        0, 1, 0
    },
    .color = PURPLE
};

struct rawTetromino S = {
    .name = "S",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 1,
        1, 1, 0,
        0, 0, 0
    },
    .color = GREEN
};
struct rawTetromino S90 = {
    .name = "S90",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 1, 0,
        0, 1, 1,
        0, 0, 1
    },
    .color = GREEN
};

struct rawTetromino S180 = {
    .name = "S180",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 0,
        0, 1, 1,
        1, 1, 0
    },
    .color = GREEN
};

struct rawTetromino S270 = {
    .name = "S270",
    .width = 3,
    .height = 3,
    .tiles = {
        1, 0, 0,
        1, 1, 0,
        0, 1, 0
    },
    .color = GREEN
};


struct rawTetromino Z = {
    .name = "Z",
    .width = 3,
    .height = 3,
    .tiles = {
        1, 1, 0,
        0, 1, 1,
        0, 0, 0
    },
    .color = RED
};
struct rawTetromino Z90 = {
    .name = "Z90",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 1,
        0, 1, 1,
        0, 1, 0
    },
    .color = RED
};
struct rawTetromino Z180 = {
    .name = "Z180",
    .width = 3,
    .height = 3,
    .tiles = {
        0, 0, 0,
        0, 1, 1,
        1, 1, 0
    },
    .color = RED
};
struct rawTetromino Z270 = {
    .name = "Z270",
    .width = 3,
    .height = 3,
    .tiles = {
        1, 0, 0,
        1, 1, 0,
        0, 1, 0
    },
    .color = RED
};

struct rawTetromino * pool[] = {&L, &J, &T, &S, &Z};

struct rawTetromino * rotationPool[] = {
    &L, &L90, &L180, &L270, 
    &J, &J90, &J180, &J270, 
    &T, &T90, &T180, &T270, 
    &S, &S90, &S180, &S270,
    &Z, &Z90, &Z180, &Z270};

struct rawTetromino ** getPool()
{
    return pool;
}

struct rawTetromino ** getRotationPool()
{
    return rotationPool;
}

void changeTetrominoRawByName(char * rotatedPiece, struct tetromino * piece){
    for (int i = 0; i<(int)(sizeof(rotationPool)/sizeof(rotationPool[0])); i++){
        if (strcmp(rotationPool[i]->name, rotatedPiece) == 0){
            piece->raw = *rotationPool[i];
        }
    }
}