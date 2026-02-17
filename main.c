#include "main.h"
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

void drawTile(int x, int y, struct Color color){
    int gridX = leftGridCoord;
    int gridY = topGridCoord;
    DrawRectangle(gridX + x * tilesSize, gridY + y * tilesSize, tilesSize, tilesSize, color);
}

struct tetromino * initTetromino(struct rawTetromino ** pool)
{
    struct tetromino * new = malloc(sizeof(struct tetromino));
    new->raw = *pool[rand() % 6];
    new->pos.x = 3;
    new->pos.y = 0;
    return new;
}

bool colorIsEqual(Color a, Color b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

static bool canPlaceWithOffset(
    const struct tetromino * piece,
    int offsetX,
    int offsetY,
    const Color * grid
)
{
    int tileNumber = piece->raw.width * piece->raw.width;
    for (int i = 0; i<tileNumber; i++){
        if (!piece->raw.tiles[i]){
            continue;
        }

        int x = i % piece->raw.width + piece->pos.x + offsetX;
        int y = i / piece->raw.width + piece->pos.y + offsetY;
        if (x < 0 || x >= tilesOnWidth || y < 0 || y >= tilesOnHeight){
            return false;
        }

        int pos = x + tilesOnWidth * y;
        if (!colorIsEqual(grid[pos], RAYWHITE)){
            return false;
        }
    }

    return true;
}


bool updatePiece(struct tetromino * piece, bool rotation, int horinzontalDeplacement, bool descend, struct Color * grid)
{
    (void) rotation;
    if (rotation || strcmp(piece->raw.name, "0") == 0){
        struct rawTetromino oldRaw = piece->raw;
        struct position oldPos = piece->pos;
        const char * oldName = oldRaw.name;

        char rotatedPiece[10];
        rotatedPiece[0] = oldName[0];
        rotatedPiece[1] = '\0';

        const struct wallKick * kickSet[4] = {0};
        if (oldName[1] == '\0') {
            strcat(rotatedPiece, "90");
            kickSet[0] = &wallKick2;
            kickSet[1] = &wallKick3;
            kickSet[2] = &wallKick4;
            kickSet[3] = &wallKick5;
        }
        else if (strcmp(&oldName[1], "90") == 0) {
            strcat(rotatedPiece, "180");
            kickSet[0] = &wallKick290;
            kickSet[1] = &wallKick390;
            kickSet[2] = &wallKick490;
            kickSet[3] = &wallKick590;
        }
        else if (strcmp(&oldName[1], "180") == 0) {
            strcat(rotatedPiece, "270");
            kickSet[0] = &wallKick2180;
            kickSet[1] = &wallKick3180;
            kickSet[2] = &wallKick4180;
            kickSet[3] = &wallKick5180;
        }
        else if (strcmp(&oldName[1], "270") == 0) {
            kickSet[0] = &wallKick2270;
            kickSet[1] = &wallKick3270;
            kickSet[2] = &wallKick4270;
            kickSet[3] = &wallKick5270;
        }
        else {
            printf("Rotation non trouvée!\n");
            return false;
        }

        changeTetrominoRawByName(rotatedPiece, piece);

        if (canPlaceWithOffset(piece, 0, 0, grid)){
            return true;
        }

        for (int i = 0; i<4; i++){
            int offsetX = kickSet[i]->pos.x;
            int offsetY = kickSet[i]->pos.y;
            if (canPlaceWithOffset(piece, offsetX, offsetY, grid)){
                piece->pos.x += offsetX;
                piece->pos.y += offsetY;
                return true;
            }
        }

        piece->raw = oldRaw;
        piece->pos = oldPos;
        return false;
    }

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
                    if (x+1 == 10 || !colorIsEqual(grid[posFuture], RAYWHITE)){
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
                    if (x == 0 || !colorIsEqual(grid[posFuture], RAYWHITE)){
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
            if (posFuture >= 180 || !colorIsEqual(grid[posFuture], RAYWHITE)){
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
                grid[pos] = piece->raw.color;
            }
        }
        //check si des lignes sont completes
        for (int i = 0; i<18; i++){
            bool ligneComplete = true;
            for (int j = 0; j<10; j++){
                if (colorIsEqual(grid[i*10 + j], RAYWHITE)){
                    ligneComplete = false;
                    break;
                }
            }
            if (ligneComplete){
                //supprime la ligne complete
                for (int j = 0; j<10; j++){
                    grid[i*10 + j] = RAYWHITE;
                }
                // fais descendre les autres lignes
                for (int k = i; k>0; k--){
                    for (int j = 0; j<10; j++){
                        if (!colorIsEqual(grid[k * 10 + j], RAYWHITE)){
                            grid[(k+1) * 10 + j] = grid[k * 10 + j];
                            grid[k * 10 + j] = RAYWHITE;                      
                        }
                    }
                }
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

int getRotationMove(float dt)
{
    const float das = 0.12f;   // Delai avant auto-repeat
    const float arr = 0.05f;   // Intervalle de repeat
    static float holdTimer = 0.0f;
    static float repeatTimer = 0.0f;

    if (IsKeyPressed(KEY_UP)) {
        holdTimer = 0.0f;
        repeatTimer = 0.0f;
        return 1;
    }

    if (!IsKeyDown(KEY_UP)) {
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

    struct tetromino * currentTetrominos = malloc(sizeof(struct tetromino));
    currentTetrominos = initTetromino(getPool());
    int numberOfTetrominos = 1;

    drawUI();

    SetTargetFPS(60);

    float fallTimer = 0.0f;
    const float fallStep = 0.5f;    // 2 updates/sec pour la chute

    // Grille des 18 rangées de 10 tuiles
    struct Color mainGrid[180];
    for (int i = 0; i<180;i++){
        mainGrid[i] = RAYWHITE;
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
            updatePiece(currentTetrominos, false, moveCmd, false, mainGrid);
        }

        int moveVerticalCommand = getVerticalMove(dt);
        if (moveVerticalCommand != 0){
            dropped = updatePiece(currentTetrominos, false, 0, true, mainGrid) || dropped;
        }

        int rotateCommand = getRotationMove(dt);
        if (rotateCommand != 0){
            updatePiece(currentTetrominos, true, 0, false, mainGrid);
        }

        fallTimer += dt;
        if (fallTimer >= fallStep) {
            dropped = updatePiece(currentTetrominos, false, 0, true, mainGrid) || dropped;
            fallTimer -= fallStep;
        }
        if (dropped){
            currentTetrominos = initTetromino(getPool());
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

            //Draw the tiles on the grid
            for (int i = 0; i<180; i++){
                drawTile(i%10, i/10, mainGrid[i]);
            }

            // Draw the currently moving piece
            drawTetromino(*currentTetrominos);
            
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    free(currentTetrominos);
    return 0;
}
