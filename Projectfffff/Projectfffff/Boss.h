#pragma once
#include "Direct2D_Player_Render.h"

//(25.06.09) - 김정현
//보스를 만들어보자...

// GDI 변수를 Direct2D로 변경
extern ID2D1HwndRenderTarget* g_pRenderTarget;
//extern ID2D1Bitmap* bossBmp;

const int BOSS_SPR_WD = 400;
const int BOSS_SPR_HD = 400;

const int BOSS_ANIM_COLS = 4;
const int BOSS_ANIM_ROWS = 5;

const int BOSS_ANIM_ATTACK_1_IMAGES = 2;
const int BOSS_ANIM_ATTACK_1_REPEATS = 4;
const int BOSS_ANIM_ATTACK_1_FRAMES = BOSS_ANIM_ATTACK_1_IMAGES * BOSS_ANIM_ATTACK_1_REPEATS;
const int BOSS_ANIM_ATTACK_2_FRAMES = 8;
const int BOSS_ANIM_ATTACK_3_FRAMES = 8;

const int EFFECT_ANIM_ATTACK_1_FRAMES = 3;
const int EFFECT_ANIM_ATTACK_2_FRAMES = 3;
const int EFFECT_ANIM_ATTACK_3_FRAMES = 3;

const int EFFECT_SPR_WD = 400;
const int EFFECT_SPR_HD = 400;

const int BOSS_SIZE = 600;

enum BossState {
    BOSS_IDLE,
    BOSS_PREPARE_ATTACK,
    BOSS_ATTACK_1,   // 공격1
    BOSS_ATTACK_2,   // 공격2
    BOSS_ATTACK_3    // 공격3
};

struct Effect {
    bool active;  
    int animFrame;
    int spriteRow;
    DWORD lastAnimUpdate;
    DWORD startTime;
};

extern Effect attackEffect;

struct Boss {
    int hp;
    BossState state;
    int animFrame;
    int maxFrame;
    DWORD lastAnimUpdate;
    DWORD prepareStartTime;
    int x;
    int y;
    bool hitFlag = false;
    DWORD hitTime = 0;
};

