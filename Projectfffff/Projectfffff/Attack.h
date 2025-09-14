#pragma once
#include "Direction.h"
#include "Monster.h"
#include "ItemBitMap.h"
#include "Boss.h"

extern bool boss_flag;
extern bool game_end_flag;
extern int challenge[7];

inline void AttackDagger(Player& p, Boss& boss, int bx, int by) {
    const int R = 80;
    const int DAMAGE = 10;
    const int KNOCKBACK = 40;
    const int STEP_SIZE = 10;

    if (boss.hp <= 0) return;

    int dx = (boss.x - bx) - p.x;
    int dy = (boss.y - by) - p.y;
    int dist = dx * dx + dy * dy;
    if (dist > R * R) return;

    bool hit = false;

    switch (p.dir) {
    case DIR_DOWN:        if (dy > 0) hit = true; break;
    case DIR_DOWN_RIGHT:  if (dx > 0 && dy > 0) hit = true; break;
    case DIR_RIGHT:       if (dx > 0) hit = true; break;
    case DIR_UP_RIGHT:    if (dx > 0 && dy < 0) hit = true; break;
    case DIR_UP:          if (dy < 0) hit = true; break;
    case DIR_UP_LEFT:     if (dx < 0 && dy < 0) hit = true; break;
    case DIR_LEFT:        if (dx < 0) hit = true; break;
    case DIR_DOWN_LEFT:   if (dx < 0 && dy > 0) hit = true; break;
    }

    if (!hit) return;

    boss.hp -= DAMAGE;
    if (boss.hp < 0) boss.hp = 0;

    boss.hitFlag = true;
    boss.hitTime = GetTickCount64();
}

//(25.06.09) - 김정현
//단검, 장검으로 쳤을 때 벽 안으로 밀리지 않게 수정함

//단검
inline void AttackDagger(int pX, int pY, Direction dir, Monster* monsterList, int monsterCount) {
    const int R = 80;
    const int DAMAGE = 10;
    const int KNOCKBACK = 40;
    const int STEP_SIZE = 10;

    for (int i = 0; i < monsterCount; ++i) {
        Monster& m = monsterList[i];
        if (m.hp <= 0) continue;

        int dx = m.x - pX;
        int dy = m.y - pY;
        int dist = dx * dx + dy * dy;
        if (dist > R * R)
            continue;

        bool hit = false;

        switch (dir) {
        case DIR_DOWN: {
            if (dy > 0) {
                hit = true;
            }
            break;
        }
        case DIR_DOWN_RIGHT: {
            if (dx > 0 && dy > 0)
                hit = true;
            break;
        }
        case DIR_RIGHT: {
            if (dx > 0)
                hit = true;
            break;
        }
        case DIR_UP_RIGHT: {
            if (dx > 0 && dy < 0)
                hit = true;
            break;
        }
        case DIR_UP: {
            if (dy < 0)
                hit = true;
            break;
        }
        case DIR_UP_LEFT: {
            if (dx < 0 && dy < 0) hit = true;
            break;
        }
        case DIR_LEFT: {
            if (dx < 0) hit = true;
            break;
        }
        case DIR_DOWN_LEFT: {
            if (dx < 0 && dy > 0) hit = true;
            break;
        }
        }
        if (!hit) continue;

        m.hp -= DAMAGE;
        if (m.hp < 0) m.hp = 0;
        m.hitFlag = true;
        m.hitTime = GetTickCount64();

        int dirX = 0, dirY = 0;

        switch (dir) {
        case DIR_DOWN:        dirY = 1; break;
        case DIR_DOWN_RIGHT:  dirX = 1; dirY = 1; break;
        case DIR_RIGHT:       dirX = 1; break;
        case DIR_UP_RIGHT:    dirX = 1; dirY = -1; break;
        case DIR_UP:          dirY = -1; break;
        case DIR_UP_LEFT:     dirX = -1; dirY = -1; break;
        case DIR_LEFT:        dirX = -1; break;
        case DIR_DOWN_LEFT:   dirX = -1; dirY = 1; break;
        }

        for (int step = 0; step < KNOCKBACK; step += STEP_SIZE) {
            m.x += dirX * STEP_SIZE;
            m.y += dirY * STEP_SIZE;
            if (m.checkCollisionWithWalls()) {
                m.x -= dirX * STEP_SIZE;
                m.y -= dirY * STEP_SIZE;
                break;
            }
        }
    }
}

