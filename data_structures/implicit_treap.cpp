// Implicit treap
// Comented code if for range reverse, range
// querrys and lazy prop
typedef struct node *pnode;
struct node {
int pr,cnt,val;
// int sum; // (paramters for range query)
// bool rev;int add; //(params for lazy prop)
  pnode l,r;
  node(int val):
  pr(rand()),cnt(1),val(val),l(0),r(0)
  //,sum(val),rev(0),add(0)
  {}
  };
void push(pnode it){
  if(it){
    /*if(it->rev){
      swap(it->l,it->r);
      if(it->l)it->l->rev^=true;
      if(it->r)it->r->rev^=true;
      it->rev=false;
    }
    it->val+=it->add;it->sum+=it->cnt*it->add;
    if(it->l)it->l->add+=it->add;
    if(it->r)it->r->add+=it->add;
    it->add=0;*/
  }
}
int cnt(pnode t){return t?t->cnt:0;}
//int sum(pitem t){return t?push(t),t->sum:0;}
void upd_cnt(pnode t){
  if(t){
    t->cnt=cnt(t->l)+cnt(t->r)+1;
    // t->sum=t->val+sum(t->l)+sum(t->r);
  }
}
void merge(pnode& t, pnode l, pnode r){
  push(l);push(r);
  if(!l||!r)t=l?l:r;
  else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
  else merge(r->l,l,r->l),t=r;
  upd_cnt(t);
}
void split(pnode t,pnode& l,pnode& r,int k){
  if(!t){l=r=0;return;}
  push(t);
  if(k<=cnt(t->l))split(t->l,l,t->l,k),r=t;
  else split(t->r,t->r,r,k-1-cnt(t->l)),l=t;
  upd_cnt(t);
}
void output(pnode t){
  if(!t)return;
  push(t);
  output(t->l);
  cout << t->val;
  output(t->r);
}