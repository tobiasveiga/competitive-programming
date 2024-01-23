/*
ANARC05B - The Double HeLiX
https://www.spoj.com/problems/ANARC05B/

Explanation:
- Leverages on two things
- 1) The choice of segment between two common numbers is always the one with
largest sum
- 2) The sequences are already sorted, so a double pointer approach can be used
to find the common numbers in a single pass in each sequence (see merging sorted
lists)
- We start from the beginning of both sequence and move the pointer together,
always moving the one with the smallest value, then when the pointer point to
the same number (end of segment) we update the sum with maximum of the sum of
the two previous segment

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 n, m, a[10'000], b[10'000], sum;

void solve() {
  i32 i, j, sumA, sumB;
  i = 0, j = 0;
  sumA = 0, sumB = 0, sum = 0;
  while (i < n) { // sequence a guaranteed to end first
    if (a[i] > b[j])
      sumB += b[j++];
    else if (a[i] < b[j])
      sumA += a[i++];
    else {
      sum += std::max(sumA, sumB);
      sum += a[i];
      i++, j++;
      sumA = 0, sumB = 0;
    }
  }
  while (j < m)
    sumB += b[j++];
  sum += std::max(sumA, sumB);
}

int main() {
  while (true) {
    std::cin >> n;
    if (n == 0)
      break;
    for (i32 i = 0; i < n; i++)
      std::cin >> a[i];
    std::cin >> m;
    for (i32 i = 0; i < m; i++)
      std::cin >> b[i];
    if (a[n - 1] > b[m - 1]) {
      std::swap(n, m);
      std::swap(a, b);
    }
    solve();
    printf("%ld\n", sum);
  }
  return 0;
}