//장검
inline void AttackLongsword(int pX, int pY, Direction dir, Monster* monsterList, int monsterCount) {
    const int R = 120;
    const int DAMAGE = 10;
    const int KNOCKBACK = 40;
    const int STEP_SIZE = 10;

    for (int i = 0; i < monsterCount; ++i) {
        Monster& m = monsterList[i];
        if (m.hp <= 0) continue;

        int dx = m.x - pX;
        int dy = m.y - pY;
        int dist = dx * dx + dy * dy;
        if (dist > R * R)
            continue;

        bool hit = false;

        switch (dir) {
        case DIR_DOWN: {
            if (dy > 0)
                hit = true;
            break;
        }
        case DIR_DOWN_RIGHT: {
            if (dx > 0 && dy > 0)
                hit = true;
            break;
        }
        case DIR_RIGHT: {
            if (dx > 0)
                hit = true;
            break;
        }
        case DIR_UP_RIGHT: {
            if (dx > 0 && dy < 0)
                hit = true;
            break;
        }
        case DIR_UP: {
            if (dy < 0)
                hit = true;
            break;
        }
        case DIR_UP_LEFT: {
            if (dx < 0 && dy < 0) hit = true;
            break;
        }
        case DIR_LEFT: {
            if (dx < 0) hit = true;
            break;
        }
        case DIR_DOWN_LEFT: {
            if (dx < 0 && dy > 0) hit = true;
            break;
        }
        }
        if (!hit) continue;

        m.hp -= DAMAGE;
        if (m.hp < 0) m.hp = 0;
        m.hitFlag = true;
        m.hitTime = GetTickCount64();

        int dirX = 0, dirY = 0;

        switch (dir) {
        case DIR_DOWN:        dirY = 1; break;
        case DIR_DOWN_RIGHT:  dirX = 1; dirY = 1; break;
        case DIR_RIGHT:       dirX = 1; break;
        case DIR_UP_RIGHT:    dirX = 1; dirY = -1; break;
        case DIR_UP:          dirY = -1; break;
        case DIR_UP_LEFT:     dirX = -1; dirY = -1; break;
        case DIR_LEFT:        dirX = -1; break;
        case DIR_DOWN_LEFT:   dirX = -1; dirY = 1; break;
        }

        for (int step = 0; step < KNOCKBACK; step += STEP_SIZE) {
            int prevX = m.x;
            int prevY = m.y;
            m.x += dirX * STEP_SIZE;
            m.y += dirY * STEP_SIZE;

            if (m.checkCollisionWithWalls()) {
                m.x = prevX;
                m.y = prevY;
                break;
            }
        }
    }
}
//화살
struct Arrow {
    Arrow() = default;
    Arrow(float x, float y)
        :x{ x }, y{ y }, dist(0), active{ true } {
    }
    float x, y;
    Direction dir;
    float dist;
    bool active;
};

extern vector<Arrow> arrow;
extern HBITMAP arrowBmp;
extern HDC ArrowDC;
inline void ShootArrow(int pX, int pY, Direction dir) {
    Arrow a;
    a.x = pX; a.y = pY;
    a.dir = dir;
    a.dist = 0;
    a.active = true;
    arrow.push_back(a);
}

inline void UpdateArrows(Monster* monsterList, int monsterCount) {

    const int SPEED = 10;
    const int MAX_DIST = 250;
    const int DAMAGE = 5;

    for (auto& a : arrow) {
        if (!a.active) continue;

        switch (a.dir) {
        case DIR_DOWN:
            a.y += SPEED;
            break;
        case DIR_DOWN_RIGHT:
            a.x += SPEED;
            a.y += SPEED;
            break;
        case DIR_RIGHT:
            a.x += SPEED;
            break;
        case DIR_UP_RIGHT:
            a.x += SPEED;
            a.y -= SPEED;
            break;
        case DIR_UP:
            a.y -= SPEED;
            break;
        case DIR_UP_LEFT:
            a.x -= SPEED;
            a.y -= SPEED;
            break;
        case DIR_LEFT:
            a.x -= SPEED;
            break;
        case DIR_DOWN_LEFT:
            a.x -= SPEED;
            a.y += SPEED;
            break;
        }
        a.dist += SPEED;
        if (a.dist > MAX_DIST) {
            a.active = false;
            continue;
        }

        for (int i = 0; i < monsterCount; ++i) {
            Monster& m = monsterList[i];
            if (m.hp <= 0) continue;
            
            int dx = m.x - a.x;
            int dy = m.y - a.y;

            bool inRange = false;
            inRange = (dx * dx + dy * dy) <= (35 * 35);
            if (inRange) {
                m.hp = max(0, m.hp - DAMAGE);
                m.hitFlag = true;
                m.hitTime = GetTickCount64();
                a.active = false;
                break;
            }
        }

        arrow.erase(
            remove_if(arrow.begin(), arrow.end(),
                [](const Arrow& a) { return !a.active; }),
            arrow.end());
    }
}

