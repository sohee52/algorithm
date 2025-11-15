#include <bits/stdc++.h>
using namespace std;

int n;
int board[500][500];
long long outDust = 0;

// 이동 방향: 왼, 아래, 오른, 위
int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};

struct Node {
    int y, x, p;   // (y offset, x offset, spread percent)
};

Node pattern[4][9];

// alpha(남은 먼지)가 떨어지는 위치
// LEFT -> 왼, DOWN -> 아래, RIGHT -> 오른, UP -> 위
int ay[4] = {0, 1, 0, -1};
int ax[4] = {-1, 0, 1, 0};

// offset을 90도 반시계 회전
Node rotCCW(Node t) {
    return Node{-t.x, t.y, t.p};
}

void initPattern() {
    // LEFT 기준 패턴 (y,x,p)
    Node leftPat[9] = {
        {-1,  1,  1},
        { 1,  1,  1},
        {-2,  0,  2},
        { 2,  0,  2},
        {-1,  0,  7},
        { 1,  0,  7},
        {-1, -1, 10},
        { 1, -1, 10},
        { 0, -2,  5}
    };

    // LEFT 패턴을 pattern[0]에 복사
    for (int i = 0; i < 9; i++)
        pattern[0][i] = leftPat[i];

    // LEFT 패턴을 기준으로 90도씩 회전하여 4방향 패턴 생성
    // pattern[0] = LEFT 패턴
    // pattern[1] = LEFT를 90도 회전 → DOWN 패턴
    // pattern[2] = DOWN을 90도 회전 → RIGHT 패턴
    // pattern[3] = RIGHT를 90도 회전 → UP 패턴
    for (int d = 1; d < 4; d++) {
        for (int i = 0; i < 9; i++) {
            pattern[d][i] = rotCCW(pattern[d-1][i]);
        }
    }
}

void spread(int y, int x, int dir) {
    // 현재 칸 dust 가져오기
    int dust = board[y][x];
    if (dust == 0) return;

    int moved = 0;

    // 각 비율 칸 9개에 대해 먼지 뿌리기
    for (int i = 0; i < 9; i++) {
        int ny = y + pattern[dir][i].y;
        int nx = x + pattern[dir][i].x;
        int per = pattern[dir][i].p;

        int amt = dust * per / 100;
        moved += amt; // moved에 퍼진 양 누적

        // 영역 밖이면 outDust 증가
        if (ny < 0 || ny >= n || nx < 0 || nx >= n)
            outDust += amt;
        else // 안이면 board[ny][nx] 증가
            board[ny][nx] += amt;
    }

    // 남은 먼지 전체를 단 한 칸(alpha 위치)에 몰아서 보낸다.
    int remain = dust - moved; // 알파 칸에 들어갈 먼지량
    int ny = y + ay[dir]; // 알파 자리 계산
    int nx = x + ax[dir];

    // 알파 칸이 범위 밖이면 먼지는 outDust에 누적
    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
        outDust += remain;
    else // 범위 안이면 그 칸에 먼지가 쌓임
        board[ny][nx] += remain;

    // 현재 칸 먼지 제거
    board[y][x] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            cin >> board[y][x]; // 모래량 저장

    initPattern();

    // 토네이도가 (n/2, n/2) 중심에서 시작
    int y = n / 2;
    int x = n / 2;

    // LEFT부터 시작
    int dir = 0;

    int moveCnt = 1;
    bool finish = false;

    while (true) {
        // 달팽이 형태 이동 구현
        // 1칸 이동하고 방향 전환  
        // 1칸 이동하고 방향 전환  
        // 2칸 이동하고 방향 전환  
        // 2칸 이동하고 방향 전환  
        // 3칸 이동하고 방향 전환  
        // 3칸 이동하고 방향 전환  
        // ...
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < moveCnt; i++) {
                y += dy[dir];
                x += dx[dir];

                // 먼지를 퍼트리는 함수
                spread(y, x, dir);

                // (0,0) 도착하면 중단
                if (y == 0 && x == 0) {
                    finish = true;
                    break;
                }
            }
            if (finish) break;
            dir = (dir + 1) % 4; // 회전
        }
        if (finish) break;
        moveCnt++;
    }

    cout << outDust << "\n";
    return 0;
}
