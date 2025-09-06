#pragma once

#include "Inventory.h"

bool CanCombine(Inventory item1, Inventory item2) {
    if ((item1.itemID == 73 && item2.itemID == 73) ||
        (item1.itemID == 71 && item2.itemID == 72) ||
        (item1.itemID == 72 && item2.itemID == 71) ||
        (item1.itemID == 73 && item2.itemID == 72) ||
        (item1.itemID == 72 && item2.itemID == 73) ||
        (item1.itemID == 72 && item2.itemID == 72) ||
        (item1.itemID == 71 && item2.itemID == 71) ||
        (item1.itemID == 71 && item2.itemID == 74) ||
        (item1.itemID == 74 && item2.itemID == 71) ||
        (item1.itemID == 71 && item2.itemID == 73) ||
        (item1.itemID == 73 && item2.itemID == 71) ||
        (item1.itemID == 74 && item2.itemID == 74) ||
        (item1.itemID == 74 && item2.itemID == 73) ||
        (item1.itemID == 73 && item2.itemID == 74) ||
        (item1.itemID == 74 && item2.itemID == 72) ||
        (item1.itemID == 72 && item2.itemID == 74)) {
        return true;
    }
    return false;
}

Inventory CombineItems(Inventory item1, Inventory item2) {
    Inventory result;
    if (item1.itemID == 73 && item2.itemID == 73) {
        result.itemID = 83;
    }
    else if ((item1.itemID == 71 && item2.itemID == 72) || (item1.itemID == 73 && item2.itemID == 72) or
        (item1.itemID == 72 && item2.itemID == 71) || (item1.itemID == 72 && item2.itemID == 73)) {
        result.itemID = 83;
    }
    else if (item1.itemID == 72 && item2.itemID == 72) {
        result.itemID = 82;
    }
    else if (item1.itemID == 71 && item2.itemID == 71) {
        result.itemID = 81;
    }
    else if ((item1.itemID == 71 && item2.itemID == 74) or 
        (item1.itemID == 74 && item2.itemID == 71)) {
        result.itemID = 81;
    }
    else if ((item1.itemID == 71 && item2.itemID == 73) or 
        (item1.itemID == 73 && item2.itemID == 71)) {
        result.itemID = 81;
    }
    else if (item1.itemID == 74 && item2.itemID == 74) {
        result.itemID = 84;
    }
    else if ((item1.itemID == 74 && item2.itemID == 73) or 
        (item1.itemID == 73 && item2.itemID == 74)) {
        result.itemID = 84;
    }
    else if ((item1.itemID == 74 && item2.itemID == 72) or 
        (item1.itemID == 72 && item2.itemID == 74)) {
        result.itemID = 84;
    }

    result.itemcnt = 1;
    return result;
}

void PlaceItemOnCookingSlot(Inventory& slot, Inventory item) {
    slot = item;
}

void CombineAndPlaceOnCookingSlot(Inventory& slot1, Inventory& slot2, Inventory& slot3) {
    if (CanCombine(slot1, slot2)) {
        Inventory result = CombineItems(slot1, slot2);
        slot3 = result;
        slot1.itemID = 0;
        slot1.itemcnt = 0;
        slot2.itemID = 0;
        slot2.itemcnt = 0;
    }
}

