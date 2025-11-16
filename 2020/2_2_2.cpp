#include <bits/stdc++.h>
using namespace std;
int n, qq, grid_size, a[64][64], level, na[64][64];
const int dy[4] = {1, 0, 0, -1};
const int dx[4] = {0, 1, -1, 0};
bool visited[64][64];
queue<pair<int, int>> q;

// half_size 크기의 격자를 move_dir 방향으로 이동
void spin(int start_y, int start_x, int half_size, int move_dir) {
    for (int y = start_y; y < start_y + half_size; y++) {
        for (int x = start_x; x < start_x + half_size; x++) {
            int ny = y + dx[move_dir] * half_size;
            int nx = x + dy[move_dir] * half_size;
            na[ny][nx] = a[y][x];
        }
    }
}
void move(int level) {
    // spin 이후의 상태를 저장할 na를 0으로 초기화
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            na[i][j] = 0;
        }
    }
    int box_size = (1 << level);
    int half_size = box_size / 2;

    // 조건에 맞게 회전을 진행한다.
    for (int i = 0; i < grid_size; i += box_size) {
        for (int j = 0; j < grid_size; j += box_size) {
            // 4개의 사분면을 각각 알맞은 방향으로 이동
            spin(i, j, half_size, 0);                      // 왼쪽 위 → 오른쪽으로
            spin(i, j + half_size, half_size, 1);          // 오른쪽 위 → 아래로
            spin(i + half_size, j, half_size, 2);          // 왼쪽 아래 → 위로
            spin(i + half_size, j + half_size, half_size, 3); // 오른쪽 아래 → 왼쪽으로
        }
    }

    // spin 이후 결과를 a로 복사
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            a[i][j] = na[i][j];
        }
    }
}

void melt() {
    // melt 이후의 상태를 저장할 na를 0으로 초기화
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            na[i][j] = 0;
        }
    }

    // 인접한 칸의 수가 3개 이하인 곳의 얼음을 찾아 1씩 녹인다.
    for (int y = 0; y < grid_size; y++) {
        for (int x = 0; x < grid_size; x++) {
            int cnt = 0;
            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (nx >= 0 && nx < grid_size && ny >= 0 && ny < grid_size && a[ny][nx]) cnt++;
            }
            if(a[y][x] && cnt < 3) na[y][x] = a[y][x] - 1;
            else na[y][x] = a[y][x];
        }
    }

    // melt 이후의 결과를 a로 복사
    for(int i = 0; i < grid_size; i++)
        for(int j = 0; j < grid_size; j++)
            a[i][j] = na[i][j];
}

int bfs() {
    int mx = 0;
    while (q.size()) {
        auto [y, x] = q.front();
        mx++; q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < grid_size && ny >= 0 && ny < grid_size && !visited[ny][nx] && a[ny][nx]) {
                visited[ny][nx] = 1; q.push({ny, nx});
            }
        }
    }
    return mx;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    cin >> n >> qq;
    grid_size = (1 << n);
	for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            cin >> a[i][j];
        }
    }
    while(qq--) {
        cin >> level;
        if (level) move(level);
        melt();
    }
    
    // 남아있는 빙하의 총 양
    int remain = 0;
    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
            remain += a[i][j];
        }
    }
    cout << remain << "\n";

    // 얼음 군집 중 최대 크기
    int mx = 0;
    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
            if(a[i][j] && !visited[i][j]) {
                visited[i][j] = true;
                q.push({i, j});
                mx = max(mx, bfs());
            }
        }
    }
    cout << mx << "\n";
}