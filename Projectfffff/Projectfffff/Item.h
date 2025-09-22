#pragma once

#include <vector>
#include "ItemBitMap.h"


struct WorldItem {
	int x, y;
	int itemID;
	int itemcnt;
};

extern vector<WorldItem> worldItems;

//void DrawWorldItems(HDC mdc, HDC itemDC) {
//    for (auto& wi : worldItems) {
//        int sx, sy;
//        GetItemTileCoords(wi.itemID, sx, sy);
//        int screenX = wi.x - bx;
//        int screenY = wi.y - by;
//        TransparentBlt(mdc,screenX, screenY,ITEM_SIZE, ITEM_SIZE, itemDC, sx, sy,ITEM_SIZE, ITEM_SIZE,RGB(0, 0, 255));
//    }
//}

void DrawWorldItems() {
    for (auto& wi : worldItems) {
        int sx, sy;
        GetItemTileCoords(wi.itemID, sx, sy);
        int screenX = wi.x - bx;
        int screenY = wi.y - by;

        D2D1_RECT_F destRect = D2D1::RectF(
            static_cast<FLOAT>(screenX),
            static_cast<FLOAT>(screenY),
            static_cast<FLOAT>(screenX + ITEM_SIZE),
            static_cast<FLOAT>(screenY + ITEM_SIZE)
        );

        D2D1_RECT_F srcRect = D2D1::RectF(
            static_cast<FLOAT>(sx),
            static_cast<FLOAT>(sy),
            static_cast<FLOAT>(sx + ITEM_SIZE),
            static_cast<FLOAT>(sy + ITEM_SIZE)
        );

        g_pRenderTarget->DrawBitmap(
            Itembmp,  // 알파 채널 포함된 아이템 시트 비트맵
            destRect,
            1.0f,
            D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
            srcRect
        );
    }
}