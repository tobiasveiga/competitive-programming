/*
MULTQ3 - Multiples of 3
https://www.spoj.com/problems/MULTQ3/

Explanation:
- Square Root Decomposition
- A block has three counters, cnt[3], onde for each num % 3 values in the block
range
- A block has a pointer, p in [0, 2], to the current counter initialized at 0
- A full block increment means p is updated to the previous value
- A partial increment update the input array and the block cnt array
- A full block query returns cnt[p]
- A partial query returns a linear time search in the block for %3==p numbers

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 N, Q, A, B, CMD;

i32 a[100'000];
i32 M; // number of blocks / block size;
struct Block {
  i32 cnt[3], p, start, end;
  void inc() {
    if (A <= start && B >= end) {
      p = (p - 1 + 3) % 3;
      return;
    }
    for (i32 j = std::max(start, A); j <= std::min(end, B); j++) {
      cnt[a[j]]--;
      a[j] = (a[j] + 1) % 3;
      cnt[a[j]]++;
    }
  }
  i32 get() {
    if (A <= start && B >= end)
      return cnt[p];
    i32 total = 0;
    for (i32 j = std::max(start, A); j <= std::min(end, B); j++) {
      if (a[j] == p)
        total++;
    }
    return total;
  }
} block[1'000];

void build() {
  M = (i32)sqrt(N) + 1;
  for (i32 i = 0; i < M; i++) {
    block[i].start = i * M, block[i].end = std::min(i * M + M, N) - 1;
    block[i].cnt[0] = block[i].end - block[i].start + 1;
  }
}

void increase() {
  for (i32 i = A / M; i <= B / M; i++)
    block[i].inc();
}

void answer() {
  i32 total = 0;
  for (i32 i = A / M; i <= B / M; i++)
    total += block[i].get();
  printf("%ld\n", total);
}

int main() {
  scanf("%ld %ld", &N, &Q);
  build();
  for (i32 i = 0; i < Q; i++) {
    scanf("%ld %ld %ld", &CMD, &A, &B);
    if (CMD == 0)
      increase();
    else
      answer();
  }
  return 0;
}