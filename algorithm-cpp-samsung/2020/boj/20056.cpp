#include <bits/stdc++.h>
using namespace std;
int n, m, k, y, x, mm, s, d, ny, nx, ans;
vector<tuple<int, int, int>> a[50][50], na[50][50];
pair<int, int> move (int y, int x, int s, int d) {
    int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    int ny = (y + (dy[d] * s) % n + n) %n;
    int nx = (x + (dx[d] * s) % n + n) %n;

    return {ny, nx};
}

void split(int y, int x) {
    int mass_sum = 0;
    int velocity_sum = 0;
    int dir[2] = {0, 0};

    int cnt = na[y][x].size();
    for (int i = 0; i < cnt; i++) {
        auto [m, s, d] = na[y][x][i];
        mass_sum += m;
        velocity_sum += s;
        dir[d % 2]++;
    }

    int new_m = mass_sum/5;
    int new_s = velocity_sum/cnt;

    if (new_m == 0) return;

    int start = 0;
    if (dir[0] == 0 || dir[1] == 0) start = 0;
    else start = 1;

    for (int d = start; d < 8; d += 2) {
        a[y][x].push_back({new_m, new_s, d});
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        cin >> y >> x >> mm >> s >> d;
        a[y-1][x-1].push_back({mm, s, d});
    }

    while (k--) {
        // 이동 -> na에 저장
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                for (auto &[m, s, d] : a[y][x]) {
                    auto [ny, nx] = move(y, x, s, d);
                    na[ny][nx].push_back({m, s, d});
                }
            }
        }

        // a 초기화
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j].clear();
            }
        }

        // 합치기 + 나누기 -> a에 넣기
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                int cnt = na[y][x].size();
                if (cnt == 1) a[y][x].push_back(na[y][x][0]);
                else if (cnt >= 2) split(y, x);
            }
        }

        // na 초기화
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                na[i][j].clear();
            }
        }
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            for (auto &[m, s, d] : a[y][x]) {
                ans += m;
            }
        }
    }
    cout << ans << "\n";
}
