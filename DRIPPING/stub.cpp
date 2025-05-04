#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <tuple>
#include <cmath>

typedef long long ll;
using namespace std;

tuple<char, ll, ll> prisonier(ll W, vector<ll> notebook);

signed main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);

    auto fifo_in = ifstream(argv[1]);
    auto fifo_out = ofstream(argv[2]);

    int n;
    fifo_in >> n;

    fflush(stdout);
    vector<vector<ll>> notebooks(n);

    // in/out
    ll C = 0;
    ll M = 0;
    ll W = 0;
    ll ANS;
    ll MAXI = 0;
    for (int i = 0; i < n; i = (i + 1) % n)
    {
        MAXI += 1;
        C += 1;
        

        char x;
        ll y;
        ll z;

        auto U = prisonier(W, notebooks[i]);
        x = get<0>(U);
        y = get<1>(U);
        z = get<2>(U);
        
        
        notebooks[i].push_back(z);
        if (x == 'w')
        {
            W = y;
            M = max(M, abs(W));
        }
        else
        {
            ANS = y;
            break;
        }
    }

    if (ANS == n)
    {
        C = (C + n - 1) / n;
        double U = (double)M * (double)M * (double)C;
        double score = 20.0 + 80.0 * pow(1.02, -sqrt(max(0.0, U - 40.0)));
        int S = score * 100;
        fifo_out << S / 10000 << '.' << S % 10000 << '\n';
    }
    else
    {
        fifo_out << "0.0\n";
    }

    return 0;
}