#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

void drawTetromino(struct tetromino piece)
{
    int width = sqrt(sizeof(piece.raw.tiles)/4);
    int nbTiles = width * width;
    for (int i = 0; i<nbTiles; i++){
        if (piece.raw.tiles[i]){
            int x = i % width;
            int y = i / width;
            int gridX = leftGridCoord + tilesSize * tilesOnWidth/2 - tilesSize * (width/2);
            int gridY = topGridCoord;
            DrawRectangle(gridX + x * tilesSize, gridY + y * tilesSize, tilesSize, tilesSize, piece.raw.color);
        }
    }
    
}

struct tetromino * initTetromino(int seed, struct rawTetromino * pool)
{
    struct tetromino * new = malloc(sizeof(struct tetromino));
    new->raw = pool[seed%1];
    return new;
}

void updatePiece(struct tetromino piece, bool rotation, int horinzontalDeplacement, bool descend)
{
    (void) rotation;
    (void) horinzontalDeplacement;
    if (descend) {
        piece.pos.y += 1;
    }
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Tetris");

    struct tetromino * tetrominos = malloc(100 * sizeof(struct tetromino));
    tetrominos[0] = *initTetromino(100, getPool());
    int numberOfTetrominos = 1;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

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