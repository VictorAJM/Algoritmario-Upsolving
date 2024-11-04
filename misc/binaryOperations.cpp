
// count bits in n
#define bits(n) (int)__builtin_popcount(n)


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