/*
ANARC09A - Seinfeld
https://www.spoj.com/problems/ANARC09A/

Solution:
- Simple greedy solution
- We iterate the line from left to right
- Keep a counter for the number of changes and for how stable the line is
- The stability counter adds 1 if a { is consumed and subtract 1 if } is
consumed
- Stability should end at 0
- Stability can't ever go below 0, meaning excessive } at one point
- Stability can't grow beyond a value, in which we can't have enough subtraction
left
- The stability max value at iteration i is n - i;

ACCEPTED
*/
#include <stdio.h>
#include <string.h>
#define i32 long

char line[2001];

i32 solve() {
  i32 stability = 0, changes = 0, n = strlen(line);

  for (i32 i = 0; i < n; i++) {
    if (line[i] == '{') {
      if (stability >= (n - i))
        changes++, stability--;
      else
        stability++;
    } else {
      if (stability == 0)
        changes++, stability++;
      else
        stability--;
    }
  }
  return changes;
}

int main() {
  i32 t = 1;
  while (scanf("%s", line) && line[0] != '-') {
    printf("%ld. %ld\n", t++, solve());
  }
  return 0;
}