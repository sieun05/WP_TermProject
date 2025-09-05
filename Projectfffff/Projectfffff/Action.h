#pragma once
#include "Direction.h"
#include "ItemBitMap.h"
#include "Player.h"
#include "Cell.h"
#include "Inventory.h"

extern Cell game_map[MAP_HEIGHT][MAP_WIDTH];
extern int challenge[7];
//extern Inventory playeritem[4]; // 장비 슬롯

inline void Mining(Player p, int bx, int by) {

    int curMapX = (bx + p.x) / CELL_SIZE;
    int curMapY = (by + p.y + 25) / CELL_SIZE;

    int targetX = curMapX;
    int targetY = curMapY;

    switch (p.dir) {
    case DIR_UP:        targetY -= 1; break;
    case DIR_DOWN:      targetY += 1; break;
    case DIR_LEFT:      targetX -= 1; break;
    case DIR_RIGHT:     targetX += 1; break;
    case DIR_UP_LEFT:   targetX -= 1; targetY -= 1; break;
    case DIR_UP_RIGHT:  targetX += 1; targetY -= 1; break;
    case DIR_DOWN_LEFT: targetX -= 1; targetY += 1; break;
    case DIR_DOWN_RIGHT:targetX += 1; targetY += 1; break;
    }

    if (targetX < 0 || targetX >= MAP_WIDTH || targetY < 0 || targetY >= MAP_HEIGHT)
        return;

    //2506102
    if (game_map[targetY][targetX].type >= 1 and game_map[targetY][targetX].type <= 3) {

        //(25.06.09) - 김정현
        //돌 아이템 드랍
        //(25.06.10) - 오시은
        //철, 금 아이템 드랍
        int dropX = targetX * CELL_SIZE;
        int dropY = targetY * CELL_SIZE;
        switch (game_map[targetY][targetX].type) {
        case 1:
            worldItems.push_back({ dropX, dropY, 52, 1 });
            //2506103
            if (not challenge[0]) challenge[0] = 1;
            break;
        case 2:
            worldItems.push_back({ dropX, dropY, 61, 1 });
            break;
        case 3:
            worldItems.push_back({ dropX, dropY, 62, 1 });
            break;
        }

        game_map[targetY][targetX].type = 0;
    }
}

inline void Mining2(Player p, int bx, int by) {

    int curMapX = (bx + p.x) / CELL_SIZE;
    int curMapY = (by + p.y + 25) / CELL_SIZE;

    int targetX = curMapX;
    int targetY = curMapY;

    switch (p.dir) {
    case DIR_UP:        targetY -= 1; break;
    case DIR_DOWN:      targetY += 1; break;
    case DIR_LEFT:      targetX -= 1; break;
    case DIR_RIGHT:     targetX += 1; break;
    case DIR_UP_LEFT:   targetX -= 1; targetY -= 1; break;
    case DIR_UP_RIGHT:  targetX += 1; targetY -= 1; break;
    case DIR_DOWN_LEFT: targetX -= 1; targetY += 1; break;
    case DIR_DOWN_RIGHT:targetX += 1; targetY += 1; break;
    }

    if (targetX < 0 || targetX >= MAP_WIDTH || targetY < 0 || targetY >= MAP_HEIGHT)
        return;

    if (game_map[targetY][targetX].type == 0 or
        game_map[targetY][targetX].type == 5 or
        game_map[targetY][targetX].type == 6) {

        game_map[targetY][targetX].type = 7;
        // TODO: 이펙트나 사운드 추가 가능
    }
}

