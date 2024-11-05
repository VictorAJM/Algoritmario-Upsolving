#include<bits/stdc++.h>
#define F first
#define S second
#define sz size()
using namespace std;

const long long P = 1e9 + 7;
const long long p = 257;


long long pot(long long x, long long v){
	if(v==0) return 1; 
    if(v==1) return x;
    long long y = pot(x,v/2); y=(y*y)%P; 
    return ((v&1 ? (y*x)%P : y));
}


const int lmt = 1e5+5; 
int sp[30][lmt];
int main(){

  int n; cin>>n;
  vector<pair<string, int>> s(n);
  for(int i = 0; i < n; i++){
      cin>>s[i].first;
      s[i].second=i+1;
  }
  sort(s.begin(), s.end());
  map<long long, int> hashing;
  vector<long long> POW(n+1,1);
  for(int i = 1; i <= n; i++){
    POW[i] = (POW[i-1]*p)%P;
  }
  
  for(int i = 0; i < n; i++){
    long long D = 0;
    for(int j = 0; j < s[i].F.sz; j++){
      D = (D + s[i].first[j]*POW[j])%P;
    }
  }
  vector<int> r(n+1);
  for(int i = 0; i < n; i++){
      r[s[i].second]=i;
  }
  for(int i = 1; i < n; i++){
    int j = 0;
    while(j<min(s[i-1].F.sz, s[i].F.sz) && 
      s[i-1].first[j]==s[i].first[j]){
      j++;
    }
    sp[0][i]=j;
  }
  return 0;
}