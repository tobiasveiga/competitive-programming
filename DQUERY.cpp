/*
DQUERY - D-query
https://www.spoj.com/problems/DQUERY/
Solution using Square Root Decomposition
ACCEPTED
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <unordered_map>
using namespace std;

int32_t input[30'000];
int32_t n, q, low, high, ans;
unordered_map<int32_t, int32_t> umap;
int32_t nextPos[30'000], nextPosOriginal[30'000];
int32_t blockCount, blockSize;

void computeNext() {
  for (int i = n - 1; i >= 0; i--) {
    if (umap.find(input[i]) == umap.end())
      nextPos[i] = INT32_MAX;
    else
      nextPos[i] = umap[input[i]];
    umap[input[i]] = i;
  }
  memcpy(nextPosOriginal, nextPos, sizeof(int32_t) * n);
}
void determineBlocks() {
  /*Ignores last block if it is partial*/
  blockSize = floor(sqrt(n)); // remainder size is sqrt(n) x r, r < 1
  blockCount = n / blockSize;
};
void sortInBlocks() {
  for (int i = 0; i < blockCount; i++)
    sort(nextPos + (i * blockCount), nextPos + ((i + 1) * blockCount));
};
void build() {
  computeNext();
  determineBlocks();
  sortInBlocks();
}

void solveInRange(int32_t a, int32_t b) {
  if (b >= n)
    b = n - 1;
  for (int i = a; i <= b; i++)
    if (nextPosOriginal[i] > high)
      ans += 1;
}
void countUniqueInBlock(int32_t blockInd) {
  int32_t blockStart = blockInd * blockSize;
  int32_t a = blockStart;
  int32_t b = blockStart + blockSize; // starts outside
  int32_t mid;
  if (a == b && nextPos[a] > high) {
    ans++;
    return;
  }
  while (a < b) {
    mid = (a + b) / 2;
    if (nextPos[mid] <= high)
      a = mid + 1;
    else
      b = mid;
  }
  ans += (blockSize - a + blockStart);
}

void query() {
  ans = 0;
  const int32_t firstBlock = low / blockSize; // 0 / 2, 1 / 2
  const int32_t lastBlock = high / blockSize; // 2 / 2, 3 /2
  if (firstBlock == lastBlock) {
    solveInRange(low, high);
    return;
  }
  solveInRange(low, firstBlock * blockSize + blockSize - 1);
  solveInRange(lastBlock * blockSize, high);
  for (int i = firstBlock + 1; i <= lastBlock - 1; i++)
    countUniqueInBlock(i);
}

int main() {
  cin >> n;
  for (long i = 0; i < n; i++)
    cin >> input[i];
  build();
  cin >> q;
  for (long i = 0; i < q; i++) {
    cin >> low;
    cin >> high;
    low--;
    high--;
    query();
    cout << ans << endl;
  }
  return 0;
}
