#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// Ordered set
typedef tree<
  int, null_type,
  less<int>, rb_tree_tag,
  tree_order_statistics_node_update
> ordered_set;
// Iterator to K-th largest element
//  > st.find_by_order(index)
// Count of elements strictly smaller:
//  > st.order_of_key(x)


// Multi-set
typedef tree<
  int, null_type,
  less_equal<int>, rb_tree_tag,
  tree_order_statistics_node_update
> ordered_multiset;
// Iterator to K-th largest element
//  > st.find_by_order(index)
// Count of elements strictly smaller:
//  > st.order_of_key(x)
// Use *st.find_by_order(index) to errase