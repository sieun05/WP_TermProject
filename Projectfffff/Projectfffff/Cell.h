#pragma once
//#include "Monster.h"
#include <random>

using namespace std;

#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#define MAP_PIXEL_WIDTH MAP_WIDTH * CELL_SIZE
#define MAP_PIXEL_HEIGHT MAP_HEIGHT * CELL_SIZE

#define SCREEN_WIDTH 32
#define SCREEN_HEIGHT 18

#define CELL_SIZE 60

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> flag{ 0, 1 };
uniform_int_distribution<int> ran{ 0, 3 };
uniform_int_distribution<int> drop_ran{ 1, 10 };
uniform_int_distribution<int> ranattack{ 0, 2 };

////(25.06.08) - 오시은
//수정함

struct Cell {
	Cell() = default;
	Cell(int type) : type{ type } {};
	Cell(int type, int block_num) : type{ type }, block_num{ block_num } {};
	Cell(const Cell& c) = default;
	Cell& operator=(const Cell& c) = default;

	int type;
	int block_num;
	int broken_cnt{};
};

extern Cell game_map[MAP_HEIGHT][MAP_WIDTH];

void DrawWallTile(HDC& hdc, HDC* memdc, HDC& memdc2, int screenX, int screenY, int mapX, int mapY, int wallpaint) {
	int srcX{}, srcY{};

	if (mapY + 1 < MAP_HEIGHT &&
		(game_map[mapY + 1][mapX].type != 1 and game_map[mapY + 1][mapX].type != 2 and game_map[mapY + 1][mapX].type != 3)) {
		if (wallpaint == 1) return;

		srcX = 0, srcY = 0; //또는 1 0
		if ((mapY + mapX) % 3 == 0) srcX++;
		TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));

		//벽 바깥쪽모서리
		{
			if (mapX - 1 > 0 and (game_map[mapY][mapX - 1].type == 0 or game_map[mapY][mapX - 1].type == 7)) {
				srcX = 2, srcY = 0;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX + 1 < MAP_WIDTH and (game_map[mapY][mapX + 1].type == 0 or game_map[mapY][mapX + 1].type == 7)) {
				srcX = 3, srcY = 0;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
		}

		//벽 앞에 풀밭
		if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 5) {
			srcX = 2, srcY = 2;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, *memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}

		//벽 앞에 주황풀
		if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 6) {
			srcX = 2, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, *memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}

		//(25.06.10) - 오시은
		//벽 앞에 제작대, 요리제작대, 상자
		if (mapY + 1 < MAP_HEIGHT &&
			(game_map[mapY + 1][mapX].type == 9 or game_map[mapY + 1][mapX].type == 10)) {
			srcX = 1, srcY = 4;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		else if (mapY + 1 < MAP_HEIGHT && 
			game_map[mapY + 1][mapX].type == 11) {
			srcX = 0, srcY = 4;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
	}
	else {
		if (wallpaint == 0) return;

		srcX = 3; srcY = 2;
		TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));

		/*if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 0) {
			srcX = 3; srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 0) {
			srcX = 1, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}*/
		if (mapY + 2 < MAP_HEIGHT and
			(game_map[mapY + 1][mapX].type == 1 or game_map[mapY + 1][mapX].type == 2 or game_map[mapY + 1][mapX].type == 3) and
			not (game_map[mapY + 2][mapX].type == 1 or game_map[mapY + 2][mapX].type == 2 or game_map[mapY + 2][mapX].type == 3)) {
			srcX = 2, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}

		//(25.06.10) - 오시은
		//철벽, 금벽 반짝이
		if (game_map[mapY + 1][mapX].type == 2) {
			int ran = flag(dre);
			srcX = 0 + ran, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		else if (game_map[mapY + 1][mapX].type == 3) {
			int ran = flag(dre);
			srcX = 2 + ran, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
	}
}

