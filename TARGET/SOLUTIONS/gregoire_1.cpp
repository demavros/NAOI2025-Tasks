#include <bits/stdc++.h>
using namespace std;
 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    long long n; 
    cin >> n;
    // For each disc we store an array "pref" of length 11
    // where pref[i][d] = sum of counts for digits 0...d-1 on disc i.
    vector<vector<long long>> pref(n, vector<long long>(11,0));
    vector<long long> totalDigits(n,0), half(n,0);
    for(long long i = 0; i < n; i++){
        long long sum = 0;
        vector<long long> a(10);
        for (long long d = 0; d < 10; d++){
            cin >> a[d];
            sum += a[d];
        }
        totalDigits[i] = sum;
        half[i] = sum / 2;
        pref[i][0] = 0;
        for (long long d = 0; d < 10; d++){
            pref[i][d+1] = pref[i][d] + a[d];
        }
    }
 
    long long q;
    cin >> q;
    // Each query is a target string of length 2*n.
    // According to the problem statement and sample:
    //   - The left half (first n characters) corresponds to the left digits of discs, but in reverse order:
    //         disc n gets the 1st char, disc n-1 gets the 2nd, …, disc 1 gets the nth.
    //   - The right half (last n characters) corresponds to the right digits of discs in order:
    //         disc 1 gets char n+1, disc 2 gets char n+2, …, disc n gets char 2*n.
    for (long long qi = 0; qi < q; qi++){
        string s;
        cin >> s;
        long long totalCost = 0;
        bool poss = true;
        // Process each disc i (0-indexed means disc 1,2,...,n)
        for (long long i = 0; i < n; i++){
            // For disc (i+1):
            // right target digit = s[n + i] and
            // left target digit  = s[n - 1 - i]   (reverse order for left half)
            long long digR = s[n + i] - '0';
            long long digL = s[n - 1 - i] - '0';
 
            long long M = totalDigits[i]; // total digits on disc i
            long long Lm = half[i];       // = M/2
 
            long long best = LLONG_MAX;
 
            // Case 1: r in [0, Lm)
            // We need r in I(R) and also r in [ pref[digL] - Lm, pref[digL+1]-1 - Lm ]
            long long lowR = pref[i][digR];
            long long highR = pref[i][digR+1] - 1;
            long long lowL = pref[i][digL] - Lm;
            long long highL = pref[i][digL+1] - 1 - Lm;
            long long lo1 = max({lowR, lowL, 0LL});
            long long hi1 = min({highR, highL, Lm - 1});
            if(lo1 <= hi1)
                best = min(best, lo1); // cost = r (which is minimized by the smallest candidate)
 
            // Case 2: r in [Lm, M)
            // Write r = Lm + r'. Then we require:
            //   r in I(R) ∩ [Lm, M-1] and r' in I(L), i.e., r in [Lm + pref[digL], Lm + pref[digL+1]-1].
            long long lo2 = max({ (long long)pref[i][digR], Lm, Lm + (long long)pref[i][digL] });
            long long hi2 = min({ (long long)pref[i][digR+1] - 1, M - 1, Lm + (long long)pref[i][digL+1] - 1 });
            if(lo2 <= hi2)
                best = min(best, M - hi2); // cost = M - r (minimized when r is as large as possible)
 
            if(best == LLONG_MAX){
                poss = false;
                break;
            }
            totalCost += best;
        }
 
        if(!poss){
            cout << "IMPOSSIBLE\n-1\n";
        } else {
            cout << "POSSIBLE\n" << totalCost << "\n";
        }
    }
    return 0;
}
