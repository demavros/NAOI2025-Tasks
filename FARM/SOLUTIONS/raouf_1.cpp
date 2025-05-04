#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll compute(ll x, ll y, ll a, ll b)
{
    if (x < y)
    {
        swap(x, y);
        swap(a, b);
    }       

    ll q = x / y;
    ll r = x % y;

    if (a < y * q)
    {
        return a / y;
    }

    return q + compute(y, r, b, a - y * q);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, M, Q;
    cin >> N >> M >> Q;

    map<ll, ll> hi;
    multiset<ll> values;
    
    while(Q--){
        char c;
        cin >> c;
        if(c == 'c') cout << *(--values.end()) << '\n';
        else{
            ll x,y;
            cin >> x >> y;
            ll h = compute(N,M,x,y);
            if (values.count(hi[h]))
                values.erase(values.find(hi[h]));
            hi[h] += c == 'a' ? 1 : -1;
            values.insert(hi[h]);
        }
    }
}