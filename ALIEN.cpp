/*
ALIEN - Aliens at the train
https://www.spoj.com/problems/ALIEN/

Explantion:
- Front a back pointer, i.e. leaving and entering station respectively
- For any back pointer value, move front pointer as far as possible
- When front pointer is maxed, then move back pointer by one. Repeat
- Whenever a pointer is updated check for number of stations and people.

ACCEPTED
*/
#include <stdio.h>
#define i32 long

i32 T, At, Bt, A[100'001];
int main() {
  scanf("%ld", &T);
  while (T--) {
    scanf("%ld %ld", &At, &Bt);
    for (i32 i = 0; i < At; i++)
      scanf("%ld", A + i);
    i32 np = 0, ns = 0;
    i32 i = 0, j = 0;
    i32 p = 0, s = 0;
    while (i < At) {
      if (s > ns) // update max stations
        np = p, ns = s;
      if (s == ns && p < np) // max stations the same but with less people
        np = p;
      while (j < At) {
        if (p + A[j] <= Bt) {
          p += A[j], s++;
          if (s > ns)
            np = p, ns = s;
          if (s == ns && p < np)
            np = p;
        } else
          break;
        j++;
      }
      p -= A[i], s--;
      i++;
    }
    printf("%ld %ld\n", np, ns);
  }
  return 0;
}