void DrawBossMonster(HDC mdc, const Boss& boss, int bx, int by, const Effect& attackEffect) {
    int row = 0;
    int frame = boss.animFrame;

    switch (boss.state) {
    case BOSS_IDLE:
        row = 0;
        frame = boss.animFrame % BOSS_ANIM_COLS;
        break;
    case BOSS_PREPARE_ATTACK:
        row = 1;
        frame = 0;
        break;
    case BOSS_ATTACK_1:
        row = 2;
        frame = (boss.animFrame / BOSS_ANIM_ATTACK_1_REPEATS) % BOSS_ANIM_ATTACK_1_IMAGES;
        break;
    case BOSS_ATTACK_2:
        row = 3;
        frame = boss.animFrame % BOSS_ANIM_ATTACK_2_FRAMES;
        break;
    case BOSS_ATTACK_3:
        row = 4;
        frame = boss.animFrame % BOSS_ANIM_ATTACK_3_FRAMES;
        break;
    }

    int sx = frame * BOSS_SPR_WD;
    int sy = row * BOSS_SPR_HD;
    
    if (!boss.hitFlag) {
        if (bossBmp && g_pRenderTarget) {
            int drawX = boss.x - bx - BOSS_SIZE / 2;
            int drawY = boss.y - by - BOSS_SIZE / 2;

            D2D1_RECT_F destRect = D2D1::RectF(
                static_cast<FLOAT>(drawX),
                static_cast<FLOAT>(drawY),
                static_cast<FLOAT>(drawX + BOSS_SIZE),
                static_cast<FLOAT>(drawY + BOSS_SIZE)
            );

            D2D1_RECT_F srcRect = D2D1::RectF(
                static_cast<FLOAT>(sx),
                static_cast<FLOAT>(sy),
                static_cast<FLOAT>(sx + BOSS_SPR_WD),
                static_cast<FLOAT>(sy + BOSS_SPR_HD)
            );

            g_pRenderTarget->DrawBitmap(
                bossBmp,
                destRect,
                1.0f,
                D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                srcRect
            );
        }

        if (attackEffect.active && bossBmp && g_pRenderTarget) {
            int effectSx = attackEffect.animFrame * EFFECT_SPR_WD;
            int effectSy = attackEffect.spriteRow * EFFECT_SPR_HD;
            int effectX = boss.x - bx - BOSS_SIZE / 2;
            int effectY = boss.y - by - BOSS_SIZE / 2;

            D2D1_RECT_F destRect = D2D1::RectF(
                static_cast<FLOAT>(effectX),
                static_cast<FLOAT>(effectY),
                static_cast<FLOAT>(effectX + BOSS_SIZE),
                static_cast<FLOAT>(effectY + BOSS_SIZE)
            );

            D2D1_RECT_F srcRect = D2D1::RectF(
                static_cast<FLOAT>(effectSx + 2000),
                static_cast<FLOAT>(effectSy),
                static_cast<FLOAT>(effectSx + 2000 + EFFECT_SPR_WD),
                static_cast<FLOAT>(effectSy + EFFECT_SPR_HD)
            );

            g_pRenderTarget->DrawBitmap(
                bossBmp,
                destRect,
                1.0f,
                D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                srcRect
            );
        }
    }
    else {
        if (bossBmp && g_pRenderTarget) {
            int drawX = boss.x - bx - BOSS_SIZE / 2;
            int drawY = boss.y - by - BOSS_SIZE / 2;

            D2D1_RECT_F destRect = D2D1::RectF(
                static_cast<FLOAT>(drawX),
                static_cast<FLOAT>(drawY),
                static_cast<FLOAT>(drawX + BOSS_SIZE),
                static_cast<FLOAT>(drawY + BOSS_SIZE)
            );

            D2D1_RECT_F srcRect = D2D1::RectF(
                static_cast<FLOAT>(sx),
                static_cast<FLOAT>(sy + 2000),
                static_cast<FLOAT>(sx + BOSS_SPR_WD),
                static_cast<FLOAT>(sy + BOSS_SPR_HD + 2000)
            );

            g_pRenderTarget->DrawBitmap(
                bossBmp,
                destRect,
                1.0f,
                D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                srcRect
            );
        }

        if (attackEffect.active && bossBmp && g_pRenderTarget) {
            int effectSx = attackEffect.animFrame * EFFECT_SPR_WD;
            int effectSy = attackEffect.spriteRow * EFFECT_SPR_HD;
            int effectX = boss.x - bx - BOSS_SIZE / 2;
            int effectY = boss.y - by - BOSS_SIZE / 2;

            D2D1_RECT_F destRect = D2D1::RectF(
                static_cast<FLOAT>(effectX),
                static_cast<FLOAT>(effectY),
                static_cast<FLOAT>(effectX + BOSS_SIZE),
                static_cast<FLOAT>(effectY + BOSS_SIZE)
            );

            D2D1_RECT_F srcRect = D2D1::RectF(
                static_cast<FLOAT>(effectSx + 2000),
                static_cast<FLOAT>(effectSy),
                static_cast<FLOAT>(effectSx + 2000 + EFFECT_SPR_WD),
                static_cast<FLOAT>(effectSy + EFFECT_SPR_HD)
            );

            g_pRenderTarget->DrawBitmap(
                bossBmp,
                destRect,
                1.0f,
                D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                srcRect
            );
        }
    }
}

//2506103
void CheckBossAttackHit(Boss& boss, Player& p, int bx, int by, DWORD now) {
    if (now - boss.hitTime > 500) {
        boss.hitFlag = false;
    }
    if (!attackEffect.active) return;

    int px = p.x + bx;
    int py = p.y + by;
    int bossX = boss.x - bx;
    int bossY = boss.y - by;
    RECT pRect = { p.x, p.y, p.x + 62, p.y + 62 };

    //1번패턴 - 아래로 공격(지속데미지)
    if (boss.state == BOSS_ATTACK_1) {
        RECT attackRect = {
            bossX - 200,
            bossY,
            bossX + 200,
            bossY + 270
        };

        if (PtInRect(&attackRect, POINT{ pRect.left, pRect.top }) or
            PtInRect(&attackRect, POINT{ pRect.left, pRect.right }) or
            PtInRect(&attackRect, POINT{ pRect.right, pRect.top }) or
            PtInRect(&attackRect, POINT{ pRect.right, pRect.bottom })) {

            if (now - p.lastHitTime >= 300) { // 0.3초마다 데미지
                p.hp -= 5;
                p.lastHitTime = now;
                p.isHurt = true;
            }
        }
    }
    // 2번 패턴 - 왼→오 아래 휘두름 (한 번만 데미지)
    else if (boss.state == BOSS_ATTACK_2) {
        if (boss.animFrame == 3 && !p.isHurt) { // 3프레임에 판정
            RECT attackRect = {
                bossX - 200,
                bossY,
                bossX + 100,
                bossY + 300
            };

            if (PtInRect(&attackRect, POINT{ pRect.left, pRect.top }) or
                PtInRect(&attackRect, POINT{ pRect.left, pRect.right }) or
                PtInRect(&attackRect, POINT{ pRect.right, pRect.top }) or
                PtInRect(&attackRect, POINT{ pRect.right, pRect.bottom })) {

                p.isHurt = true;
                p.hp -= 10;
                p.lastHitTime = now;
            }
        }
    }

    // 3번 패턴 - 오→왼 아래 휘두름 (한 번만 데미지)
    else if (boss.state == BOSS_ATTACK_3) {
        if (boss.animFrame == 3 && !p.isHurt) {
            RECT attackRect = {
                bossX - 100,
                bossY,
                bossX + 200,
                bossY + 300
            };

            if (PtInRect(&attackRect, POINT{ pRect.left, pRect.top }) or
                PtInRect(&attackRect, POINT{ pRect.left, pRect.right }) or
                PtInRect(&attackRect, POINT{ pRect.right, pRect.top }) or
                PtInRect(&attackRect, POINT{ pRect.right, pRect.bottom })) {

                p.isHurt = true;
                p.hp -= 10;
                p.lastHitTime = now;
            }
        }
    }

    // 애니메이션이 끝나면 다음 프레임에 다시 피격 가능
    if (boss.state == BOSS_IDLE) {
        p.isHurt = false;
    }
}

