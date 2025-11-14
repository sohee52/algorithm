#include <bits/stdc++.h>
using namespace std;

int n, m, k;

// (m, s, d)
vector<tuple<int, int, int>> a[50][50];
vector<tuple<int, int, int>> na[50][50];

pair<int,int> move(int x, int y, int s, int d) {
    int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    int nx = (x + dx[d] * s % n + n) % n;
    int ny = (y + dy[d] * s % n + n) % n;
    return {nx, ny};
}

void split(int x, int y) {
    int mass_sum = 0;
    int velocity_sum = 0;
    int dir_type[2] = {0,0};

    int cnt = na[x][y].size();

    for (int i = 0; i < cnt; i++) {
        auto [m, s, d] = na[x][y][i];
        mass_sum += m;
        velocity_sum += s;
        dir_type[d % 2]++;
    }

    int new_m = mass_sum / 5;
    int new_s = velocity_sum / cnt;

    // 질량 0이면 소멸
    if (new_m == 0) return;

    int start_dir;
    if (dir_type[0] == 0 || dir_type[1] == 0)
        start_dir = 0;
    else
        start_dir = 1;

    for (int d = start_dir; d < 8; d += 2) {
        a[x][y].push_back({new_m, new_s, d});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int x, y, mm, s, d;
        cin >> x >> y >> mm >> s >> d;
        a[x-1][y-1].push_back({mm, s, d});
    }

    while (k--) {

        // na 배열 초기화
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                na[i][j].clear();

        // 1) 이동
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                for (auto &[m, s, d] : a[x][y]) {
                    auto [nx, ny] = move(x, y, s, d);
                    na[nx][ny].push_back({m, s, d});
                }
            }
        }

        // 2) a 초기화
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j].clear();

        // 3) 합치기 + 나누기
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
