#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define vec vector
const int N = 1000;
const int K = 7;

// calc[i][j] stores the # of steps to get 
// all cows distance j away to door i
// to make implementing a cyclic array easier
// we double the size
vec<vec<ll>> calc(2 * N, vec<ll>(N + 1, 0));

//answer for doors 0,1,.., j and i doors open
vec<vec<ll>> dp(K+1,vec<ll>(N+1, INT64_MAX));

int rot;

void compdp(
  int k, int begin, int end, int rl, int rr
  ) {
// fixed k,begin end are the ends of the arr
// rl rr are the bounds on the last door used
  int mid = (begin + end) / 2;

  ll best = INT64_MAX;
  int best_last = -1;
  // best is min amount moved
  // last is the last door used
  for (int last=rl;last<=min(mid, rr);last++){
    ll cost = 
      dp[k-1][last-1]+
      calc[last+rot][mid-last+1];
    if (cost < best) {
      best = cost;
      best_last = last;
    } else if (cost==best&& last<best_last){
      best_last = last;
    }
  }
  dp[k][mid] = best;
  if (begin == end) { return; }
  compdp(k, begin, mid, rl, best_last);
  compdp(k, mid + 1, end, best_last, rr);
}

int main() {
  freopen("cbarn.in", "r", stdin);
  int n, k;
  cin >> n >> k;

  vec<int> a(2 * n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= n; j++) {
      calc[i][j] = calc[i + n][j] =
        calc[i][j-1] + (ll)a[i+j-1]*(j-1);
    }
  }

  // rotate stores where we start
  //  in linear representation
  ll ans = INT64_MAX;
  for (rot = 0; rot < n; rot++) {
    for (int i = 0; i < n; i++) { 
      dp[0][i] = calc[rot][i + 1]; 
    }
    for (int i = 1; i < k; i++) {
      for (int j = 0; j < n; j++) { 
        dp[i][j] = INT64_MAX; 
      }
      compdp(i, i, n - 1, i, n - 1);
    }
    ans = min(ans, dp[k - 1][n - 1]);
  }

  freopen("cbarn.out", "w", stdout);
  cout << ans << endl;
}