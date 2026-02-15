#include "pieces.h"
#include <stdbool.h>

#define tilesOnWidth 10
#define tilesOnHeight 18
#define tilesSize 40

#define headerHeight 200

#define borderWidth 20

#define screenWidth (tilesOnWidth * tilesSize + 2 * borderWidth)
#define screenHeight (tilesOnHeight * tilesSize + headerHeight + 3 * borderWidth)

#define topGridCoord (headerHeight + 2 * borderWidth)
#define leftGridCoord (borderWidth)
#define bottomGridCoord (topGridCoord + tilesOnHeight * tilesSize)
#define rightGridCoord (leftGridCoord + tilesOnWidth * tilesSize)

bool updatePiece(
    struct tetromino * piece, 
    bool rotation, 
    int horinzontalDeplacement,
    bool descend,
    bool * grid
);

struct tetromino * initTetromino(struct rawTetromino ** pool);

struct grid{
    bool tiles[180];
};