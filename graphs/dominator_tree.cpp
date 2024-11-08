// idom[i]=parent of i in dominator tree
//  with root=rt, or -1 if not exists
// Use the global variable for n
//  g is the adj list
// Call dominators(rt) with rt being the node
//  index that will be the root to gen idom
#define SZ(a) (int)a.size()
const int MAXN = 2e5+5;
int n,rnk[MAXN],pre[MAXN],anc[MAXN],
idom[MAXN],semi[MAXN],low[MAXN];
vector<int> g[MAXN],rev[MAXN],dom[MAXN],ord;
void dfspre(int pos){
  rnk[pos]=SZ(ord); ord.pb(pos);
  for(auto x:g[pos]){
    rev[x].pb(pos);
    if(rnk[x]==n) pre[x]=pos,dfspre(x);
  }
}
int eval(int v){
  if(anc[v]<n&&anc[anc[v]]<n){
    int x=eval(anc[v]);
    if(rnk[semi[low[v]]]>rnk[semi[x]])
      low[v]=x;
    anc[v]=anc[anc[v]];
  }
  return low[v];
}
void dominators(int rt){
  for(int i=0; i<n; i++){
    dom[i].clear(); rev[i].clear();
    rnk[i]=pre[i]=anc[i]=idom[i]=n;
    semi[i]=low[i]=i;
  }
  ord.clear(); dfspre(rt);
  for(int i=SZ(ord)-1;i;i--){
    int w=ord[i];
    for(int v:rev[w]){
      int u=eval(v);
      if(rnk[semi[w]]>rnk[semi[u]])
        semi[w]=semi[u];
    }
    dom[semi[w]].pb(w); anc[w]=pre[w];
    for(int v:dom[pre[w]]){
      int u=eval(v);
      idom[v]=(
        rnk[pre[w]]>rnk[semi[u]]?u:pre[w]
      );
    }
    dom[pre[w]].clear();
  }
  for(int w:ord) if(w!=rt&&idom[w]!=semi[w])
    idom[w]=idom[idom[w]];
  for(int i=0; i<n; i++) if(idom[i]==n)
    idom[i]=-1;
}
