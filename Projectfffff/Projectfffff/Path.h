#pragma once

//(25.06.07) - 김정현
//몬스터 이동 로직(플레이어를 쫒아가는 경로 추적)

#include <vector>
#include <utility>
#include <limits> 

#include "Cell.h"
#include <queue>
#include <cmath>

struct Point { int r, c; };

std::vector<Point> AStar(
    const Point& start,
    const Point& goal
);

static int heuristic(const Point& a, const Point& b) {
    return abs(a.r - b.r) + abs(a.c - b.c);
}

static inline bool inBounds(int r, int c) {
    return r >= 0 && c >= 0 && r < MAP_HEIGHT && c < MAP_WIDTH;
}

std::vector<Point> AStar(const Point& start, const Point& goal) {
    using NodeKey = std::pair<int, int>;
    struct Node { Point p; int g, f; Point parent; };
    auto key = [&](Point p) { return NodeKey{ p.r,p.c }; };

    struct Cmp { bool operator()(Node const& a, Node const& b) const { return a.f > b.f; } };
    std::priority_queue<Node, std::vector<Node>, Cmp> open;
    std::map<NodeKey, int> bestG;
    open.push({ start,0,heuristic(start,goal),{-1,-1} });
    bestG[key(start)] = 0;

    std::map<NodeKey, Point> parent;

    const int dr[4] = { -1,1,0,0 }, dc[4] = { 0,0,-1,1 };
    while (!open.empty()) {
        auto cur = open.top(); open.pop();
        if (cur.p.r == goal.r && cur.p.c == goal.c) {
            std::vector<Point> path;
            Point p = goal;
            while (!(p.r == start.r && p.c == start.c)) {
                path.push_back(p);
                p = parent[key(p)];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }
        for (int i = 0; i < 4; i++) {
            int nr = cur.p.r + dr[i], nc = cur.p.c + dc[i];
            if (!inBounds(nr, nc)) continue;
            int type = game_map[nr][nc].type;
            if (type != 0 && type != 5 && type != 6) continue;
            int ng = cur.g + 1;
            NodeKey nk{ nr,nc };
            if (!bestG.count(nk) || ng < bestG[nk]) {
                bestG[nk] = ng;
                parent[nk] = cur.p;
                int nf = ng + heuristic({ nr,nc }, goal);
                open.push({ {nr,nc},ng,nf,cur.p });
            }
        }
    }
    return {};
}