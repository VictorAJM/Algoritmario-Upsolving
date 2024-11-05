int N; 
vector<long long> h, H, p_pow, P_pow;
// h es el hasheo 1, H el 2, p_pow y P_pow 
// son las respectivas potencias de un primo
long long m; // debe ser un primo grande
int f(int i){
  map<int, int> mapa;
  for(int j = 0; j+i <= N; j++){
    long long d = 
      (((h[(j+i)-1]+m)-(j==0?0:h[j-1]))*
      p_pow[N-(j+i)])%m;
    long long c = 
      (((H[(j+i)-1]+m)-(j==0?0:H[j-1]))*
      P_pow[N-(j+i)])%m;
    auto it = mapa.find(d);
    if(it==mapa.end()){
      mapa[d]=c;
    }else{
      if(it->second==-1 || it->second==c){
        return j;
      }else{
        it->second=-1;
      }
    }
  }
  return -1;
}
