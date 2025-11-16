#include <bits/stdc++.h>
using namespace std;

int n, m, k;

// (m, s, d)
vector<tuple<int, int, int>> a[50][50]; // 현재 상태
vector<tuple<int, int, int>> na[50][50]; // 다음 상태

pair<int,int> move(int x, int y, int s, int d) {
    int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

		// + n → 음수 방지, % n → 맵 크기만큼 순환
    int nx = (x + (dx[d] * s % n) + n) % n;
    int ny = (y + (dy[d] * s % n) + n) % n;
    return {nx, ny};
}

void split(int x, int y) {
    int mass_sum = 0;
    int velocity_sum = 0;
    int dir[2] = {0, 0}; // 0번째는 상하좌우, 1번째는 대각선

    int cnt = na[x][y].size();

    for (int i = 0; i < cnt; i++) {
        auto [m, s, d] = na[x][y][i];
        mass_sum += m;
        velocity_sum += s;
        dir[d % 2]++;
    }

    // 조건에 맞게 새로운 질량과 속력 정의
    int new_m = mass_sum / 5;
    int new_s = velocity_sum / cnt;

    // 질량 0이면 소멸
    if (new_m == 0) return;

    // 방향을 상하좌우로 할 것인지, 대각선으로 할 것인지 결정하는 start
    // 모두 상하좌우 또는 모두 대각선 -> 상하좌우
    // 상하좌우와 대각선이 섞여있으면 -> 대각선
    int start;
    if (dir[0] == 0 || dir[1] == 0) start = 0;
    else start = 1;

    for (int d = start; d < 8; d += 2) {
        a[x][y].push_back({new_m, new_s, d});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k; // 격자의 크기, 원자의 개수, 실험 시간

    for (int i = 0; i < m; i++) {
        int x, y, mm, s, d; // 위치 x, 위치 y, 질량, 속력, 방향
        cin >> x >> y >> mm >> s >> d;
        a[x-1][y-1].push_back({mm, s, d}); // 0-based로 바꾸기
    }

    while (k--) {

        // na 초기화
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                na[i][j].clear();

        // 이동 -> na에 넣기
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                for (auto &[m, s, d] : a[x][y]) {
                    auto [nx, ny] = move(x, y, s, d);
                    na[nx][ny].push_back({m, s, d});
                }
            }
        }

        // a 초기화
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j].clear();

        // 합치기 + 나누기 -> a에 넣기
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = na[i][j].size();
                if (cnt == 1) a[i][j].push_back(na[i][j][0]);
                else if (cnt > 1) split(i, j);
            }
        }
    }

    // 결과 합산
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (auto &[m, s, d] : a[i][j])
                ans += m;

    cout << ans;
    return 0;
}
