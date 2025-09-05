#pragma once
#include "Cell.h"
#include "Path.h"

//(25.06.07) - 김정현
//몬스터 이동 로직 수정

#define MONSTER_SIZE 70

extern int bx, by;
extern default_random_engine dre;
extern uniform_int_distribution<int> ran;

typedef enum {
	Monster_1, Monster_2
}MonsterType;

struct Monster {
    Monster() = default;
    Monster(int x, int y, int hp, int speed, HBITMAP bmp, MonsterType type)
        :x{ x }, y{ y }, hp{ hp }, speed{ speed }, bmp{ bmp }, type{ type }, dir{ 0 }, anim{ 0 }, animTimer{ 0 } {
    };

    int x;
    int y;
    int hp;
    int speed;
    HBITMAP bmp;
    MonsterType type;

    int dir;
    int anim;
    int animTimer;

    bool hitFlag = false;
    DWORD hitTime = 0;

    bool chasing = false; //플레이어 발견 변수
    int roamDir = 0;
    int roamSteps = 0;

    std::vector<Point> path; 
    size_t pathIdx = 0;

    void computePath(const Point& playerCell);

    void followPath();

    bool checkCollisionWithWalls();
};

extern Cell game_map[MAP_WIDTH][MAP_HEIGHT];

inline bool SpawnMonster1(Monster* m) {

    if (!m) return false;
    uniform_int_distribution<int> distX(0, MAP_WIDTH - 1);
    uniform_int_distribution<int> distY(0, MAP_HEIGHT - 1);
    while (true) {
        int col = distX(dre);
        int row = distY(dre);

        if (game_map[row][col].type == 5) {
            m->x = col * CELL_SIZE + (CELL_SIZE / 2);
            m->y = row * CELL_SIZE + (CELL_SIZE / 2);
            return true;
        }
    }
    return false;
}
inline bool SpawnMonster2(Monster* m) {

    if (!m) return false;
    uniform_int_distribution<int> distX(0, MAP_WIDTH - 1);
    uniform_int_distribution<int> distY(0, MAP_HEIGHT - 1);
    while (true) {
        int col = distX(dre);
        int row = distY(dre);

        if (game_map[row][col].type == 6) {
            m->x = col * CELL_SIZE + (CELL_SIZE / 2);
            m->y = row * CELL_SIZE + (CELL_SIZE / 2);
            return true;
        }
    }
    return false;
}

static int CanMove_Monster(int x, int y) {
	int col = x / CELL_SIZE;
	int row = y / CELL_SIZE;

	if (col < 0 || col >= MAP_WIDTH || row < 0 || row >= MAP_HEIGHT)
		return 0;
    int type = game_map[row][col].type;
    if (type != 0 && type != 5 && type != 6)
        return 0;

	return 1;
}


