/*
OLOLO - Onotole needs your help
https://www.spoj.com/problems/OLOLO/

Explanation
- Uses the XOR operation to find the distinct number
- Imagine a table where each number is as row of bits
- The XOR operates on each column
  -> columns with even number of bits will zero out
  -> columns with odd number of bits with result in 1 bit
- The unique number causes the columns with its bits to have odd number of bits
- Hence the XOR output on the table is the unique number

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 N, Pi, ans;

int main() {
  while (scanf("%ld", &N) != EOF) {
    ans = 0;
    for (i32 i = 0; i < N; i++)
      scanf("%ld", &Pi), ans ^= Pi;
    printf("%ld\n", ans);
  }
  return 0;
}