void ChooseRandomAttack(Boss& boss) {
    int randAttack = ranattack(dre);

    switch (randAttack) {
    case 0:
        boss.state = BOSS_ATTACK_1;
        boss.maxFrame = BOSS_ANIM_ATTACK_1_FRAMES * 4;
        attackEffect.active = true;
        attackEffect.animFrame = 0;
        attackEffect.spriteRow = 0;
        attackEffect.startTime = GetTickCount64();
        break;
    case 1:
        boss.state = BOSS_ATTACK_2;
        boss.maxFrame = BOSS_ANIM_ATTACK_2_FRAMES;
        attackEffect.active = true;
        attackEffect.animFrame = 0;
        attackEffect.spriteRow = 1;
        attackEffect.startTime = GetTickCount64();
        break;
    case 2: 
        boss.state = BOSS_ATTACK_3;
        boss.maxFrame = BOSS_ANIM_ATTACK_3_FRAMES;
        attackEffect.active = true;
        attackEffect.animFrame = 0;
        attackEffect.spriteRow = 2;
        attackEffect.startTime = GetTickCount64();
        break;
    }

    boss.animFrame = 0;
}

void UpdateBossAnimation(Boss& boss, DWORD currentTime) {
    DWORD animationSpeed = 150;
    if (boss.state == BOSS_ATTACK_1) {
        animationSpeed = 35;
    }
    if (currentTime - boss.lastAnimUpdate >= animationSpeed) {
        boss.animFrame++;
        if (boss.state == BOSS_ATTACK_1 && boss.animFrame >= BOSS_ANIM_ATTACK_1_FRAMES * 4) {
            boss.state = BOSS_IDLE;
            boss.animFrame = 0;
            attackEffect.active = false;
        }
        else if ((boss.state == BOSS_ATTACK_2 || boss.state == BOSS_ATTACK_3) && boss.animFrame >= boss.maxFrame) {
            boss.state = BOSS_IDLE;
            boss.animFrame = 0;
            attackEffect.active = false;
        }
        boss.lastAnimUpdate = currentTime;
    }

    if (attackEffect.active) {
        DWORD now = GetTickCount64();
        DWORD effectAnimSpeed = (boss.state == BOSS_ATTACK_1) ? 35 : 50; 

        if (boss.state == BOSS_ATTACK_1) {
            
            if (now - attackEffect.lastAnimUpdate >= effectAnimSpeed) {
                attackEffect.animFrame = (attackEffect.animFrame + 1) % EFFECT_ANIM_ATTACK_1_FRAMES; 
                attackEffect.lastAnimUpdate = now;
            }
        }
        else if (boss.state == BOSS_ATTACK_2 || boss.state == BOSS_ATTACK_3) {
           
           /* if (now - attackEffect.startTime >= 800) {*/
                if (boss.animFrame == 2) {
                    attackEffect.animFrame = 0;
                }
                else if (boss.animFrame == 3) {
                    attackEffect.animFrame = 1;
                }
                else if (boss.animFrame == 4) {
                    attackEffect.animFrame = 2;
                }
                else if (boss.animFrame > 4) {
                    attackEffect.active = false;
                }
                attackEffect.lastAnimUpdate = now;
            //}
        }
    }
}