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

struct tetromino * initTetromino(int seed, struct rawTetromino ** pool)
{
    struct tetromino * new = malloc(sizeof(struct tetromino));
    new->raw = *pool[seed % 3];
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
            if (posFuture >= 180 || grid[posFuture] == true){
                isPossible = false;
                markGrid = true;
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

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Tetris");

    struct tetromino * tetrominos = malloc(100 * sizeof(struct tetromino));
    tetrominos[0] = *initTetromino(100, getPool());
    int numberOfTetrominos = 1;

    drawUI();

    SetTargetFPS(60);
    float fallTimer = 0.0f;
    float fallStep = 0.5f;    // 2 updates/sec pour la chute

    float moveTimer = 0.0f;
    float moveStep = 0.1f; 

    bool mainGrid[180];
    for (int i = 0; i<180;i++){
        mainGrid[i] = false;
    }
    bool dropped = false;
    int horizontalMov = 0;
    //--------------------------------------------------------------------------------------

    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        if (IsKeyDown(KEY_RIGHT)) {
            horizontalMov ++;
        }
        if (IsKeyDown(KEY_LEFT)) {
            horizontalMov --;
        }
        
        moveTimer += GetFrameTime();
        if (moveTimer >= moveStep){
            bool mov = updatePiece(&tetrominos[numberOfTetrominos - 1], false, horizontalMov, false, mainGrid);
            horizontalMov = 0;
            moveTimer = 0.0f;
        }
        
        

        fallTimer += GetFrameTime();
        if (fallTimer >= fallStep) {
            dropped = updatePiece(&tetrominos[numberOfTetrominos - 1], false, horizontalMov, true, mainGrid);
            fallTimer = 0.0f;
        }
        if (dropped){
            tetrominos[numberOfTetrominos] = *initTetromino(100, getPool());
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

    return 0;
}
