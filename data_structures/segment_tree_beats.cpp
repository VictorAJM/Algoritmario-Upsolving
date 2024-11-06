// Segment tree to support this querys:
//  upd_set(i, x) -> set a[i]=x
//  upd_mod(l, r, x) -> for all i between
//    [l,r], set a[i] = a[i]%x
//  querry(l, r) -> get sum in [l, r]
int n;
const int MAXN = 100001;
long long tsum[MAXN * 4], tmax[MAXN * 4];
void update_mod(int l,int r,long long v,
int t=1,int tl=0,int tr=n-1) {
  if (r < tl || tr < l || tmax[t] < v)
    return;
  else if (tl == tr) {
    int val = tmax[t] % v;
    tsum[t] = tmax[t] = val;
    return;
  }
  int tm = (tl + tr) / 2;
  update_mod(l, r, v, t * 2, tl, tm);
  update_mod(l, r, v, t * 2 + 1, tm + 1, tr);
  tsum[t] = tsum[t * 2] + tsum[t * 2 + 1];
  tmax[t] = max(tmax[t * 2],tmax[t * 2 + 1]);
}
void update_set(int i,long long v,int t = 1,
int tl = 0, int tr = n-1) {
  if (tl == tr) {
    tsum[t] = tmax[t] = v;
    return;
  }
  int tm = (tl + tr) / 2;
  if (i <= tm) 
    update_set(i, v, t * 2, tl, tm);
  else
    update_set(i, v, t * 2 + 1, tm + 1, tr);
  tsum[t] = tsum[t * 2] + tsum[t * 2 + 1];
  tmax[t] = max(tmax[t * 2],tmax[t * 2 + 1]);
}
long long query(int l, int r, int t = 1,
int tl = 0 , int tr = n-1) {
  if (r < tl || tr < l)
    return 0;
  else if (l <= tl && tr <= r)
    return tsum[t];
  int tm = (tl + tr) / 2;
  return query(l, r, t * 2, tl, tm) +
  query(l, r, t * 2 + 1, tm + 1, tr);
}