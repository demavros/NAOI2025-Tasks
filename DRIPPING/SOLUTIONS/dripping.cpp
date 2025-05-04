#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
 
tuple<char, ll, ll> prisonier(ll W, vector<ll> notebook) {
    if(notebook.size()) {
        return tuple<char, ll, ll>{'a', W, 0};
    }
    return tuple<char, ll, ll>{'w', W+1, W};
}
