
// Phi function
int phi[N];
void totient() {
  for (int i=1;i<N;i++) phi[i]=i;
  for (int i=2;i<N;i++) {
	  if (phi[i]==i) {
  	  for (int j=i;j<N;j+=i)
        phi[j]-=phi[j]/i;
	  }
  }
}

// extended euclid and inverse
using ll = long long;
ll extended(ll a,ll b,ll &x,ll &y) {
  if (b==0) {
	x = 1; y = 0;
	return a;
  }
  ll x1, y1;
  ll d = extended(b,a%b,x1,y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
ll inverse(ll a, ll m) {
  ll x, y;
  ll g = extended(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}


// Mobius inversion
//f(1) = 1
//f(p) = -1
const long long N= 10000000;
vector<long long> m(N + 1);
vector<bool> isp(N + 2, 1);
int mb(){
  m[1] = 1, m[2] = -1;
  for(int i=3; i<=N; i+=2){
    if(isp[i]){
      m[i] = -1;
      for(int j=2;j*i<=N;j++){
        isp[i*j] = 0;
        if(j%i) m[i*j]=m[i]*m[j];
        else m[i*j] = 0;
      }
    }   
  }
}
