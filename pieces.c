#include "pieces.h"

struct rawTetromino J = {
    .name = "J",
    .width = 4,
    .height = 4,
    .tiles = {
        1, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = ORANGE
};

struct rawTetromino J90 = {
    .name = "J90",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = ORANGE
};

struct rawTetromino J180 = {
    .name = "J180",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0
    },
    .color = ORANGE
};

struct rawTetromino J270 = {
    .name = "J270",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 0, 0,
        0, 1, 0, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = ORANGE
};

struct rawTetromino L = {
    .name = "L",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 1, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = BLUE
};

struct rawTetromino L90 = {
    .name = "L90",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0
    },
    .color = BLUE
};
struct rawTetromino L180 = {
    .name = "L180",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 0, 0,
        1, 1, 1, 0,
        1, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = BLUE
};
struct rawTetromino L270 = {
    .name = "L270",
    .width = 4,
    .height = 4,
    .tiles = {
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = BLUE
};

struct rawTetromino T = {
    .name = "T",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 0, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = PURPLE
};
struct rawTetromino T90 = {
    .name = "T90",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = PURPLE
};
struct rawTetromino T180 = {
    .name = "T180",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = PURPLE
};
struct rawTetromino T270 = {
    .name = "T270",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = PURPLE
};

struct rawTetromino S = {
    .name = "S",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = GREEN
};
struct rawTetromino S90 = {
    .name = "S90",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0
    },
    .color = GREEN
};

struct rawTetromino S180 = {
    .name = "S180",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = GREEN
};

struct rawTetromino S270 = {
    .name = "S270",
    .width = 4,
    .height = 4,
    .tiles = {
        1, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = GREEN
};


struct rawTetromino Z = {
    .name = "Z",
    .width = 4,
    .height = 4,
    .tiles = {
        1, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = RED
};
struct rawTetromino Z90 = {
    .name = "Z90",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = RED
};
struct rawTetromino Z180 = {
    .name = "Z180",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = RED
};
struct rawTetromino Z270 = {
    .name = "Z270",
    .width = 4,
    .height = 4,
    .tiles = {
        1, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 0
    },
    .color = YELLOW
};

struct rawTetromino O = {
    .name = "O",
    .width = 4,
    .height = 4,
    .tiles = {
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    },
    .color = YELLOW
};

struct rawTetromino * pool[] = {&L, &J, &T, &S, &Z, &O};

struct rawTetromino * rotationPool[] = {
    &L, &L90, &L180, &L270, 
    &J, &J90, &J180, &J270, 
    &T, &T90, &T180, &T270, 
    &S, &S90, &S180, &S270,
    &Z, &Z90, &Z180, &Z270,
    &O};

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

// 4 tests for wall kicks when rotation from 0° to 90°
struct wallKick wallKick2 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = 0
    }
};

struct wallKick wallKick3 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = -1
    }
};

struct wallKick wallKick4 = {
    .difficulty = 0,
    .pos = {
        .x = 0,
        .y = 2
    }
};

struct wallKick wallKick5 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = 2
    }
};

// 4 tests for wall kicks when rotation from 90° to 180°
struct wallKick wallKick290 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = 0
    }
};

struct wallKick wallKick390 = {
    .difficulty = 0,
    .pos = {
        .x = 2,
        .y = 0
    }
};

struct wallKick wallKick490 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = -2
    }
};

struct wallKick wallKick590 = {
    .difficulty = 0,
    .pos = {
        .x = 2,
        .y = 1
    }
};

// 4 tests for wall kicks when rotation from 180° to 270°
struct wallKick wallKick2180 = {
    .difficulty = 0,
    .pos = {
        .x = 2,
        .y = 0
    }
};

struct wallKick wallKick3180 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = 0
    }
};

struct wallKick wallKick4180 = {
    .difficulty = 0,
    .pos = {
        .x = 2,
        .y = -1
    }
};

struct wallKick wallKick5180 = {
    .difficulty = 0,
    .pos = {
        .x = -1,
        .y = 2
    }
};

// 4 tests for wall kicks when rotation from 270° to 0°
struct wallKick wallKick2270 = {
    .difficulty = 0,
    .pos = {
        .x = 1,
        .y = 0
    }
};

struct wallKick wallKick3270 = {
    .difficulty = 0,
    .pos = {
        .x = -2,
        .y = 0
    }
};

struct wallKick wallKick4270 = {
    .difficulty = 0,
    .pos = {
        .x = 1,
        .y = 2
    }
};

struct wallKick wallKick5270 = {
    .difficulty = 0,
    .pos = {
        .x = -2,
        .y = -1
    }
};
