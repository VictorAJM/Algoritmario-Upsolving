#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
using ll = long long;
const double PI = acos(-1);
void fft(vector<cd> & a, bool invert) {
  ll n = a.size();
  if (n == 1) return;
  vector<cd> a0(n / 2), a1(n / 2);
  for (ll i = 0; 2 * i < n; i++) {
	a0[i] = a[2*i];
	a1[i] = a[2*i+1];
  }
  fft(a0, invert);
  fft(a1, invert);
  double ang = 2 * PI / n * (invert ? -1:1);
  cd w(1), wn(cos(ang), sin(ang));
  for (ll i = 0; 2 * i < n; i++) {
	a[i] = a0[i] + w * a1[i];
	a[i + n/2] = a0[i] - w * a1[i];
	if (invert) {
  	a[i] /= 2;
  	a[i + n/2] /= 2;
	}
  w *= wn;
  }
}
vector<ll> multiply(
  vector<ll> const& a, vector<ll> const& b
  ) {
  vector<cd> fa(a.begin(), a.end());
  vector<cd> fb(b.begin(), b.end());
  ll n = 1;
  while (n < a.size() + b.size())
	n <<= 1;
  fa.resize(n);
  fb.resize(n);
  fft(fa, false);
  fft(fb, false);
  for (ll i = 0; i < n; i++)
	fa[i] *= fb[i];
  fft(fa, true);
  vector<ll> result(n);
  for (ll i = 0; i < n; i++)
	result[i] = round(fa[i].real());
  return result;
}

int main() {
  int n,m;
  cin>>n>>m;
  vector<ll> a(n);
  vector<ll> b(m);
  for(int i=0;i<n;i++) {
    int u;
    cin>>u;
    a[i]=u;
  }
  for (int i=0;i<m;i++) {
    int u;
    cin>>u;
    b[m-1-i]=u;
  }
  auto c = multiply(a,b);
  for (int i=0;i<n+m-1;i++) cout<<c[i]<<" ";
}