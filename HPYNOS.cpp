#include <stdio.h>
#define i32 long

i32 N;
i32 get_next(i32 curr) {
  i32 res = 0;
  while (curr > 0) {
    auto rem = curr % 10;
    res += rem * rem;
    curr /= 10;
  }
  // return upperbound == 4 + 9 ** 2 * 9 = 733
  return res;
}
int main() {
  scanf("%ld", &N);
  i32 T = 0;
  i32 a = N, b = N;
  while (a != 1) {
    b = get_next(b);
    if (a == b) {
      printf("-1\n");
      return 0;
    }
    b = get_next(b);
    if (a == b) {
      printf("-1\n");
      return 0;
    }
    a = get_next(a);
    // printf("curr a %ld\n", a);
    T++;
  }
  printf("%ld\n", T);
  return 0;
}