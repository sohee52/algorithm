#include <bits/stdc++.h>
using namespace std;

int n, k;
int s[205];        // 내구도
bool p[205];       // 사람 위치
int turn = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= 2 * n; i++) cin >> s[i];

    while (true) {
        turn++;

        // 1) 벨트 회전
        int last_s = s[2 * n];
        for (int i = 2 * n; i >= 2; i--) s[i] = s[i - 1];
        s[1] = last_s;

        for (int i = n; i >= 2; i--) p[i] = p[i - 1];
        p[1] = false;        // 1번 위치엔 새로 올 사람만
        p[n] = false;        // n번 위치 도착 시 내려감

        // 2) 사람 이동 (n-1 -> 1 순서로)
        for (int i = n - 1; i >= 1; i--) {
            if (p[i] && !p[i + 1] && s[i + 1] > 0) {
                p[i] = false;
                p[i + 1] = true;
                s[i + 1]--;
            }
        }
        p[n] = false; // 내리는 위치에 도달한 사람은 내림

        // 3) 올리는 위치(1번)에 사람 올리기
        if (!p[1] && s[1] > 0) {
            p[1] = true;
            s[1]--;
        }

        // 4) 내구도 0인 칸 개수 체크
        int cnt = 0;
        for (int i = 1; i <= 2 * n; i++) {
            if (s[i] == 0) cnt++;
        }

        if (cnt >= k) break;
    }

    cout << turn << "\n";
}
