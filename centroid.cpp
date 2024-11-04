#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
vector<int> g[MAXN];int n;
bool tk[MAXN];
int fat[MAXN]; // father in centroid decomp
int szt[MAXN]; // size of subtree

int calcsz(int x, int f){
  szt[x]=1;
  for(auto y:g[x])
    if(y!=f && !tk[y]) szt[x]+=calcsz(y,x);
  return szt[x];
}
// O(nlogn), X is the beginning
void cdfs(int x=1, int f=-1, int sz=-1){ 
  if(sz<0)
    sz=calcsz(x,-1);
  for(auto y:g[x])
    if(!tk[y] && szt[y]*2 >= sz){
      szt[x]=0;
      cdfs(y,f,sz);
      return;
    }
  tk[x]=true; fat[x]=f;
  for(auto y:g[x])
    if(!tk[y]) cdfs(y,x);
}

void centroid(){
  memset(tk,false,sizeof(tk));cdfs();
  // return fat
}
