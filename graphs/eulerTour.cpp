#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
using ii = pair<int,int>;
const int N = 2e5+5;
int n,m,deg[N],used[N];
vector<int> tour;
stack<int> s;
vector<ii> g[N];
int main() {
  cin>>n>>m;
  for (int i=0;i<m;i++) {
    int u,v;
    cin>>u>>v;
    g[u].push_back({v,i});
    g[v].push_back({u,i});
    deg[u]++; deg[v]++;
  }
  for (int i=1;i<=n;i++) if (deg[i]%2) {
    cout<<"IMPOSSIBLE\n";
    return 0;
  }
  s.push(1);
  while (!s.empty()) {
    int u = s.top();
    if (deg[u]) {
      while (!g[u].empty()) {
        int v = g[u].back().F;
        int id = g[u].back().S;
        g[u].pop_back();
        if (!used[id]) {
          deg[u]--;
          deg[v]--;
          used[id] = 1;
          s.push(v);
          break;
        }
      }
    } else {
      tour.push_back(u);
      s.pop();
    }
  }
  if (tour.size() != m+1) {
    cout<<"IMPOSSIBLE\n";
  } else {
    for (int i : tour) cout<<i<<" ";
    cout<<"\n";
  }
}