inline void DrawArrows(HDC mdc, int bx, int by) {
    if (!ArrowDC) return;
    const int SPR_W = 60;
    const int SPR_H = 60;

    for (auto& a : arrow) {
        if (!a.active) continue;

        int dx = int(a.x) - bx;
        int dy = int(a.y) - by;

        int col = 0, row = 0;
        switch (a.dir) {
        case DIR_LEFT:       col = 0; row = 0; break;
        case DIR_RIGHT:      col = 1; row = 0; break;
        case DIR_UP:         col = 2; row = 0; break;
        case DIR_DOWN:       col = 3; row = 0; break;

        case DIR_DOWN_LEFT:  col = 0; row = 1; break;
        case DIR_DOWN_RIGHT: col = 1; row = 1; break;
        case DIR_UP_LEFT:    col = 2; row = 1; break;
        case DIR_UP_RIGHT:   col = 3; row = 1; break;
        }

        TransparentBlt(mdc, dx - SPR_W / 2, dy - SPR_H / 2, SPR_W, SPR_H, ArrowDC, col * SPR_W, row * SPR_H, SPR_W, SPR_H, RGB(0, 0, 255));
    }
}


//마법 지팡이
struct Magic {

    float x, y;
    Direction dir;
    float dist;
    bool active;
};
extern vector<Magic> magics;
extern HBITMAP fireBmp;

extern bool    useWaterEffect;
extern HDC     FireDC;
extern HDC     waterEffectDC;


inline void ShootMagic(int pX, int pY, Direction dir) {
    Magic m{ float(pX), float(pY), dir, 0.f, true };
    magics.push_back(m);
}

inline void UpdateMagics(Monster* monsterList, int monsterCount) {
    const int SPEED = 4;
    const int MAX_DIST = 210;
    const int DAMAGE = 15;
    const int FRAME_LEN = 70;
    for (auto& m : magics) {
        if (!m.active) continue;

        switch (m.dir) {
        case DIR_DOWN:        m.y += SPEED; break;
        case DIR_DOWN_RIGHT:  m.x += SPEED; m.y += SPEED; break;
        case DIR_RIGHT:       m.x += SPEED; break;
        case DIR_UP_RIGHT:    m.x += SPEED; m.y -= SPEED; break;
        case DIR_UP:          m.y -= SPEED; break;
        case DIR_UP_LEFT:     m.x -= SPEED; m.y -= SPEED; break;
        case DIR_LEFT:        m.x -= SPEED; break;
        case DIR_DOWN_LEFT:   m.x -= SPEED; m.y += SPEED; break;
        }
        m.dist += SPEED;
        if (m.dist > MAX_DIST) {
            m.active = false;
            continue;
        }
        for (int i = 0; i < monsterCount; ++i) {
            Monster& mon = monsterList[i];
            if (mon.hp <= 0) continue;
            float dx = mon.x - m.x;
            float dy = mon.y - m.y;
            if (dx * dx + dy * dy <= 35 * 35) {
                mon.hp = max(0, mon.hp - DAMAGE);
                mon.hitFlag = true;
                mon.hitTime = GetTickCount64();
                m.active = false;
                break;
            }
        }
    }
    magics.erase(
        remove_if(magics.begin(), magics.end(),
            [](auto& m) { return !m.active; }),
        magics.end());
}

