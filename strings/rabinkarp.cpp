#include<bits/stdc++.h>
using namespace std;

// Dadas dos cadenas, encuentra en qué índices
// hay tal que coincide
vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int N = s.size(), M = t.size();

    vector<long long> p_pow(max(N, M)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m; 
        // saca las potencias para el hashing

    vector<long long> h(M + 1, 0); 
    for (int i = 0; i < M; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
        // hace hashing de la string A
    
    long long h_s = 0; 
    for (int i = 0; i < N; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 
        // hace el hashing del prefijo-N de B

    vector<int> occurrences;
    for (int i = 0; i + N - 1 < M; i++) {
        long long cur_h = (h[i+N] + m - h[i]) % m;
        // Hace el hasheo de Ai - Ai+N
        if (cur_h == h_s * p_pow[i] % m) 
            occurrences.push_back(i);
            // recorre el patron i posiciones
    }
    return occurrences;
}

int main(){
    return 0;
}