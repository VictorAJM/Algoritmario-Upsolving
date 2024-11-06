#define vi vector<int>
int dfs_st(
  vector<vi> &ady, vi &s,
  vector<bool> &v, int n
){
  v[n] = 1, s[n] = 1;
  for(auto nx: ady[n]) if(!v[nx])
    s[n] += dfs_st(ady, s, v, nx);
  return s[n];
}
vi get_centroids(
  vector<vi> &ady
){
  int n = 0;
  int sz = ady.size();
  vi subt(ady.size()), c;
  vector<bool> vis(ady.size(), 0);
  dfs_st(ady, subt, vis, 0);
  vis.assign(ady.size(), 0);
  bool is_c = 0;
  while(!is_c){
    is_c = 1;
    vis[n] = 1;
    for(auto nx: ady[n]){
      if(!vis[nx] && subt[nx] > sz/2){
        is_c = 0;
        n = nx;
        break;
      }
    }
  }
  c.push_back(n);
  for(int nd: ady[n]){
    if(sz - subt[nd] == sz/2)c.push_back(nd);
  }
  return c;
}