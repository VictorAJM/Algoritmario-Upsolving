
// count bits in n
#define bits(n) (int)__builtin_popcount(n)

// Number of leading zeros
__builtin_clz(x)   // for int
__builtin_clzll(x) // for long long
// Number of trailing zeros
__builtin_ctz(x)    // for int
__builtin_ctzll(x)  // for long long
// Returns 1+the index of lsb of x
__builtin_ffs(x)

// pragma next to include, similar to O(1)
#pragma GCC target("popcnt")
bitset<M> a[N];
int main() {
  int similarBits = (a[i]&a[j]).count();

  a[i].set(i); // set ith to true
  a[i].reset(i); // set ith to false
  a[i].flip(i); // flip it!
  a[i].to_string();
  a[i].to_ulong(); // a[i].to_ullong();
  a[i].all(); // any, none
}