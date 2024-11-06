// BST Implementation (Treap)
#define f first
#define s second
typedef struct node *pnode;
struct node {
  int pr,key,cnt;
  pnode l,r;
  node(int key):
  key(key),pr(rand()),cnt(1),l(0),r(0) {}
};
int cnt(pnode t){return t?t->cnt:0;}
void upd_cnt(pnode t){
if(t)t->cnt=cnt(t->l)+cnt(t->r)+1;  
}
// l: < key, r: >= key
void split(pnode t,int key,pnode& l,pnode& r){
  if(!t)
    l=r=0;
  else if(key<t->key)
    split(t->l,key,l,t->l),r=t;
  else
  split(t->r,key,t->r,r),l=t;
  upd_cnt(t);
}
void insert(pnode& t, pnode it){
  if(!t)
    t=it;
  else if(it->pr>t->pr)
    split(t,it->key,it->l,it->r),t=it;
  else
    insert(it->key<t->key?t->l:t->r,it);
  upd_cnt(t);
}
void merge(pnode& t, pnode l, pnode r){
  if(!l||!r)t=l?l:r;
  else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
  else merge(r->l,l,r->l),t=r;
  upd_cnt(t);
}
void erase(pnode& t, int key){
  if(t->key==key)merge(t,t->l,t->r);
  else erase(key<t->key?t->l:t->r,key);
  upd_cnt(t);
}
// Union of 2 diff treaps
void unite(pnode &t, pnode l, pnode r){
  if(!l||!r){t=l?l:r;return;}
  if(l->pr<r->pr)swap(l,r);
  pnode p1,p2;split(r,l->key,p1,p2);
  unite(l->l,l->l,p1);unite(l->r,l->r,p2);
  t=l;upd_cnt(t);
}
// K-th largest node by value
pnode kth(pnode t, int k){
  if(!t)return 0;
  if(k==cnt(t->l))return t;
  return k<cnt(t->l)?
    kth(t->l,k):
    kth(t->r,k-cnt(t->l)-1);
}
// position and value of lower_bound
pair<int,int> lb(pnode t, int key){
  if(!t)return {0,1<<30}; // (special value)
  if(key>t->key){
    auto w=lb(t->r,key);
    w.f+=cnt(t->l)+1;
    return w;
  }
  auto w=lb(t->l,key);
  if(w.f==cnt(t->l))w.s=t->key;
  return w;
}