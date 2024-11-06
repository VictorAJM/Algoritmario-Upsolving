#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
string tour;
int n;
stack<int> s;
vector<int> g[N];
int main() {
  cin>>n;
  if (n==1) {
    cout<<"01\n";
    return 0;
  }
  for (int i=0;i<(1<<(n-1));i++) {
    g[i].push_back((i*2)%(1<<(n-1)));
    g[i].push_back((i*2+1)%(1<<(n-1)));
  }
  s.push(0);
  while (!s.empty()) {
    int u = s.top();
    if (!g[u].empty()) {
      int v = g[u].back();
      g[u].pop_back();
      s.push(v);
    } else {
      tour.push_back(u%2+'0');
      s.pop();
    }
  }
  for (int i=0;i<n-2;i++) 
    tour.push_back('0');
  for (char u : tour) cout<<u;
}