#pragma once

#include "Inventory.h"

#ifndef PRODUCT_H
#define PRODUCT_H

extern Inventory inventory[3][10];
extern int challenge[7];

bool HasRequiredItemsForCraft(int itemID, int requiredCount) {
    int totalItemCount = 0;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 10; ++col) {
            if (inventory[row][col].itemID == itemID) {
                if (not challenge[1]) challenge[1] = 1;
                totalItemCount += inventory[row][col].itemcnt;
            }
        }
    }
    return totalItemCount >= requiredCount;
}


bool RemoveItemsFromInventory(int itemID, int count) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 10; ++col) {
            if (inventory[row][col].itemID == itemID) {
                if (inventory[row][col].itemcnt >= count) {
                    inventory[row][col].itemcnt -= count;
                    if (inventory[row][col].itemcnt == 0) {
                        inventory[row][col].itemID = 0;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

#endif