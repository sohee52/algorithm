#include <bits/stdc++.h>
using namespace std;
int n, k, a[204], turn;
bool r[204];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> k;
    for (int i = 1; i <= 2*n; i++) {
        cin >> a[i];
    }

    while(true) {
        turn++;

        // 1. 벨트 회전
        int temp_a = a[2*n];
        bool temp_r = r[2*n];
        for (int i = 2*n; i >= 2; i--) {
            a[i] = a[i-1];
            r[i] = r[i-1];
        }
        a[1] = temp_a;
        r[1] = temp_r;
        
        // 회전 후 n 위치 로봇 내리기
        if (r[n]) r[n] = false;

        // 2. 로봇 이동 (n-1부터 1까지)
        for (int i = n-1; i >= 1; i--) {
            if (r[i] && !r[i+1] && a[i+1] > 0) {
                r[i+1] = true;
                r[i] = false;  // 원래 위치 비우기
                a[i+1]--;
            }
        }
        
        // 이동 후 n 위치 로봇 내리기
        if (r[n]) r[n] = false;

        // 3. 로봇 올리기
        if (a[1] > 0) {
            r[1] = true;
            a[1]--;
        }

        // 4. 종료 조건 체크
        int zero_cnt = 0;
        for (int i = 1; i <= 2*n; i++) {
            if (a[i] == 0) zero_cnt++;
        }
        if (zero_cnt >= k) break;
    }
    
    cout << turn << "\n";
}