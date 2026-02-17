#include "raylib.h"
#include "string.h"

struct position{
    int x,y;
};

struct rawTetromino {
    const char * name;
    int width;
    int height;
    int tiles[16];
    struct Color color;
};

struct tetromino {
    struct rawTetromino raw;
    struct position pos;
};
 struct wallKick{
    int difficulty; // 0 for J,L,S,Z,T shapes; 1 for I shape
    struct position pos;
 };

struct rawTetromino ** getPool();
struct rawTetromino ** getRotationPool();
void changeTetrominoRawByName(char * rotatedPiece, struct tetromino * piece);

extern struct wallKick wallKick2;
extern struct wallKick wallKick3;
extern struct wallKick wallKick4;
extern struct wallKick wallKick5;

extern struct wallKick wallKick290;
extern struct wallKick wallKick390;
extern struct wallKick wallKick490;
extern struct wallKick wallKick590;

extern struct wallKick wallKick2180;
extern struct wallKick wallKick3180;
extern struct wallKick wallKick4180;
extern struct wallKick wallKick5180;

extern struct wallKick wallKick2270;
extern struct wallKick wallKick3270;
extern struct wallKick wallKick4270;
extern struct wallKick wallKick5270;
