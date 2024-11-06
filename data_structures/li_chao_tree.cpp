// Supports line inserts on a range
// and querrys for the max value at some
// point [not tested but should work .-.]
template<typename data_t>
struct Line {
  data_t a, b;
  Line() : a(0), b(-inf) {}
  Line(data_t a, data_t b) : a(a), b(b) {}
  data_t get(data_t x) {
    return a * x + b;
  }
};
struct Node {
  Line<data_t> line = Line<data_t>();
  Node *lc = nullptr;
  Node *rc = nullptr;
};
void InsertLineKnowingly(
  Node* &n,data_t tl,data_t tr,Line<data_t> x
) {
  if (n == nullptr) n = new Node();
  if (n->line.get(tl) < x.get(tl))
    swap(n->line, x);
  if (n->line.get(tr) >= x.get(tr)) return;
  if (tl == tr) return;
  data_t mid = (tl + tr) / 2;
  if (n->line.get(mid) > x.get(mid))
  InsertLineKnowingly(n->rc, mid + 1, tr, x);
  else {
    swap(n->line, x);
    InsertLineKnowingly(n->lc, tl, mid, x);
  }
}
void InsertLine(Node* &n, data_t tl,
data_t tr, data_t l, data_t r,
Line<data_t> x) {
  if (tr < l || r < tl || tl > tr || l > r)
    return;
  if (n == nullptr) n = new Node();
  if (l <= tl && tr <= r)
    return InsertLineKnowingly(n, tl, tr, x);
  data_t mid = (tl + tr) / 2;
  InsertLine(n->lc, tl, mid, l, r, x);
  InsertLine(n->rc, mid + 1, tr, l, r, x);
}
data_t Query(Node* &n, data_t tl,
data_t tr, data_t x) {
  if (n == nullptr) return -inf;
  if (tl == tr) return n->line.get(x);
  data_t res = n->line.get(x);
  data_t mid = (tl + tr) / 2;
  if (x <= mid)
    res = max(res, Query(n->lc, tl, mid, x));
  else
  res=max(res, Query(n->rc, mid + 1, tr, x));
  return res;
}
void InsertLine(data_t l, data_t r,
Line<data_t> x) {
  return InsertLine(root, 0, sz - 1, l, r, x);
}
data_t Query(data_t x) {
  return Query(root, 0, sz - 1, x);
}