void DrawGroundTile(HDC& hdc, HDC& memdc, int screenX, int screenY, int mapX, int mapY) {
	int srcX{}, srcY{};

	if (not
		(mapY + 1 < MAP_HEIGHT && game_map[mapY][mapX].type == 1 or
			mapY + 1 < MAP_HEIGHT && game_map[mapY][mapX].type == 2 or
			mapY + 1 < MAP_HEIGHT && game_map[mapY][mapX].type == 3)) {
		srcX = 0, srcY = 0;
		TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));

		//상하좌우 물일때
		{
			if (mapY - 1 > 0 and game_map[mapY - 1][mapX].type == 7) {
				srcX = 0, srcY = 1;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 7) {
				srcX = 1, srcY = 1;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 7) {
				srcX = 2, srcY = 1;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 7) {
				srcX = 3, srcY = 1;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
		}

		//상하좌우 풀일때
		{
			if (mapY - 1 > 0 and game_map[mapY - 1][mapX].type == 5) {
				srcX = 0, srcY = 2;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 5) {
				srcX = 1, srcY = 2;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 5) {
				srcX = 2, srcY = 2;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 5) {
				srcX = 3, srcY = 2;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
		}

		//상하좌우 주황풀일때
		{
			if (mapY - 1 > 0 and game_map[mapY - 1][mapX].type == 6) {
				srcX = 0, srcY = 3;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 6) {
				srcX = 1, srcY = 3;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 6) {
				srcX = 2, srcY = 3;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 6) {
				srcX = 3, srcY = 3;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
		}

		//(25.06.10) - 오시은
		//제작대, 요리제작대, 상자, 나무
		if (game_map[mapY][mapX].type == 9) {
			srcX = 2, srcY = 4;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		else if (game_map[mapY][mapX].type == 10) {
			srcX = 1, srcY = 4;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		else if (game_map[mapY][mapX].type == 11) {
			srcX = 0, srcY = 4;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		else if (game_map[mapY][mapX].type == 8) {
			srcX = 1, srcY = 0;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));

			if (mapY - 1 > 0 and game_map[mapY - 1][mapX].type == 8) {
				srcX = 2, srcY = 5;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 8) {
				srcX = 1, srcY = 5;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 8) {
				srcX = 3, srcY = 5;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 8) {
				srcX = 0, srcY = 5;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}

			if (mapY + 1 > 0 and (game_map[mapY+1][mapX].type == 9 or game_map[mapY + 1][mapX].type == 10)) {
				srcX = 1, srcY = 6;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
			if (mapY + 1 > 0 and game_map[mapY + 1][mapX].type == 11) {
				srcX = 0, srcY = 6;
				TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			}
		}
	}
}

void DrawGround2Tile(HDC& hdc, HDC& memdc, int screenX, int screenY, int mapX, int mapY) {
	int srcX{}, srcY{};

	srcX = 0, srcY = 0;
	TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
	/*if (not (mapY + 1 < MAP_HEIGHT && game_map[mapY + 1][mapX].type == 1)) {

	}*/
}

void DrawGroundwallTile(HDC& hdc, HDC& memdc, int screenX, int screenY, int mapX, int mapY) {
	int srcX{}, srcY{};

	if (mapY + 1 < MAP_HEIGHT &&
		(game_map[mapY + 1][mapX].type == 1 or game_map[mapY + 1][mapX].type == 2 or game_map[mapY + 1][mapX].type == 3)) {
		srcX = 3, srcY = 2; //또는 1 0
		TransparentBlt(hdc, screenX, screenY + 5, CELL_SIZE, CELL_SIZE - 5, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		if (mapY + 2 < MAP_HEIGHT and
			(game_map[mapY + 1][mapX].type == 1 or game_map[mapY + 1][mapX].type == 2 or game_map[mapY + 1][mapX].type == 3) and
			not (game_map[mapY + 2][mapX].type == 1 or game_map[mapY + 2][mapX].type == 2 or game_map[mapY + 2][mapX].type == 3)) {
			srcX = 2, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}

		//(25.06.10) - 오시은
		//철벽, 금벽 반짝이
		if (game_map[mapY + 1][mapX].type == 2) {
			int ran = flag(dre);
			srcX = 0 + ran, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		else if (game_map[mapY + 1][mapX].type == 3) {
			int ran = flag(dre);
			srcX = 2 + ran, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
	}

	//(25.06.10) - 오시은
	//제작대, 요리제작대, 상자
	if (mapY + 1 < MAP_HEIGHT &&
		(game_map[mapY + 1][mapX].type == 9 or game_map[mapY + 1][mapX].type == 10)) {
		srcX = 1, srcY = 4;
		TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
	}
	else if (game_map[mapY + 1][mapX].type == 11) {
		srcX = 0, srcY = 4;
		TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
	}
}

void DrawWaterTile(HDC& hdc, HDC& memdc, HDC& memdc2, int screenX, int screenY, int mapX, int mapY, int water_sel) {
	int srcX{}, srcY{};

	srcX = water_sel, srcY = 0;
	TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));

	//앞이 땅
	{
		if (mapY - 1 > 0 and
			(game_map[mapY - 1][mapX].type != 7)) {
			srcX = water_sel, srcY = 2;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
			srcX = 0, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 0) {
			srcX = 1, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 0) {
			srcX = 2, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 0) {
			srcX = 3, srcY = 1;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc2, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
	}

	//상하좌우 풀일때
	{
		if (mapY - 1 > 0 and game_map[mapY - 1][mapX].type == 5) {
			srcX = 0, srcY = 2;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 5) {
			srcX = 1, srcY = 2;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 5) {
			srcX = 2, srcY = 2;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 5) {
			srcX = 3, srcY = 2;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
	}

	//상하좌우 주황풀일때
	{
		if (mapY - 1 > 0 and game_map[mapY - 1][mapX].type == 6) {
			srcX = 0, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX + 1 < MAP_WIDTH and game_map[mapY][mapX + 1].type == 6) {
			srcX = 1, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapY + 1 < MAP_HEIGHT and game_map[mapY + 1][mapX].type == 6) {
			srcX = 2, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
		if (mapX - 1 > 0 and game_map[mapY][mapX - 1].type == 6) {
			srcX = 3, srcY = 3;
			TransparentBlt(hdc, screenX, screenY, CELL_SIZE, CELL_SIZE, memdc, 40 * srcX, 40 * srcY, 40, 40, RGB(0, 0, 255));
		}
	}

}