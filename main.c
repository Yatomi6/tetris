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
    new->raw = *pool[seed % 1];
    new->pos.x = 5;
    new->pos.y = 0;
    return new;
}

void updatePiece(struct tetromino * piece, bool rotation, int horinzontalDeplacement, bool descend)
{
    (void) rotation;
    (void) horinzontalDeplacement;
    if (descend) {
        piece->pos.y += 1;
    }
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
    //--------------------------------------------------------------------------------------

    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        fallTimer += GetFrameTime();
        if (fallTimer >= fallStep) {
            updatePiece(&tetrominos[0], false, 0, true);
            fallTimer = 0.0f;
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
