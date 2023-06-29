/*
MKTHNUM - K-th Number
https://www.spoj.com/problems/MKTHNUM/

Explanation:
- Online queries with square root decomponsition and optimized binary search
- The input is splited into blocks of size sqrt(n), which the values are sorted

1) Searching for the equivalent numbers
- Then we do binary search on the sorted list of unique values, which is
basically the input sorted
- At each iteration of the binary we are testing a CANDIDATE number
- We test the candidate by computing the lower bound of this number on each
block that is in the query range, and then we sum them to get the total lower
bound
- The total lower bound is the position that the CANDIDATE number would be
inserted into the query range values, the solution has total_lower_bound == k

2) Getting the correct answer
- Other numbers outside the query range can have a total lower bound equal as
the solution's, these are EQUIVALENT CANDIDATES
- Binary search of the cadidates ends at the lowest equivalent candidate
- To get the correct candidate, during the evalutation of any equivalent
candidate, we keep what is the smallest number x, such that x >= candidate,
in all blocks

3) Optimizing search within blocks
- The search in each block is done with binary search as well, since each block
is sorted
- However just simple binary search is not enough to get this solutions accepted
- The binary search can be optimized by choosing low and high values based
on previous searches in the same block for the same query
- So if we found lower bound in a block, but the CANDIDATE number was too high
then we use this lower bound as the new block high.

Time complexity:
Given s:= size / number of blocks, n:= number of input values
- preparation: O(n log2(n))
- searches in a block: O(log2(s) + log2(s/2) + log2(s/4) + ...) = O(log2(s)^2)
- query: O(log2(s)^2 * s)

NOTE: without block binary search optimization query complexity becomes:
- O(log2(n) * s * log2(s))

Space complexity:
- 3 times input size + 3 times number of blocks

ACCEPTED
*/
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#define i32 long
#define i64 long long

i32 BLKSIZE;

i32 n, m, p, q, k, input[100'000], unique[100'000], nunique, aux[100'000];
i32 ans, total_lower_bound;
i32 blk_low[500], blk_high[500], prev_value, blk_prev[500];
bool has_prev;

void show_prepared() {
  std::cout << "Input ";
  for (i32 i = 0; i < n; i++)
    std::cout << input[i] << " ";
  std::cout << "\n";
  std::cout << "Aux ";
  for (i32 i = 0; i < n; i++)
    std::cout << aux[i] << " ";
  std::cout << "\n";
  std::cout << "Unique ";
  for (i32 i = 0; i < nunique; i++)
    std::cout << unique[i] << " ";
  std::cout << "\n";
}

void prepare() {
  BLKSIZE = (i32)sqrt(n);

  memcpy(aux, input, n * sizeof(i32));
  for (i32 i = 0; i < n; i += BLKSIZE)
    std::sort(aux + i, aux + std::min(i + BLKSIZE, n));

  memcpy(unique, input, n * sizeof(i32));
  std::sort(unique, unique + n);
  nunique = n; // all numbers are different according to the problem
  // show_prepared();
}

void eval_block(i32 i_block, i32 value) {
  const auto blk_start = i_block * BLKSIZE;
  auto low = blk_start;
  auto high = std::min(blk_start + BLKSIZE, n) - 1;
  if (p > low || q < high) {
    low = std::max(low, p);
    high = std::min(high, q);
    for (i32 i = low; i <= high; i++)
      if (input[i] < value)
        total_lower_bound++;
      else if (input[i] < ans)
        ans = input[i];
    return;
  }
  if (has_prev) {
    if (value < prev_value)
      blk_high[i_block] = blk_prev[i_block];
    else
      blk_low[i_block] = blk_prev[i_block];
    low = blk_low[i_block];
    high = blk_high[i_block];
  } else {
    blk_low[i_block] = low;
    blk_high[i_block] = high;
  }
  while (low != high) {
    auto mid = (low + high) / 2;
    if (aux[mid] < value)
      low = mid + 1;
    else
      high = mid;
  } // low ends on first value >= k or at end of block
  blk_prev[i_block] = low;
  if (aux[low] < value) // i.e. low at the blocks end and all values < k
    low++;
  else if (aux[low] < ans)
    ans = aux[low];
  total_lower_bound += (low - blk_start);
}
void eval(i32 value) {
  ans = __LONG_MAX__;
  total_lower_bound = 0;
  auto r = p / BLKSIZE;
  auto s = q / BLKSIZE;
  for (i32 i = r; i <= s; i++)
    eval_block(i, value);
}
void reset_blk_info() {
  // for (i32 i = 0; i < n / BLKSIZE; i++) {
  //   blk_low[i] = i * BLKSIZE;
  //   blk_high[i] = std::min((i + 1) * BLKSIZE, n) - 1;
  //   blk_prev[i] = -1;
  // }
  has_prev = false;
}
void solve() {
  reset_blk_info();
  i32 low = 0;
  i32 high = nunique - 1;
  ans = unique[low];
  if (low == high)
    return;
  while (low != high) {
    i32 mid = (low + high) / 2;
    // std::cout << "Mid " << mid << "\n";
    eval(unique[mid]);
    if (total_lower_bound < k)
      low = mid + 1;
    else
      high = mid;
    prev_value = unique[mid];
    has_prev = true;
  } // stops at leftmost pos such k == total_lower_bound
  eval(unique[low]);
}
int main() {
  std::cin >> n >> m;
  for (i32 i = 0; i < n; i++)
    std::cin >> input[i];
  prepare();
  for (i32 i = 0; i < m; i++) {
    std::cin >> p >> q >> k;
    p--;
    q--;
    k--;
    // std::cout << "\n query " << p << " " << q << " " << k << "\n";
    solve();
    std::cout << ans << "\n";
  }

  return 0;
}