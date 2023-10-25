
/*
GSS3 - Can you answer these queries III
https://www.spoj.com/problems/GSS3/

- Solution using Square Root Decomposition instead of Binary Tree
- Solution is based on merging intervals at constant time, check Block.merge
function

Time complexities
- Build = n_blocks x build_block = sqrt(n) x sqrt(n) = n
- Modify operation = modify block = sqrt(n)
- Query time = sqrt(n)

ACCEPTED
*/
#define i32 long
#define i64 long long
#include <algorithm>
#include <iostream>
#include <math.h>

i32 A[50'000], N, M;
i32 op, x, y;
i32 block_size, n_blocks;
struct Block {
  i32 left; // max is 500kk
  i32 right;
  i32 best;
  i32 total;
  Block merge(Block other) {
    Block merged;
    merged.left = std::max(total + other.left, left);
    merged.right = std::max(other.total + right, other.right);
    merged.best = std::max({best, other.best, right + other.left});
    merged.total = total + other.total;
    return merged;
  }
} blocks[224];
Block NULL_BLOCK = {0, 0, INT32_MIN, 0};

Block build_block(i32 start, i32 end) {
  if (end >= N)
    end = N - 1;
  i32 left, right, best;
  left = right = best = INT32_MIN;
  i32 total = 0;
  for (i32 i = start; i <= end; i++) {
    left = std::max(total + A[i], left);
    right = std::max(right + A[i], A[i]);
    best = std::max(best, right); // new interval
    best = std::max(best, A[i]);  // individual interval
    total += A[i];
  }
  return {left, right, best, total};
}

void build() {
  block_size = ceil(sqrt(N));
  n_blocks = ceil(N / block_size);
  for (i32 i = 0, b = 0; b <= (N - 1) / block_size; i += block_size, b++)
    blocks[b] = build_block(i, i + block_size - 1);
}

void modify() {
  // find block and update it
  A[x] = y;
  i32 b = x / block_size;
  i32 start = b * block_size;
  blocks[b] = build_block(start, start + block_size - 1);
  return;
}

Block get_block(i32 b) {
  i32 start = b * block_size;
  i32 end = start + block_size - 1;
  if (x <= start && y >= end)
    return blocks[b];
  return build_block(std::max(start, x), std::min(end, y));
}

void print_max() {
  Block merged = NULL_BLOCK;
  for (i32 b = x / block_size; b <= y / block_size; b++)
    merged = merged.merge(get_block(b));
  std::cout << merged.best << "\n";
}

int main() {
  std::cin >> N;
  for (i32 i = 0; i < N; i++) {
    std::cin >> A[i];
  }
  build();
  std::cin >> M;
  for (i32 i = 0; i < M; i++) {
    std::cin >> op >> x >> y;
    if (op == 0) {
      x--;
      modify();
    } else {
      x--;
      y--;
      print_max();
    }
  }
  return 0;
}