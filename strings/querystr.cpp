#include<bits/stdc++.h>
using namespace std;

// Fills Z array for given string str[]
void getZarr(vector<int> &str, vector<int> &Z) {
    int n = str.size();
    int L, R, k;

    L = R = 0;
    for (int i = 1; i < n; ++i) {
      if (i > R) {
        L = R = i;
        while (R<n && str[R-L] == str[R])
          R++;
        Z[i] = R-L;
        R--;
      }
      else {
        k = i-L;
        if (Z[k] < R-i+1)
          Z[i] = Z[k];
        else{
          L = i;
          while (R<n && str[R-L] == str[R])
            R++;
          Z[i] = R-L;
          R--;
        }
      }
    //    cout<<Z[i]<<" ";
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin>>n>>m;
    vector<int> a(n);
    for(int &x: a) cin>>x;
    vector<int> b(m);
    for(int &x: b) cin>>x;
    vector<int> s(n+m-1, (-1e9)-5);
    for(int i = 0; i < m-1; i++){
        s[i] = b[i+1]-b[i];
    }
    for(int i = m; i < n+m-1; i++){
        s[i] = a[(i+1)-m]-a[i-m];
    }
   // cout<<"a";
    vector<int> Z(n+m-1);
    getZarr(s, Z);
    int d = 0;
    for(int i = m; i<n+m-1; i++){
        if(Z[i]==m-1)
            d++;
    }
    cout<<d<<"\n";
    return 0;
}