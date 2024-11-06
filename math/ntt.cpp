const int N=(1<<21)+5;
int a[N],b[N],r[N],w[N],mod,n,ninv;
void init(int _n,int g,int _mod){
  n=1<<32-__builtin_clz(_n),
  mod=_mod,ninv=inv(n,mod);
  // reversal bit permutation
  rep(i,0,n) r[i]=r[i>>1]>>1|(i&1?n>>1:0); 
  int wn=binpow(g,(mod-1)/n,mod); w[n>>1]=1;
  rep(i,(n>>1)+1,n) w[i]=1ll*w[i-1]*wn%mod;
  per(i,1,n>>1) w[i]=w[i<<1];
}
void ntt(int *a){
  rep(i,0,n) if(i<r[i]) swap(a[i],a[r[i]]);
  for(int len=1;len<n;len<<=1) 
    for(int i=0;i<n;i+=len<<1) rep(j,0,len){
      int u=a[i|j];
      int v=1ll*w[len|j]*a[i|len|j]%mod;
      a[i|j]=u+v<mod?u+v:u+v-mod;
      a[i|len|j]=u-v<0?u-v+mod:u-v;
  }
}
void conv(){
  ntt(a); ntt(b);
  rep(i,0,n) a[i]=1ll*a[i]*b[i]%mod;
  reverse(a+1,a+n); ntt(a);
  rep(i,0,n) a[i]=1ll*a[i]*ninv%mod;
}

// Si a[i] sobrepasa el primo se necesita 
// hacer fft con dos o tres primos distintos

int a[N],b[N],ans[N][3];
const int m[]=
  {(5<<25)+1,(7<<26)+1,(119<<23)+1};
const int inv[]=
  {104391568,715912618,554580198};
// 3 es raiz primitiva de esos primos
const int g=3; 
int garner(int *a,int mod){
  // Los coeficientes del número en la 
  // mixed-radix de los primos
  rep(i,0,3) rep(j,0,i) 
    a[i]=
      1ll*(a[i]-a[j]+m[i])*inv[i+j-1]%m[i]; 
  // Evaluación
  per(i,0,2) a[i]=(a[i]+1ll*a[i+1]*m[i])%mod;
  return a[0];
}

/* Versión con dos módulos regresando ll
const int m[]=
{(5<<25)+1,(7<<26)+1},inv[]={104391568},g=3;
ll c[N];
ll garner(int *a){
  a[1]=1ll*(a[1]-a[0]+m[1])*inv[0]%m[1];
  return a[0]+1ll*a[1]*m[0];
}*/
void solve(int an, int bn, int mod){
  rep(i,0,3) {
    init(an+bn-1,g,m[i]);
    rep(j,0,n) a[j]=j<an?a[j]%m[i]:0;
    rep(j,0,n) b[j]=j<bn?b[j]%m[i]:0;
    conv();
    rep(j,0,n) ans[j][i]=a[j];
  }
  rep(i,0,n) a[i]=garner(ans[i],mod);
}