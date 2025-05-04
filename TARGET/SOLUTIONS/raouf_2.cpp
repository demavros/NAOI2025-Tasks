#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define e(x) (x - '0')

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n; // Number of discs
    cin >> n;
    ll dnm = 2 * n - 1;

    vector<vector<ll>> discs(n, vector<ll>(11, 0)); // Grid prefix sum
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < 10; j++)
        {
            cin >> discs[i][j + 1];
            discs[i][j + 1] += discs[i][j];
        }

    }

    vector<vector<ll>> dp(n, vector<ll>(100, 0)); // Precomputation

    for (int i = 0; i < n; i++)
    {
        for (int X = 0; X < 10; X++)
        {
            for (int Y = 0; Y < 10; Y++)
            { // Y____X
                ll a = discs[n - 1 - i][X];
                ll b = discs[n - 1 - i][X + 1] - 1;
                if (b < a)
                {
                    dp[i][X * 10 + Y] = -1;
                    continue;
                }

                ll c = discs[n - 1 - i][Y];
                ll d = discs[n - 1 - i][Y + 1] - 1;

                if (d < c)
                {
                    dp[i][X * 10 + Y] = -1;
                    continue;
                }

                c += discs[n - 1 - i][10] >> 1;
                d += discs[n - 1 - i][10] >> 1;

                ll x = max(a, c);
                ll y = min(b, d);

                ll res = 3000000000000000000LL;
                bool w = true;

                if (x <= y)
                {
                    res = min(x, discs[n - 1 - i][10] - y);
                    w = false;
                }

                c -= discs[n - 1 - i][10];
                d -= discs[n - 1 - i][10];

                x = max(a, c);
                y = min(b, d);

                if (x <= y)
                {
                    res = min(x, min(res, discs[n - 1 - i][10] - y));
                    w = false;
                }

                if (w)
                {
                    dp[i][X * 10 + Y] = -1;
                    continue;
                }
                else
                {
                    dp[i][X * 10 + Y] = res;
                }
            }
        }
    }

    ll q; // Number of queries
    cin >> q;

    while (q--)
    {
        string S;
        cin >> S; // Get query string of length 2n
        ll ans = 0;
        for (ll i = 0; i < n; i++)
        {
            ll x = e(S[dnm - i]);
            ll y = e(S[i]);
            if (dp[i][x * 10 + y] == -1)
            {
                ans = -1;
                break;
            }
            ans += dp[i][x * 10 + y];
        }

        cout << (ans == -1 ? "IMPOSSIBLE" : "POSSIBLE") << '\n';
        cout << ans << '\n';
    }
}