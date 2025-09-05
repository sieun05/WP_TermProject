#pragma once
#include "Cell.h"
#include "Direction.h"

extern int bx, by;

struct Player {

	Player() = default;
	Player(int x, int y, int speed,int hp,int mp, int hunger)
		: x{ x }, y{ y }, speed{ speed }, hp{ hp }, mp{ mp }, hunger {hunger} {
	};

	int x;
	int y;
	int speed;
	bool Lctrl_click = false;	//(25.05.31 / 김정현)
	bool Lshift_click = false;	//L-crtl, L-shift 토글
	int hp;	//(25.05.31) - 김정현
	int mp;	//hp,mp,허기 추가
	int hunger; //허기
	bool died_flag = false;

	Direction dir;
	int animTimer;
	int anim;

	bool isAttacking = false;	//공격 변수 추가
	int atkType = 0;
	int atkDir;
	DWORD atkStart = 0;
	int atkFrame = 0;

	int maxHp;	//장비 변수 추가
	int baseHp;

	int maxMp; //장비 변수 또 추가
	int baseMp;

	bool isHurt = false; //피해 비트맵 관련 변수 추가
	DWORD hurtStart = 0;
	static constexpr DWORD HURT_DURATION = 300;

	static constexpr DWORD COOLDOWN_MS = 700; //무기 쿨타임
	DWORD lastArrowTime = 0;
	DWORD lastMagicTime = 0;

	//2506103
	DWORD lastHitTime = 0;
};

//(25.06.07) - 김정현
//플레이어 비트맵 추가

static constexpr int PLAYER_SPRITE_SIZE = 64;  // 한 프레임 크기
static constexpr int PLAYER_SPRITE_FRAMES = 4;   // 프레임 수

//25.06.08 - 오시은
//캐릭터 크기 조정 변수 추가
static constexpr int PLAYER_SIZE = 80;

extern HBITMAP PlayerBmp;
extern HDC PlayerDC;
extern int PlayerBmpWidth;
extern int PlayerBmpHeight;

inline bool InitPlayerSprite(HINSTANCE hInst) {

	PlayerBmp = (HBITMAP)LoadImage(nullptr,L"비트맵\\플레이어\\1.bmp",IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (!PlayerBmp) 
		return false;
	PlayerDC = CreateCompatibleDC(nullptr);
	SelectObject(PlayerDC, PlayerBmp);

	BITMAP bm{};
	GetObject(PlayerBmp, sizeof(bm), &bm);
	PlayerBmpWidth = bm.bmWidth;
	PlayerBmpHeight = bm.bmHeight;

	return true;
}

inline void CleanupPlayerSprite() {
	if (PlayerDC)
		DeleteDC(PlayerDC);
	if (PlayerBmp)
		DeleteObject(PlayerBmp);
}

inline void UpdatePlayerAnimation(Player* p) {
	if (!p) return;
	p->animTimer++;

	//25.06.08 - 오시은
	//캐릭터 속도에 따라 애니메이션 속도 변화

	int delay_num{};
	if (p->Lctrl_click)
		delay_num = 2;
	else if (p->Lshift_click)
		delay_num = 8;
	else
		delay_num = 4;

	if (p->animTimer >= delay_num) {
		p->animTimer = 0;
		p->anim = (p->anim + 1) % PLAYER_SPRITE_FRAMES;
	}
}

inline void DrawPlayer(const Player* p, HDC hdc) {
	if (!p || !hdc) return;

	//25.06.08 - 오시은
	//캐릭터 크기 조정 변수 수정
	int half = PLAYER_SIZE / 2;
	int drawX = p->x - half;
	int drawY = p->y - half;

	int row = 0;
	switch (p->dir) {
	case DIR_DOWN:
	case DIR_DOWN_LEFT:
	case DIR_DOWN_RIGHT:
		row = 0; break;
	case DIR_LEFT:
		row = 1; break;
	case DIR_RIGHT:
		row = 2; break;
	case DIR_UP:
	case DIR_UP_LEFT:
	case DIR_UP_RIGHT:
		row = 3; 
		break;
	default:
		row = 0; break;
	}

	int srcX = (p->anim % PLAYER_SPRITE_FRAMES) * PLAYER_SPRITE_SIZE;
	int srcY;

	if (!p->isHurt)
		srcY = row * PLAYER_SPRITE_SIZE;
	else
		srcY = (row + 4) * PLAYER_SPRITE_SIZE;
	TransparentBlt(hdc, drawX, drawY, PLAYER_SIZE, PLAYER_SIZE, PlayerDC, srcX, srcY,PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE,RGB(0, 0, 255));
}

//(25.06.08) - 오시은
//인벤 캐릭터 그리는 함수
inline void DrawPlayer(int x, int y, int iven_character_anim, HDC hdc) {
	if (!hdc) return;

	float half = PLAYER_SIZE * 1.5 / 2;
	int drawX = x - half;
	int drawY = y - half;

	int row = 0;

	int srcX = (iven_character_anim % PLAYER_SPRITE_FRAMES) * PLAYER_SPRITE_SIZE;
	int srcY = row * PLAYER_SPRITE_SIZE;
	TransparentBlt(hdc, drawX, drawY, PLAYER_SIZE * 1.5, PLAYER_SIZE * 1.5, PlayerDC, srcX, srcY, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE, RGB(0, 0, 255));
}
