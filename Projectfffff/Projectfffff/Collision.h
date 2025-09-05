#pragma once
#include "Cell.h"
#include "Player.h"

//(25.05.31) - 김정현
//맵 장애물 충돌처리 구현 /  벽에 딱 붙도록 처리하지는 않음.
extern Cell game_map[MAP_HEIGHT][MAP_WIDTH];
extern int bx;
extern int by;

bool MoveCollisionInView(int newX, int newY)
{

    int start_col = bx / CELL_SIZE;
    int start_row = by / CELL_SIZE;
    int offset_x = bx % CELL_SIZE;
    int offset_y = by % CELL_SIZE;

    RECT playerRect;
    playerRect.left = newX - 10;
    playerRect.top = newY + 10;
    playerRect.right = newX + 10;
    playerRect.bottom = newY + 30;

    for (int row = 0; row <= SCREEN_HEIGHT; ++row) {
        int map_row = start_row + row;

        if (map_row < 0 || map_row >= MAP_HEIGHT)
            continue;

        for (int col = 0; col <= SCREEN_WIDTH; ++col) {
            int map_col = bx / CELL_SIZE + col;
            int type = game_map[map_row][map_col].type;
            if (map_col < 0 || map_col >= MAP_WIDTH) 
                continue;
            if (type != 1 && type != 2 && type != 3 && type != 7 && type != 8 && type != 9 && type != 10 && type != 11)
                continue;
            int blockScreenX = map_col * CELL_SIZE - bx;
            int blockScreenY = map_row * CELL_SIZE - by;

            RECT blockRect;
            blockRect.left = blockScreenX;
            blockRect.top = blockScreenY;
            blockRect.right = blockScreenX + CELL_SIZE;
            blockRect.bottom = blockScreenY + CELL_SIZE;

            if (!(playerRect.left > blockRect.right ||
                playerRect.right < blockRect.left ||
                playerRect.top > blockRect.bottom ||
                playerRect.bottom < blockRect.top))
            {
                return true;
            }
        }
    }
    return false;
}