inline bool InitMonster(Monster* m, MonsterType type){
    if (!m) return false;

    m->type = type;

    switch (type) {
    case Monster_1:
        m->speed = 2;
        m->hp = 50;

        m->bmp = (HBITMAP)LoadImage(nullptr,L"비트맵\\몬스터\\1.bmp",IMAGE_BITMAP,0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        break;

    case Monster_2:
        m->speed = 2;
        m->hp = 50;
        m->bmp = (HBITMAP)LoadImage(nullptr,L"비트맵\\몬스터\\2.bmp",IMAGE_BITMAP,0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        break;
    default:
        m->speed = 1;
        m->hp = 1;
        m->bmp = NULL;
        break;
    }

    m->roamDir = ran(dre);
    m->roamSteps = 50 + ran(dre) * 20;
    return (m->bmp != NULL);
}

inline bool UpdateMonster(Monster* m, int dx, int dy)
{
    if (!m) return false;

    int half = MONSTER_SIZE / 2;
    bool didMove = false;

    if (dx != 0) {
        int candX = m->x + dx * m->speed;
        int leftPixel = candX - half + 10;
        int rightPixel = candX + half - 20;
        
        int topPixel = m->y - half + 30;
        int bottomPixel = m->y + half + 30;

        if (leftPixel >= 0 && rightPixel <= MAP_PIXEL_WIDTH&& topPixel >= 0 && bottomPixel <= MAP_PIXEL_HEIGHT) {
            if (dx > 0) {
                int rightCol = rightPixel / CELL_SIZE;
                int topRow = topPixel / CELL_SIZE;
                int bottomRow = bottomPixel / CELL_SIZE;
                if (rightCol < MAP_WIDTH && (game_map[topRow][rightCol].type == 0 || game_map[topRow][rightCol].type == 5 || game_map[topRow][rightCol].type == 6) &&
                    (game_map[bottomRow][rightCol].type == 0 || game_map[bottomRow][rightCol].type == 5 || game_map[bottomRow][rightCol].type == 6)) {
                    m->x = candX;
                    didMove = true;
                }
            }
            else {
                
                int leftCol = leftPixel / CELL_SIZE;
                int topRow = topPixel / CELL_SIZE;
                int bottomRow = (bottomPixel) / CELL_SIZE;
                if (leftCol >= 0 && (game_map[topRow][leftCol].type == 0 || game_map[topRow][leftCol].type == 5 || game_map[topRow][leftCol].type == 6) &&
                    (game_map[bottomRow][leftCol].type == 0 || game_map[bottomRow][leftCol].type == 5 || game_map[bottomRow][leftCol].type == 6)) {
                    m->x = candX;
                    didMove = true;
                }
            }
        }
    }

    if (dy != 0) {
        int candY = m->y + dy * m->speed;
        int leftPixel = m->x - half;
        int rightPixel = m->x + half;
        int topPixel = candY - half;
        int bottomPixel = candY + half;

        if (leftPixel >= 0 && rightPixel <= MAP_PIXEL_WIDTH && topPixel >= 0 && bottomPixel <= MAP_PIXEL_HEIGHT) {
            if (dy > 0) {
                int bottomRow = bottomPixel / CELL_SIZE;
                int leftCol = leftPixel / CELL_SIZE;
                int rightCol = (rightPixel) / CELL_SIZE;
                if (bottomRow < MAP_HEIGHT && game_map[bottomRow][leftCol].type == 0 && game_map[bottomRow][rightCol].type == 0) {
                    m->y = candY;
                    didMove = true;
                }
            }
            else {
                int topRow = topPixel / CELL_SIZE;
                int leftCol = leftPixel / CELL_SIZE;
                int rightCol = (rightPixel) / CELL_SIZE;
                if (topRow >= 0 && topRow < MAP_HEIGHT && game_map[topRow][leftCol].type == 0 && game_map[topRow][rightCol].type == 0) {
                    m->y = candY;
                    didMove = true;
                }
            }
        }
    }
    if (dx != 0 || dy != 0) {
        if (dx > 0 && dy == 0)        m->dir = 2; 
        else if (dx < 0 && dy == 0)   m->dir = 6; 
        else if (dx == 0 && dy > 0)   m->dir = 0;
        else if (dx == 0 && dy < 0)   m->dir = 4; 
        else if (dx > 0 && dy > 0)    m->dir = 1;
        else if (dx > 0 && dy < 0)    m->dir = 3; 
        else if (dx < 0 && dy < 0)    m->dir = 5; 
        else if (dx < 0 && dy > 0)    m->dir = 7;
    
    }

    m->animTimer++;
    if (m->animTimer >= 8) {
        m->animTimer = 0;
        m->anim = (m->anim + 1) % 4;
    }
    return didMove;
}

void DrawMonster(const Monster* m, HDC hdc) {
    if (!m || !hdc) return;

    DWORD now = GetTickCount64();
    bool stillHit = m->hitFlag && (now - m->hitTime < 500);

    int halfSize = MONSTER_SIZE / 2;
    int drawX = m->x - bx - halfSize;
    int drawY = m->y - by - halfSize;

    if (stillHit == false && m->hitFlag)
        const_cast<Monster*>(m)->hitFlag = false;

    if (m->bmp) {
        HDC memDC = CreateCompatibleDC(hdc);
        SelectObject(memDC, m->bmp);
        int monX;
        int monY;
        if (stillHit) {
            monX = (m->anim % 4) * 70;
            monY = (m->dir % 8 + 8) * 70;
        }
        else {
            monX = (m->anim % 4) * 70;
            monY = (m->dir % 8) * 70;
        }
     
        TransparentBlt(hdc, drawX, drawY, MONSTER_SIZE, MONSTER_SIZE, memDC, monX, monY, 70, 70, RGB(0, 0, 255));
        DeleteDC(memDC);
    }
}

void Monster::computePath(const Point& playerCell) {
    int playerX = playerCell.c * CELL_SIZE + CELL_SIZE / 2;
    int playerY = playerCell.r * CELL_SIZE + CELL_SIZE / 2;
    int dx = playerX - x;
    int dy = playerY - y;
    int distSq = dx * dx + dy * dy;

    if (!chasing && distSq <= 300 * 300) {
        chasing = true;
    }

    if (chasing) {
        Point selfCell{ y / CELL_SIZE, x / CELL_SIZE };
        path = AStar(selfCell, playerCell);
        pathIdx = 1;
    }
}

void Monster::followPath() {
    if (chasing && pathIdx < path.size()) {
        if (pathIdx < path.size()) {
            Point next = path[pathIdx];
            int targetX = next.c * CELL_SIZE + CELL_SIZE / 2;
            int targetY = next.r * CELL_SIZE + CELL_SIZE / 2;
            int dx = targetX - x;
            int dy = targetY - y;
            
            int vx = targetX - x;
            int vy = targetY - y;
            int sx = (vx > 0) - (vx < 0);
            int sy = (vy > 0) - (vy < 0);

            if (sx > 0 && sy == 0) 
                dir = 2;
            else if (sx < 0 && sy == 0) 
                dir = 6;
            else if (sx == 0 && sy > 0) 
                dir = 0;
            else if (sx == 0 && sy < 0) 
                dir = 4;
            else if (sx > 0 && sy > 0)  
                dir = 1;
            else if (sx > 0 && sy < 0)  
                dir = 3;
            else if (sx < 0 && sy < 0)  
                dir = 5;
            else if (sx < 0 && sy > 0)  
                dir = 7;

            x += sx * speed;
            y += sy * speed;

            if (abs(x - targetX) < speed && abs(y - targetY) < speed) {
                ++pathIdx;
            }
        }
        else {
            if (--roamSteps <= 0) {
                roamDir = ran(dre) % 4;
                roamSteps = 50 + ran(dre) * 20;
            }
            int dx = (roamDir == 0 ? 1 : roamDir == 1 ? -1 : 0);
            int dy = (roamDir == 2 ? 1 : roamDir == 3 ? -1 : 0);
            UpdateMonster(this, dx, dy);
        }
    }
    else {
        int dir = roamDir;
        int steps = roamSteps;
        if (--roamSteps <= 0) {
            roamDir = ran(dre) % 4;
            roamSteps = 50 + ran(dre) % 20;
        }

        int dx = (dir == 0 ? 1 : dir == 1 ? -1 : 0);
        int dy = (dir == 2 ? 1 : dir == 3 ? -1 : 0);
        UpdateMonster(this, dx, dy);
    }
}

bool Monster::checkCollisionWithWalls() {
    int cellR = y / CELL_SIZE;
    int cellC = x / CELL_SIZE;
    int type = game_map[cellR][cellC].type;
    if (type != 0 && type != 5 && type != 6) //이동 금지 타일
        return true;
    return false;
}