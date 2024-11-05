#define vi vector<int>

vi dad, dep, heavy, head, pos;
int cur_pos;

int dfs(int v, vector<vi> const& adj) {
  int size = 1;
  int max_c_size = 0;
  for (int c : adj[v]) {
    if (c != dad[v]) {
      dad[c] = v, dep[c] = dep[v] + 1;
      int c_size = dfs(c, adj);
      size += c_size;
      if (c_size > max_c_size)
        max_c_size = c_size, heavy[v] = c;
    }
  }
  return size;
}
void decompose(int v,int h,vector<vi> &adj) {
  head[v] = h, pos[v] = cur_pos++;
  if (heavy[v] != -1)
    decompose(heavy[v], h, adj);
  for (int c : adj[v]) {
    if (c != dad[v] && c != heavy[v])
      decompose(c, c, adj);
  }
}
void init(vector<vi> const& adj) {
  int n = adj.size();
  dad = vector<int>(n);
  dep = vector<int>(n);
  heavy = vector<int>(n, -1);
  head = vector<int>(n);
  pos = vector<int>(n);
  vect = vll(n);
  cur_pos = 0;

  dfs(0, adj);
  decompose(0, 0, adj);
}
// Set for sum querys using seg tree
ll query(int a, int b, SegTree &st) {
  ll res = 0;
  for (
    ; head[a] != head[b]; b = dad[head[b]]
  ) {
    if (dep[head[a]] > dep[head[b]])
      swap(a, b);
    res += st.query(pos[head[b]], pos[b]);
  }
  if (dep[a] > dep[b])
    swap(a, b);
  res += st.query(pos[a], pos[b]);;
  return res;
}