inline void Mining3(Player p, int bx, int by) {
    int curMapX = (bx + p.x) / CELL_SIZE;
    int curMapY = (by + p.y + 25) / CELL_SIZE;

    int targetX = curMapX;
    int targetY = curMapY;

    switch (p.dir) {
    case DIR_UP:        targetY -= 1; break;
    case DIR_DOWN:      targetY += 1; break;
    case DIR_LEFT:      targetX -= 1; break;
    case DIR_RIGHT:     targetX += 1; break;
    case DIR_UP_LEFT:   targetX -= 1; targetY -= 1; break;
    case DIR_UP_RIGHT:  targetX += 1; targetY -= 1; break;
    case DIR_DOWN_LEFT: targetX -= 1; targetY += 1; break;
    case DIR_DOWN_RIGHT:targetX += 1; targetY += 1; break;
    }

    if (targetX < 0 || targetX >= MAP_WIDTH || targetY < 0 || targetY >= MAP_HEIGHT)
        return;

    if (game_map[targetY][targetX].type == 8) {
        game_map[targetY][targetX].type = 0;

        int dropX = targetX * CELL_SIZE;
        int dropY = targetY * CELL_SIZE;
        worldItems.push_back({ dropX, dropY, 51, 1 });

        for (int i{}; i < 3; i++) {
            int drop = drop_ran(dre);
            if (drop > 0 and drop < 2) {
                worldItems.push_back({ dropX, dropY, 72 + i, 1 });
                break;
            }
        }
    }
    else if (game_map[targetY][targetX].type == 9) {
        game_map[targetY][targetX].type = 0;

        int dropX = targetX * CELL_SIZE;
        int dropY = targetY * CELL_SIZE;
        worldItems.push_back({ dropX, dropY, 91, 1 });
    }
    else if (game_map[targetY][targetX].type == 10) {
        game_map[targetY][targetX].type = 0;

        int dropX = targetX * CELL_SIZE;
        int dropY = targetY * CELL_SIZE;
        worldItems.push_back({ dropX, dropY, 92, 1 });
    }
};

inline void Eat(Player& p, Inventory& inventory) {
    int heldItemID = inventory.itemID;

    inventory.itemcnt--;
    //2506103
    if (not challenge[4]) challenge[4] = 1;
    if (inventory.itemcnt == 0) inventory.itemID = 0;
    switch (heldItemID) {
    case 81:
        p.hunger += 20;
        break;
    case 82:
        p.hunger += 30;
        break;
    case 83:
        p.hunger += 40;
        break;
    case 84:
        p.hunger += 30;
        break;
    }

    if (p.hunger >= 100) p.hunger = 100;
}

inline void CraftAndInteraction(Player p, int bx, int by, Inventory& inventory, bool& craftUI, bool& cookUI, bool& boss_flag) {
    int curMapX = (bx + p.x) / CELL_SIZE;
    int curMapY = (by + p.y + 25) / CELL_SIZE;

    int targetX = curMapX;
    int targetY = curMapY;

    switch (p.dir) {
    case DIR_UP:        targetY -= 1; break;
    case DIR_DOWN:      targetY += 1; break;
    case DIR_LEFT:      targetX -= 1; break;
    case DIR_RIGHT:     targetX += 1; break;
    case DIR_UP_LEFT:   targetX -= 1; targetY -= 1; break;
    case DIR_UP_RIGHT:  targetX += 1; targetY -= 1; break;
    case DIR_DOWN_LEFT: targetX -= 1; targetY += 1; break;
    case DIR_DOWN_RIGHT:targetX += 1; targetY += 1; break;
    }

    if (targetX < 0 || targetX >= MAP_WIDTH || targetY < 0 || targetY >= MAP_HEIGHT)
        return;

    int heldItemID = inventory.itemID;
    if (game_map[targetY][targetX].type == 0) {

        switch (heldItemID) {
        case 91:
            game_map[targetY][targetX].type = 9;
            inventory.itemcnt--;
            break;
        case 92:
            game_map[targetY][targetX].type = 10;
            inventory.itemcnt--;
            break;
        case 51:
            //2506102
            game_map[targetY][targetX].type = 8;
            inventory.itemcnt--;
            break;
        case 52:
            game_map[targetY][targetX].type = 1;
            inventory.itemcnt--;
            break;
        }
    }
    else if (game_map[targetY][targetX].type == 7) {

        switch (heldItemID) {
            //2506102 case 51 제거
        case 52:
            game_map[targetY][targetX].type = 0;
            inventory.itemcnt--;
            break;
        }
    }
    else if (game_map[targetY][targetX].type == 9) {
        craftUI = true;
    }
    else if (game_map[targetY][targetX].type == 10) {
        cookUI = true;
    }
    else if (game_map[targetY][targetX].type == 11) {
        if (heldItemID == 14) {
            //보스소환
            boss_flag = true;
            inventory.itemcnt--;
            challenge[5] = 1;
        }
    }

    if (inventory.itemcnt == 0) inventory.itemID = 0;
}