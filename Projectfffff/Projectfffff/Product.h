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
                /*if (not challenge[1]) 
                    challenge[1] = 1;*/
                totalItemCount += inventory[row][col].itemcnt;
            }
        }
    }
    return totalItemCount >= requiredCount;
}


bool RemoveItemsFromInventory(int itemID, int count) {

    int totalItemCount = 0;
    int itemrow[5]{};
    int itemcol[5]{};
    int index = 0;

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
                else {
                    totalItemCount += inventory[row][col].itemcnt;
                    itemrow[index] = row;
                    itemcol[index] = col;
                    index++;

                    if (totalItemCount >= count) {
                        for (int i = 0; i < index; i++) {
                            if (inventory[itemrow[i]][itemcol[i]].itemcnt < count) {
                                count -= inventory[itemcol[i]][itemcol[i]].itemcnt;
                                inventory[itemrow[i]][itemcol[i]].itemcnt = 0;
                                inventory[itemrow[i]][itemcol[i]].itemID = 0;
                            }
                            else {
                                inventory[itemrow[i]][itemcol[i]].itemcnt -= count;
                                if (inventory[itemrow[i]][itemcol[i]].itemcnt == 0) {
                                    inventory[itemrow[i]][itemcol[i]].itemID = 0;
                                }
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

#endif