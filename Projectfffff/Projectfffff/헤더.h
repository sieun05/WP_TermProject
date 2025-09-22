#pragma once
#include <windows.h>		//--- 윈도우 헤더 파일
#include <tchar.h>
#include <stdio.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <random>
#include <wingdi.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>

#include "Collision.h"
#include "Cell.h"
#include "Player.h"
#include "Inventory.h"
#include "BitMap.h"
#include "ItemBitMap.h"
#include "Item.h"
#include "Direction.h"
#include "Monster.h"
#include "Attack.h"
#include "Path.h"
#include "Action.h"
#include "Boss.h"
#include "Product.h"
#include "Cook.h"
#include "Direct2D_Player_Render.h"

#pragma comment(lib, "Msimg32.lib") // AlphaBlend 사용 시 필요

////(25.06.08) - 오시은
//알파블렌딩

//extern HBITMAP g_LightMask;
//extern void* g_LightBits;
//extern int g_LightWidth;
//extern int g_LightHeight;
//
//
//HBITMAP CreateLightingMask(HDC hdc, int width, int height, int radius)
//{
//    g_LightWidth = width;
//    g_LightHeight = height;
//
//    BITMAPINFO bmi = {};
//    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//    bmi.bmiHeader.biWidth = width;
//    bmi.bmiHeader.biHeight = -height; // top-down
//    bmi.bmiHeader.biPlanes = 1;
//    bmi.bmiHeader.biBitCount = 32;
//    bmi.bmiHeader.biCompression = BI_RGB;
//
//    g_LightBits = nullptr;
//    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &g_LightBits, NULL, 0);
//
//    if (!hBitmap) return NULL;
//
//    int centerX = width / 2;
//    int centerY = height / 2;
//
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            int dx = x - centerX;
//            int dy = y - centerY;
//            float dist = sqrtf(dx * dx + dy * dy);
//
//            float alpha = 255.0f;
//
//            //if (dist < radius)
//            //    alpha = 255.0f * (dist / radius);  // 중심 가까울수록 투명하게
//
//            float maxAlpha = 180.0f;  // 255보다 낮게 설정
//            if (dist < radius)
//                alpha = maxAlpha * (dist / radius);
//            else
//                alpha = maxAlpha;
//
//            int index = y * width + x;
//            BYTE* px = (BYTE*)g_LightBits + index * 4;
//            px[0] = 0; // B
//            px[1] = 0; // G
//            px[2] = 0; // R
//            px[3] = (BYTE)min(255, max(0, (int)alpha)); // A
//        }
//    }
//
//    return hBitmap;
//}