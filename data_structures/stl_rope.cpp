#include <ext/rope>
using namespace __gnu_cxx;
rope<int> s;
// Sequence with O(log(n)) random access,
// insert, erase at any position
// s.push_back(x);
// s.insert(i,r) insert rope r at position i
// s.erase(i,k)  erase subsequence [i,i+k)
// s.substr(i,k) return new rope with [i,i+k)
// s[i] access ith element (cannot modify)
// s.mutable_reference_at(i)
// (allows modification)
// s.begin() and s.end()
// to modify (mutable_begin(), mutable_end())