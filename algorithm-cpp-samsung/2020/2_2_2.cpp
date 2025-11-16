#include <bits/stdc++.h>
using namespace std;
int n, qq, grid_size, a[64][64], level, na[64][64];
const int dy[4] = {0, 1, -1, 0}; // 오른쪽, 아래, 위, 왼쪽
const int dx[4] = {1, 0, 0, -1};
bool visited[64][64];
queue<pair<int, int>> q;

void spin(int start_y, int start_x, int half_size, int move_dir) {
    for (int y = start_y; y < start_y + half_size; y++) {
        for (int x = start_x; x < start_x + half_size; x++) {
            int ny = y + dy[move_dir] * half_size;
            int nx = x + dx[move_dir] * half_size;
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

    // 격자를 box_size 단위로 나누어 각 부분을 회전
    for (int i = 0; i < grid_size; i += box_size) {
        for (int j = 0; j < grid_size; j += box_size) {
			// 각 box를 4개의 사분면으로 나누어 시계방향으로 회전
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

    // 각 칸에 대해 인접한 얼음 개수를 세고 녹일지 결정
    for (int y = 0; y < grid_size; y++) {
        for (int x = 0; x < grid_size; x++) {
            int cnt = 0;
			// 상하좌우 4방향 탐색
            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
				// 격자 범위 내이고 얼음이 있으면 카운트
                if (nx >= 0 && nx < grid_size && ny >= 0 && ny < grid_size && a[ny][nx]) cnt++;
            }
			// 현재 칸에 얼음이 있고 인접한 얼음이 3개 미만이면 1 감소
            if(a[y][x] && cnt < 3) na[y][x] = a[y][x] - 1;
			// 그렇지 않으면 유지
            else na[y][x] = a[y][x];
        }
    }

    // melt 이후의 결과를 a로 복사
    for(int i = 0; i < grid_size; i++)
        for(int j = 0; j < grid_size; j++)
            a[i][j] = na[i][j];
}

int bfs() {
    int group = 0; // 군집의 크기를 저장할 group
    while (q.size()) {
        auto [y, x] = q.front();
        group++; // 현재 칸 카운트
		q.pop();
		// 상하좌우 4방향 탐색
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
			// 격자 범위 내이고, 방문하지 않았으며, 얼음이 있으면 큐에 추가
            if (nx >= 0 && nx < grid_size && ny >= 0 && ny < grid_size && !visited[ny][nx] && a[ny][nx]) {
                visited[ny][nx] = 1; q.push({ny, nx});
            }
        }
    }
    return group;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    cin >> n >> qq;
    grid_size = (1 << n); // 격자 크기 = 2^n
	for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            cin >> a[i][j]; // 초기 얼음의 양
        }
    }

    while(qq--) { // 회전 횟수만큼 반복
        cin >> level;
        if (level) move(level); // level이 0이 아니면 회전 수행
        melt(); // 얼음 녹이기
    }
    
    // 남아있는 얼음의 총합 계산
    int remain = 0;
    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
            remain += a[i][j];
        }
    }
    cout << remain << "\n";

    // 가장 큰 얼음 군집의 크기 계산
    int mx = 0;
    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
			// 얼음이 있고 방문하지 않은 칸이면 새로운 군집 탐색 시작
            if(a[i][j] && !visited[i][j]) {
                visited[i][j] = true;
                q.push({i, j});
                mx = max(mx, bfs()); // 현재 군집 크기와 최댓값 비교
            }
        }
    }
    cout << mx << "\n";
}