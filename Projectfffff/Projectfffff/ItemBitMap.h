#pragma once
#include "Direct2D_Player_Render.h"

//(25.06.04) - ������
//��Ʈ�� �ε� ��� ���� (52 * 52)
//������ ���� ��Ʈ�� ����

using namespace std;

#define ITEM_SIZE 52
//
//static HBITMAP Itembmp = nullptr;
//static HBITMAP Numbmp = nullptr;
//
//static HBITMAP Arrowbmp = nullptr;
//
//extern HBITMAP itemDescBmp;
//extern HDC itemDescDC;
//
//void InitItemDescription() {
//    itemDescBmp = (HBITMAP)LoadImage(NULL, L"��Ʈ��\\�κ�\\������ ����.bmp",
//        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//    itemDescDC = CreateCompatibleDC(NULL);
//    SelectObject(itemDescDC, itemDescBmp);
//}
//
//void CleanupItemDescription() {
//    DeleteDC(itemDescDC);
//    DeleteObject(itemDescBmp);
//}
//
//inline bool InitItemBitmaps()
//{
//    Itembmp = (HBITMAP)LoadImage(
//        NULL,
//        L"��Ʈ��\\������\\1.bmp",
//        IMAGE_BITMAP, 0, 0,
//        LR_LOADFROMFILE | LR_CREATEDIBSECTION
//    );
//
//    if (!Itembmp) {
//        return false;
//    }
//
//    Numbmp = (HBITMAP)LoadImage(
//        NULL,
//        L"��Ʈ��\\������ ����.bmp",
//        IMAGE_BITMAP,
//        0, 0,
//        LR_LOADFROMFILE | LR_CREATEDIBSECTION
//    );
//    if (!Numbmp) {
//        DeleteObject(Itembmp);
//        Itembmp = nullptr;
//        return false;
//    }
//    return true;
//}
//
//inline void CleanupItemBitmaps()
//{
//	if (Itembmp) {
//		DeleteObject(Itembmp);
//		Itembmp = nullptr;
//	}
//    if (Numbmp) {
//        DeleteObject(Numbmp);
//        Numbmp = nullptr;
//    }
//}

inline void GetItemTileCoords(int itemID, int& outSX, int& outSY)
{
	int index = itemID - 1;
	int col = index % 10;
	int row = index / 10;
	outSX = col * ITEM_SIZE;
	outSY = row * ITEM_SIZE;
}

inline void GetNumberTileCoords(int itemNumX, int& outSX, int& outSY)
{
    int idx = itemNumX - 1;
    if (idx < 0) idx = 0;
    if (idx > 9) idx = 9;
    int col = idx % 5;
    int row = idx / 5;
    outSX = col * ITEM_SIZE;
    outSY = row * ITEM_SIZE;
}