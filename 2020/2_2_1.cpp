#include <bits/stdc++.h>
using namespace std;

int n;
int board[500][500];
long long outDust = 0;

// 왼쪽, 아래, 오른쪽, 위 순
int dr[4] = {0, 1, 0, -1};
int dc[4] = {-1, 0, 1, 0};

// 방향별 모래 비율 좌표 (기준: 왼쪽으로 이동할 때)
// 비율 순서: 1%, 1%, 2%, 2%, 7%, 7%, 10%, 10%, 5%
vector<pair<int,int>> sandPos[4] = {
    // LEFT
    { {-1,1}, {1,1}, {-1,0}, {1,0}, {-1,-1}, {1,-1}, {0,-2}, {0,-1}, {0,-3} },
    // DOWN
    { {-1,-1}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,1}, {2,0}, {1,0}, {3,0} },
    // RIGHT
    { {-1,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {1,1}, {0,2}, {0,1}, {0,3} },
    // UP
    { {1,1}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,-1}, {-2,0}, {-1,0}, {-3,0} }
};

// 비율들
int percentVal[9] = {1,1,2,2,7,7,10,10,5};

void spread(int r, int c, int dir) {
    int dust = board[r][c];
    if (dust == 0) return;

    int moved = 0;

    // 9개 방향 처리
    for (int i = 0; i < 9; i++) {
        int nr = r + sandPos[dir][i].first;
        int nc = c + sandPos[dir][i].second;

        int spreadDust = (dust * percentVal[i]) / 100;
        moved += spreadDust;

        // 격자 밖으로 나가면 outDust에 더함
        if (nr < 0 || nr >= n || nc < 0 || nc >= n)
            outDust += spreadDust;
        else
            board[nr][nc] += spreadDust;
    }

    // 마지막 남은 먼지(alpha)
    int alpha = dust - moved;

    int ar = r + dr[dir];
    int ac = c + dc[dir];

    if (ar < 0 || ar >= n || ac < 0 || ac >= n)
        outDust += alpha;
    else
        board[ar][ac] += alpha;

    board[r][c] = 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> board[i][j];

    int r = n/2, c = n/2;  // 시작: 정가운데
    int dir = 0;           // 왼쪽부터 시작
    int moveCnt = 1;       // 1칸 이동 시작
    bool finish = false;

    while(true){
        for(int k=0; k<2; k++){
            for(int i=0; i<moveCnt; i++){
                r += dr[dir];
                c += dc[dir];

                spread(r, c, dir);

                if (r == 0 && c == 0) {
                    finish = true;
                    break;
                }
            }
            if (finish) break;

            dir = (dir + 1) % 4;
        }
        if (finish) break;

        moveCnt++;
    }

    cout << outDust << "\n";
    return 0;
}
