#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    string s1;
    cin >> s1;
    string s2;
    if (n == 1) {
        s2 = string(m, '#');
    } else {
        cin >> s2;
    }

    vector<vector<ll>> dp(m + 1, vector<ll>(16, 0));
    dp[0][0b1111] = 1;
    char cache[2][3];
    auto right = [&]() {
        return (cache[0][1] == '#') + (cache[0][2] == '#') * 2 +
               (cache[1][1] == '#') * 4 + (cache[1][2] == '#') * 8;
    };


    for (int i = 1; i <= m; i++) {
        for (int start = 0; start <= 0b1111; ++start) {
            cache[0][0] = start % 2 ? '#' : '.';
            cache[0][1] = (start >> 1) % 2 ? '#' : '.';
            cache[1][0] = (start >> 2) % 2 ? '#' : '.';
            cache[1][1] = (start >> 3) % 2 ? '#' : '.';
            cache[0][2] = s1[i - 1];
            cache[1][2] = s2[i - 1];

            if (cache[0][0] + cache[0][1] != int('.') * 2 and
                cache[0][0] + cache[1][0] != int('.') * 2 and
                cache[1][1] + cache[1][0] != int('.') * 2) {
                dp[i][right()] += dp[i - 1][start];
                dp[i][right()] %= MOD;  
            }

            if (cache[0][2] == '.' and cache[1][2] == '.') {
                cache[0][2] = cache[1][2] = '#';
                if (cache[0][0] + cache[0][1] != int('.') * 2 and
                    cache[0][0] + cache[1][0] != int('.') * 2 and
                    cache[1][1] + cache[1][0] != int('.') * 2) {
                    dp[i][right()] += dp[i - 1][start];
                    dp[i][right()] %= MOD;
                }
                cache[0][2] = cache[1][2] = '.';
            }

            if (cache[0][2] == '.' and cache[0][1] == '.') {
                cache[0][2] = cache[0][1] = '#';
                if (cache[0][0] + cache[0][1] != int('.') * 2 and
                    cache[0][0] + cache[1][0] != int('.') * 2 and
                    cache[1][1] + cache[1][0] != int('.') * 2) {
                    dp[i][right()] += dp[i - 1][start];
                    dp[i][right()] %= MOD;
                }
                cache[0][2] = cache[0][1] = '.';
            }

            if (cache[1][1] == '.' and cache[1][2] == '.') {
                cache[1][1] = cache[1][2] = '#';
                if (cache[0][0] + cache[0][1] != int('.') * 2 and
                    cache[0][0] + cache[1][0] != int('.') * 2 and
                    cache[1][1] + cache[1][0] != int('.') * 2) {
                    dp[i][right()] += dp[i - 1][start];
                    dp[i][right()] %= MOD;
                }
                cache[1][1] = cache[1][2] = '.';
            }


            if (right() == 0) {
                cache[0][2] = cache[0][1] = '#';
                cache[1][2] = cache[1][1] = '#';
                if (cache[0][0] + cache[0][1] != int('.') * 2 and
                    cache[0][0] + cache[1][0] != int('.') * 2 and
                    cache[1][1] + cache[1][0] != int('.') * 2) {
                    dp[i][right()] += dp[i - 1][start];
                }
                cache[0][2] = cache[0][1] = '.';
                cache[1][2] = cache[1][1] = '.';
            }

        }
    }

    cout << (dp[m][0b0110] + dp[m][0b1001] + dp[m][0b0111] + dp[m][0b1011] +
                dp[m][0b1101] + dp[m][0b1110] + dp[m][0b1111])%MOD
         << '\n';
}