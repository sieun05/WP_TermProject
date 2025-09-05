#pragma once

#include <vector>
#include "ItemBitMap.h"

struct WorldItem {
	int x, y;
	int itemID;
	int itemcnt;
};

extern vector<WorldItem> worldItems;

void DrawWorldItems(HDC mdc, HDC itemDC) {
    for (auto& wi : worldItems) {
        int sx, sy;
        GetItemTileCoords(wi.itemID, sx, sy);
        int screenX = wi.x - bx;
        int screenY = wi.y - by;
        TransparentBlt(mdc,screenX, screenY,ITEM_SIZE, ITEM_SIZE, itemDC, sx, sy,ITEM_SIZE, ITEM_SIZE,RGB(0, 0, 255));
    }
}