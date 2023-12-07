/*
ABCDEF - ABCDEF
https://www.spoj.com/problems/ABCDEF/

Explanatation:
- Update the equation to a * b + c = (f + e) * d, with d != 0
- First we compute all the possible values on the left hand side of the
equation. We store each value in a hashmap together with how many times it
appeared
- Then we compute all the possible values in the right hand side of the
equation. For each value, if it is on the hashmap, then we have found a
solution, so we add the number of times the left hand side value appeared to the
total.

ACCEPTED
*/
#include <stdio.h>
#include <unordered_map>
#define i32 long

i32 N, input[100], total;
std::unordered_map<i32, i32> possibilities;

int main() {
  scanf("%ld", &N);
  for (i32 i = 0; i < N; i++) {
    scanf("%ld", input + i);
  }
  for (i32 i = 0; i < N; i++)
    for (i32 j = 0; j < N; j++)
      for (i32 k = 0; k < N; k++) {
        auto left_side = (input[i] * input[j] + input[k]);
        if (possibilities.find(left_side) != possibilities.end())
          possibilities[left_side]++;
        else
          possibilities[left_side] = 1;
      }
  total = 0;
  for (i32 i = 0; i < N; i++)
    for (i32 j = 0; j < N; j++)
      for (i32 k = 0; k < N; k++) {
        if (input[k] == 0)
          continue;
        auto right_side = (input[i] + input[j]) * input[k];
        if (possibilities.find(right_side) != possibilities.end())
          total += possibilities[right_side];
      }
  printf("%ld\n", total);
  return 0;
}
