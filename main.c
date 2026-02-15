#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void drawUI()
{
    DrawRectangle(0, 0, screenWidth, borderWidth, BLACK);
    DrawRectangle(0, screenHeight - borderWidth, screenWidth, borderWidth, BLACK);
    DrawRectangle(0, headerHeight + borderWidth, screenWidth, borderWidth, BLACK);
    DrawRectangle(0, 0, borderWidth, screenHeight, BLACK);
    DrawRectangle(screenWidth - borderWidth, 0, borderWidth, screenHeight, BLACK);
}

void drawTetromino(struct tetromino piece)
{
    int width = piece.raw.width;
    int nbTiles = width * width;
    for (int i = 0; i<nbTiles; i++){
        if (piece.raw.tiles[i]){
            int x = piece.pos.x + i % width;
            int y = piece.pos.y + i / width;
            int gridX = leftGridCoord;
            int gridY = topGridCoord;
            DrawRectangle(gridX + x * tilesSize, gridY + y * tilesSize, tilesSize, tilesSize, piece.raw.color);
        }
    }
}

struct tetromino * initTetromino(struct rawTetromino ** pool)
{
    struct tetromino * new = malloc(sizeof(struct tetromino));
    new->raw = *pool[rand() % 5];
    new->pos.x = 5;
    new->pos.y = 0;
    return new;
}

bool updatePiece(struct tetromino * piece, bool rotation, int horinzontalDeplacement, bool descend, bool * grid)
{
    (void) rotation;
    
    if (horinzontalDeplacement != 0){
        if (horinzontalDeplacement > 0){
            bool isPossible = true;
            int tileNumber = piece->raw.width * piece->raw.width;
            for (int i = 0; i<tileNumber; i++){
                int x = i % piece->raw.width + piece->pos.x;
                int y = i / piece->raw.width + piece->pos.y;
                int pos = x + 10 * y;
                int posFuture = pos + 1;
                if (piece->raw.tiles[i]){
                if (x+1 == 10 || grid[posFuture] == true){
                    isPossible = false;
                    }
                }
            }
            if (isPossible){
                piece->pos.x += 1;
            }
        }
        else{
            bool isPossible = true;
            int tileNumber = piece->raw.width * piece->raw.width;
            for (int i = 0; i<tileNumber; i++){
                int x = i % piece->raw.width + piece->pos.x;
                int y = i / piece->raw.width + piece->pos.y;
                int pos = x + 10 * y;
                int posFuture = pos - 1;
                if (piece->raw.tiles[i]){
                    if (x == 0 || grid[posFuture] == true){
                        isPossible = false;
                    }
                }
            }
            if (isPossible){
                piece->pos.x -= 1;
            }
        }
    }

    bool markGrid = false;
    if (descend) {
        bool isPossible = true;
        int tileNumber = piece->raw.width * piece->raw.width;
        for (int i = 0; i<tileNumber; i++){
            int x = i % piece->raw.width + piece->pos.x;
            int y = i / piece->raw.width + piece->pos.y;
            int pos = x + 10 * y;
            int posFuture = pos + 10;
            if (piece->raw.tiles[i]){
            if (posFuture >= 180 || grid[posFuture] == true){
                isPossible = false;
                markGrid = true;
                }
            }
        }
        if (isPossible){
            piece->pos.y += 1;
        }
    }

    if (markGrid){
        int tileNumber = piece->raw.width * piece->raw.width;
        for (int i = 0; i<tileNumber; i++){
            int x = i % piece->raw.width + piece->pos.x;
            int y = i / piece->raw.width + piece->pos.y;
            int pos = x + 10 * y;
            if (piece->raw.tiles[i]){
                grid[pos] = true;
            }
        }
        return true;
    }
    return false;
}

int getHorizontalMove(float dt) {
    const float das = 0.12f;   // Délai avant auto-repeat
    const float arr = 0.05f;   // Intervalle de repeat
    static float holdTimer = 0.0f;
    static float repeatTimer = 0.0f;
    static int heldDir = 0;     // -1 gauche, +1 droite

    int pressedDir = 0;
    if (IsKeyPressed(KEY_LEFT)) {
        pressedDir = -1;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        pressedDir = 1;
    }
    if (pressedDir != 0) {
        heldDir = pressedDir;
        holdTimer = 0.0f;
        repeatTimer = 0.0f;
        return heldDir;
    }

    bool leftDown = IsKeyDown(KEY_LEFT);
    bool rightDown = IsKeyDown(KEY_RIGHT);
    int downDir = 0;
    if (leftDown && !rightDown) {
        downDir = -1;
    } else if (rightDown && !leftDown) {
        downDir = 1;
    }

    if (downDir == 0) {
        heldDir = 0;
        holdTimer = 0.0f;
        repeatTimer = 0.0f;
        return 0;
    }

    if (downDir != heldDir) {
        heldDir = downDir;
        holdTimer = 0.0f;
        repeatTimer = 0.0f;
        return heldDir;
    }

    holdTimer += dt;
    if (holdTimer < das) {
        return 0;
    }

    repeatTimer += dt;
    if (repeatTimer >= arr) {
        repeatTimer -= arr;
        return heldDir;
    }

    return 0;
}

int getVerticalMove(float dt)
{
    const float das = 0.12f;   // Délai avant auto-repeat
    const float arr = 0.05f;   // Intervalle de repeat
    static float holdTimer = 0.0f;
    static float repeatTimer = 0.0f;

    if (IsKeyPressed(KEY_DOWN)) {
        holdTimer = 0.0f;
        repeatTimer = 0.0f;
        return 1;
    }

    if (!IsKeyDown(KEY_DOWN)) {
        holdTimer = 0.0f;
        repeatTimer = 0.0f;
        return 0;
    }

    holdTimer += dt;
    if (holdTimer < das) {
        return 0;
    }

    repeatTimer += dt;
    if (repeatTimer >= arr) {
        repeatTimer -= arr;
        return 1;
    }

    return 0;
}

int main(void)
{
    srand(1);
    InitWindow(screenWidth, screenHeight, "Tetris");

    struct tetromino * tetrominos = malloc(100 * sizeof(struct tetromino));
    tetrominos[0] = *initTetromino(getPool());
    int numberOfTetrominos = 1;

    drawUI();

    SetTargetFPS(60);

    float fallTimer = 0.0f;
    const float fallStep = 0.5f;    // 2 updates/sec pour la chute

    bool mainGrid[180];
    for (int i = 0; i<180;i++){
        mainGrid[i] = false;
    }

    bool dropped = false;
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        float dt = GetFrameTime();
        int moveCmd = getHorizontalMove(dt);
        if (moveCmd != 0){
            updatePiece(&tetrominos[numberOfTetrominos-1], false, moveCmd, false, mainGrid);
        }
        int moveVerticalCommand = getVerticalMove(dt);
        if (moveVerticalCommand != 0){
            dropped = updatePiece(&tetrominos[numberOfTetrominos-1], false, 0, true, mainGrid) || dropped;
        }

        fallTimer += dt;
        if (fallTimer >= fallStep) {
            dropped = updatePiece(&tetrominos[numberOfTetrominos - 1], false, 0, true, mainGrid) || dropped;
            fallTimer -= fallStep;
        }
        if (dropped){
            tetrominos[numberOfTetrominos] = *initTetromino(getPool());
            numberOfTetrominos ++;
            dropped = false;
        }
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawUI();

            for (int i = 0; i<numberOfTetrominos; i ++){
                drawTetromino(tetrominos[i]);
            }
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free(tetrominos);
    return 0;
}
