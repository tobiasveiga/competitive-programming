/*
LASTDIG - The last digit
https://www.spoj.com/problems/LASTDIG/

Solution:
- We want to know the last digit of  a ** b
- We only need the last digit of a, a_, to know the answer
- Also, for any given a_ and b there is a very limited number of answers
- Example a_ = 2, b = 0, 1, 2, 3, 4, 5 => answer = 1, 2, 4, 8, 6, 2, ...
- We can see the answer will repeat itself at every 4 numbers
- All digits from 0 to 9 repeat itself to at most a pattern of length 4
- The pattern length of a_ will be the gropup_size[a_]
- Hence instead of using b we can use b_ = ((b-1) % group_size[a_]) + 1
- Then we just precompute all answer values from a_ and b_
- And for each input we just need to map a to a_ and b to b_

Note:
- SPOJ limits solution file size to 700B
- To make this run, remove this header and change all last_digit to ld and
group_size to gs, and remove the test_build function

ACCEPTED
*/
#include <math.h>
#include <stdio.h>

#define i32 long

i32 last_digit[10][6];
i32 group_size[10];
i32 T, a, b;

void build() {
  for (i32 i = 0; i < 10; i++) {
    last_digit[i][0] = 1;
    last_digit[i][1] = i;
    auto curr = i;
    for (i32 j = 2; j < 6; j++) {
      curr = curr * i;
      last_digit[i][j] = curr % 10;
      if (last_digit[i][j] == last_digit[i][1]) {
        group_size[i] = j - 1;
        break;
      }
    }
  }
}

void test_build() {
  for (i32 i = 0; i < 10; i++) {
    for (i32 j = 0; j < group_size[i] + 2; j++) {
      printf("%ld ", last_digit[i][j]);
    }
    printf("\n");
  }
}

i32 solve() {
  if (b == 0)
    return 1l;
  auto a_ = a % 10;
  auto b_ = ((b - 1) % group_size[a_]) + 1;
  return last_digit[a_][b_];
}
int main() {
  build();
  scanf("%ld", &T);
  while (T--) {
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", solve());
  }
  return 0;
}