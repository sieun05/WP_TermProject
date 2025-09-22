#pragma once

//extern HBITMAP InvenExpanded;
//extern HBITMAP InvenNormal; 
//extern HBITMAP InvenExpandednum;
//extern HBITMAP InvenNormalnum;
//extern HBITMAP SelecInven_Ex;
//extern HBITMAP SelecInven_Nor;
//
//extern HDC hdcExpanded;
//extern HDC hdcNormal;
//extern HDC hdcExpandednum;
//extern HDC hdcNormalnum;
//extern HDC hdcSelecInven_Ex;
//extern HDC hdcSelecInven_Nor;
//
//extern int bmpExp_W;
//extern int bmpExp_H;
//extern int bmpNor_W;
//extern int bmpNor_H;
//
//extern int bmpselec_W;
//extern int bmpselec_H;

//
//inline bool InitInvBitmaps(HINSTANCE hInst){
//    InvenExpanded = (HBITMAP)LoadImage(NULL,L"비트맵\\인벤\\전체 인벤창.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
//    InvenNormal = (HBITMAP)LoadImage(NULL, L"비트맵\\인벤\\10칸 인벤토리.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
//    InvenExpandednum = (HBITMAP)LoadImage(NULL, L"비트맵\\인벤\\인벤토리 숫자.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
//    InvenNormalnum = (HBITMAP)LoadImage(NULL, L"비트맵\\인벤\\10칸 인벤토리 숫자.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
//    SelecInven_Ex = (HBITMAP)LoadImage(NULL, L"비트맵\\인벤\\인벤 선택 테두리.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
//    SelecInven_Nor = (HBITMAP)LoadImage(NULL, L"비트맵\\인벤\\인벤 선택 테두리.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
//    
//    if (!InvenExpanded || !InvenNormal) {
//        return false;
//    }
//
//    BITMAP bmp;
//    GetObject(InvenExpanded, sizeof(bmp), &bmp);
//    bmpExp_W = bmp.bmWidth;
//    bmpExp_H = bmp.bmHeight;
//    GetObject(InvenNormal, sizeof(bmp), &bmp);
//    bmpNor_W = bmp.bmWidth;
//    bmpNor_H = bmp.bmHeight;
//    GetObject(SelecInven_Ex, sizeof(bmp), &bmp);
//    bmpselec_W = bmp.bmWidth;
//    bmpselec_H = bmp.bmHeight;
//
//    HDC hdcScreen = GetDC(NULL);
//    hdcExpanded = CreateCompatibleDC(hdcScreen);
//    hdcNormal = CreateCompatibleDC(hdcScreen);
//    hdcExpandednum = CreateCompatibleDC(hdcScreen);
//    hdcNormalnum = CreateCompatibleDC(hdcScreen);
//    hdcSelecInven_Ex = CreateCompatibleDC(hdcScreen);
//    hdcSelecInven_Nor = CreateCompatibleDC(hdcScreen);
//    ReleaseDC(NULL, hdcScreen);
//
//    SelectObject(hdcExpanded, InvenExpanded);
//    SelectObject(hdcNormal, InvenNormal);
//    SelectObject(hdcExpandednum, InvenExpandednum);
//    SelectObject(hdcNormalnum, InvenNormalnum);
//    SelectObject(hdcSelecInven_Ex, SelecInven_Ex);
//    SelectObject(hdcSelecInven_Nor, SelecInven_Nor);
//
//    return true;
//}
//
//inline void CleanupInvBitmaps() {
//    if (hdcExpanded) {
//        DeleteDC(hdcExpanded);
//        hdcExpanded = nullptr;
//    }
//    if (hdcNormal) {
//        DeleteDC(hdcNormal);
//        hdcNormal = nullptr;
//    }
//    if (InvenExpanded) {
//        DeleteObject(InvenExpanded);
//        InvenExpanded = nullptr;
//    }
//    if (InvenNormal) {
//        DeleteObject(InvenNormal);
//        InvenNormal = nullptr;
//    }
//    if (hdcExpandednum) {
//        DeleteDC(hdcExpandednum);
//        hdcExpandednum = nullptr;
//    }
//    if (hdcNormalnum) {
//        DeleteDC(hdcNormalnum);
//        hdcNormalnum = nullptr;
//    }
//    if (InvenExpandednum) {
//        DeleteObject(InvenExpandednum);
//        InvenExpandednum = nullptr;
//    }
//    if (InvenNormalnum) {
//        DeleteObject(InvenNormalnum);
//        InvenNormalnum = nullptr;
//    }
//}