inline void DrawMagics(HDC mdc, int bx, int by) {
    DWORD now = GetTickCount64();
    HDC magicDC = useWaterEffect ? waterEffectDC : FireDC;
    constexpr int WATER_FRAME_COUNT = 2;
    int waterFrame = (now / 200) % WATER_FRAME_COUNT;

    if (!FireDC) return;
    const int SPR_W = 60;
    const int SPR_H = 60;
    for (auto& m : magics) {
        if (!m.active) continue;
        int frame = min(2, int(m.dist) / 40);

        int row = 0;
        switch (m.dir) {
        case DIR_LEFT:       row = 0; break;
        case DIR_RIGHT:      row = 1; break;
        case DIR_UP:         row = 2; break;
        case DIR_DOWN:       row = 3; break;
        case DIR_UP_LEFT:    row = 4; break;
        case DIR_UP_RIGHT:   row = 5; break;
        case DIR_DOWN_LEFT:  row = 6; break;
        case DIR_DOWN_RIGHT: row = 7; break;
        }
        int dx = int(m.x) - bx;
        int dy = int(m.y) - by;
        if (useWaterEffect) {
            TransparentBlt(mdc, dx - SPR_W / 2, dy - SPR_H / 2, SPR_W, SPR_H, magicDC, waterFrame * SPR_W, 0, SPR_W, SPR_H, RGB(0, 0, 255));
        }
        else {
            TransparentBlt(mdc, dx - SPR_W / 2, dy - SPR_H / 2, SPR_W, SPR_H, magicDC, frame * SPR_W, row * SPR_H, SPR_W, SPR_H, RGB(0, 0, 255));
        }
    }
}

//250914
void CheckBossHit(Boss& boss, Player& p, int bx, int by, Direction playerDirection, DWORD currentTime, bool& boss_flag, int itemID) {

    if (boss.hp <= 0) return;

    //보스 위치
    int dx = (boss.x - bx) - p.x;
    int dy = (boss.y - by) - p.y;
    int dist = dx * dx + dy * dy;


    auto damageToBoss =
        [&](int dmg) {

        if (boss.hp <= 0) return;

        boss.hp -= dmg; //보스 체력 깍기
        if (boss.hp < 0) boss.hp = 0;
        boss.hitFlag = true;
        boss.hitTime = currentTime;

        if (boss.hp == 0) {
            if (!challenge[6]) challenge[6] = 1; //도전과제
            boss_flag = false;
        }
        };

    bool daggerHit = false;
    switch (playerDirection) {
    case DIR_DOWN: {
        if (dy > 0) daggerHit = true;
        break;
    }
    case DIR_DOWN_RIGHT: {
        if (dx > 0 && dy > 0) daggerHit = true;
        break;
    }
    case DIR_RIGHT: {
        if (dx > 0) daggerHit = true;
        break;
    }
    case DIR_UP_RIGHT: {
        if (dx > 0 && dy < 0) daggerHit = true;
        break;
    }
    case DIR_UP: {
        if (dy < 0) daggerHit = true;
        break;
    }
    case DIR_UP_LEFT: {
        if (dx < 0 && dy < 0) daggerHit = true;
        break;
    }
    case DIR_LEFT: {
        if (dx < 0) daggerHit = true;
        break;
    }
    case DIR_DOWN_LEFT: {
        if (dx < 0 && dy > 0) daggerHit = true;
        break;
    }
    }

    //단검 공격

    const int R_DAGGER = 150;
    const int D_DAGGER = 10;

    if (itemID == 1) {
        if (daggerHit && dist <= R_DAGGER * R_DAGGER) {
            damageToBoss(D_DAGGER);
        }
    }

    // 장검 공격
    const int R_LONGSWORD = 200;
    const int D_LONGSWORD = 10;

    if (itemID == 2) {
        if (daggerHit && dist <= R_LONGSWORD * R_LONGSWORD) {
            damageToBoss(D_LONGSWORD);
        }
    }

    //화살 공격
    const int R_ARROW = 130;
    const int D_ARROW = 5;

    if (itemID == 3) {
		extern vector<Arrow> arrow;
        for (auto& a : arrow) {
            if (!a.active) continue;
            int adx = boss.x - a.x;
            int ady = boss.y - a.y;
            int adist = adx * adx + ady * ady;
            if (adist <= R_ARROW * R_ARROW) {
                damageToBoss(D_ARROW);
                a.active = false;
                break;
            }
		}
    }

    //마법 공격
    const int R_MAGIC = 130;
    const int D_MAGIC = 15;

    if (itemID == 4) {
		extern vector<Magic> magics;
        for (auto& m : magics) {
            if (!m.active) continue;
            int mdx = boss.x - m.x;
            int mdy = boss.y - m.y;
            int mdist = mdx * mdx + mdy * mdy;
            if (mdist <= R_MAGIC * R_MAGIC) {
                damageToBoss(D_MAGIC);
                m.active = false;
                break;
            }
        }
    }
}
