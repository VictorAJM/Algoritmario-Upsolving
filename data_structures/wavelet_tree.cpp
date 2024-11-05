typedef vector<int>::iterator iter;
//Wavelet tree
struct Wavelet {
  vector<vector<int> > C; int s;
  // sigma = size of the alphabet
  // if A is passed by reference it will be
  // modified
  Wavelet(vector<int> &A, int sigma) :
  C(sigma*2), s(sigma) {
    build(A.begin(), A.end(), 0, s-1, 1);
  }
  void build(iter b,iter e,int L,int U,int u){
    if (L == U)
      return;
    int M = (L+U)/2;
    //C[u][i] number of zeros until i-1:[0,i)
    C[u].reserve(e-b+1); C[u].push_back(0);
    for (iter it = b; it != e; ++it)
      C[u].push_back(C[u].back() + (*it<=M));
    iter p = stable_partition(
      b, e, [=](int i){return i<=M;}
    );
    build(b, p, L, M, u*2);
    build(p, e, M+1, U, u*2+1);
  }
  // Count occurrences of c until position i.
  // ie, occurrences of c in positions [0,i]
  int rank(int c, int i) {
    i++;
    int L = 0, U = s-1, u = 1, M, r;
    while (L != U) {
      M = (L+U)/2;
      r = C[u][i]; u*=2;
      if (c <= M)
        i = r, U = M;
      else
        i -= r, L = M+1, ++u;
    }
    return i;
  }
  // k-th smallest element in positions [i,j]
  int quantile(int k, int i, int j) {
    j++;
    int L = 0, U = s-1, u = 1, M, ri, rj;
    while (L != U) {
      M = (L+U)/2;
      ri = C[u][i]; rj = C[u][j]; u*=2;
      if (k <= rj-ri)
        i = ri, j = rj, U = M;
      else
        k -= rj-ri, i -= ri, j -= rj,
          L = M+1, ++u;
    }
    return U;
  }
  //Number of occurrences of numbers in [a,b]
  //present in positions [i, j]
  mutable int L, U;
  int range(int i, int j, int a, int b) {
    if (b < a or j < i)
      return 0;
    L = a; U = b;
    return range(i, j+1, 0, s-1, 1);
  }
  int range(int i,int j,int a,int b,int u){
    if (b < L or U < a)
      return 0;
    if (L <= a and b <= U)
      return j-i;
    int M=(a+b)/2, ri=C[u][i], rj=C[u][j];
    return range(ri, rj, a, M, u*2) +
      range(i-ri, j-rj, M+1, b, u*2+1);
  }
  // Optional functions
  void swap(
    int i, int a, int b, int L, int U, int u
  ){
    if(L==U) return;
    int M = (L+U)/2;
    if(a<=M&&b<=M)
      swap(C[u][i], a, b, L, M, u*2);
    else if(a>M&&b>M)
      swap(i-C[u][i], a, b, M+1, U, u*2+1);
    else if(a>M) C[u][i+1]++;
    else C[u][i+1]--;
  }
  // Swap values at (i, i+1)
  // a->value at position i on the array
  // b->value at postion i+1 on the array
  void swap(int i, int a, int b){
    if(a!=b)
        swap(i, a, b, 0, s-1, 1);
  }
};