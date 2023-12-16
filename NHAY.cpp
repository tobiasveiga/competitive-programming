/*
NHAY - A Needle in the Haystack
https://www.spoj.com/problems/NHAY/

Explanation:
- Uses KMP algorithm
- The general idea is that for a number of consecutive hits matching the needle
string, if there is a miss, then there is a new number of hits we can recover
from the previous and continue matching from there.
- The table recover maps from previous hits to a new hits count.

ACCEPTED
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <unordered_set>
#include <vector>
#define i32 long

i32 N, h; // h is hay pointer
char *needle, hay;

std::vector<i32> solutions;

i32 *recover;
void set_recover() {
  recover = (i32 *)calloc(strlen(needle) + 1, sizeof(i32));
  // recover[0 and 1] = 0
  for (i32 j = 1, i = 1; j < N; j++) {
    if (needle[j - i] == needle[j]) {
      recover[j + 1] = j - i + 1;
      continue;
    }
    if (needle[0] == needle[j]) {
      i = j;
      recover[j + 1] = j - i + 1;
    } else
      i = j + 1;
  }
}

bool test_line_end(char c) { return c != '\n' && c != '\r' && c != EOF; }

int main() {

  while (scanf("%ld", &N) != EOF) {
    scanf("%ms", &needle);
    set_recover();

    // Solve
    getchar(); // skips \n
    i32 hits = 0;
    for (hay = getchar(), h = 0; test_line_end(hay); hay = getchar(), h++) {
      while (hits > 0 && hay != needle[hits])
        hits = recover[hits];
      if (hay == needle[hits])
        hits++;
      if (hits == N) {
        solutions.push_back(h - N + 1);
        hits = recover[N];
      }
    }

    // print solution
    for (auto pos : solutions)
      printf("%ld\n", pos);
    if (solutions.size() == 0)
      printf("\n");

    // reset
    free(recover);
    solutions.clear();
  }
  return 0;
}
