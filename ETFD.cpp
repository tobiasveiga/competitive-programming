/*
ETFD - Euler Totient Function Depth
https://www.spoj.com/problems/ETFD/

Explanation:
- Update from the ETFS solution -> this utilizes Mobius Inversion to compute the
values of phi quickly from 1 to 1e6
- Then compute the whole sequence of a_n depth (memo) with a iterative bottom up
approach
- While computing a, each value found is also store in a map s.t. we have
    >> depth -> (sorted idx with a[idx] = depth)
- This map is used to find in O(log(n)) the count of memo values that are equal
to k;

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

int T;
i32 n, m, k, cnt;

i32 phi[(i32)1e6 + 1];
i32 memo[(i32)1e6 + 1];

void compute_phi() {
  for (i32 i = 0; i < 1e6 + 1; i++)
    phi[i] = i;
  for (i32 i = 2; i < 1e6 + 1; i++) {
    if (phi[i] != i)
      continue;
    for (i32 j = i; j < 1e6; j += i) {
      phi[j] -= (phi[j] / i);
    }
  }
}
std::unordered_map<i32, std::vector<i32>> k2num;
void compute_memo() {
  memo[1] = 0;
  k2num[0] = std::vector<i32>({1});
  for (i32 i = 2; i < 1e6 + 1; i++) {
    auto depth = memo[phi[i]] + 1;
    memo[i] = depth;
    if (k2num.find(depth) != k2num.end())
      k2num[depth].push_back(i);
    else
      k2num[depth] = std::vector<i32>({i});
  }
}
void solve() {
  auto low = k2num[k].begin(), high = k2num[k].end();
  auto lb = std::lower_bound(low, high, m);              // left is < m
  auto ub = std::upper_bound(low + (lb - low), high, n); // left is <= n
  cnt = ub - lb;
}
int main() {
  compute_phi();
  compute_memo();
  scanf("%d", &T);
  while (T--) {
    scanf("%ld %ld %ld", &m, &n, &k);
    solve();
    printf("%ld\n", cnt);
  }
  return 0;
}