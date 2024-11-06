#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
vector<int> g[N];
int vs[N],low[N],high[N];
stack<int> st;
bool onStack[N];
int scc[N],cnt,cnt2;
void dfs(int u) {
  vs[u]=1;
  cnt++;
  low[u]=high[u]=cnt;
  st.push(u);
  onStack[u]=true;
  for (int v : g[u]) {
    if (vs[v]==0) {
      dfs(v);
      low[u]=min(low[u],low[v]);
    } else if (onStack[v]) {
      low[u]=min(low[u],high[v]);
    } 
  }
  if (low[u]==high[u]) {
    ++cnt2;
    while (st.top()!=u) {
      onStack[st.top()]=false;
      scc[st.top()]=cnt2;
      st.pop();
    }
    onStack[st.top()]=false;
    scc[st.top()]=cnt2;
    st.pop();
  }
}
int main() {
  cin>>n>>m;
  for (int i=1;i<=m;i++) {
    int u,v;
    cin>>u>>v;
    g[u].push_back(v);
  }
  for (int i=1;i<=n;i++) 
    if (vs[i]==0) dfs(i);
  cout<<cnt2<<"\n";
  for (int i=1;i<=n;i++) cout<<scc[i]<<" ";
}