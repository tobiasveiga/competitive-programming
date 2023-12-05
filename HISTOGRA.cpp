/*
HISTOGRA - Largest Rectangle in a Histogram
https://www.spoj.com/problems/HISTOGRA/

Explantion:
- Uses induction approach, adding rectangles to the right
- Assume the effective range ER of a rectangle := 1 + left_ER + right_ER.
left_ER is how many rectangles to its left are not smaller than itself, right_ER
is how many rectangles to its right are not smaller than itself

Induction approach:
- The first added rectangle has left_ER = 0
- If the next added rectangle is greater than the previous, its left_ER will be
0 as well.
- If we add a smaller rectangle all rectangles to the left that are taller
reached their maximum right_ER and can be removed, right_ER being the distance
to the added rectangle. Also, the ammount of rectangles removed is the left_ER
of the added rectangle.
- So when a rectangle enters, we have its left ER.
- And when a rectangle is removed know its right_ER.
- When the sequence ends, i.e. no more rectangles to be added, we remove all
rectangles.

Implementation details:
- This solution uses a stack for add and removal operations.
- The left_ER is computed at removal time by computing the distance to the
previous rectangle in the stack
- We add one extra position in the end of the inputs with height = -1 as a
sentinel to remove all rectangles at the end of the process
- Since we add N rectangles and removed N rectangles, the time complexity of
this solutions is O(N). The stack can use up to O(N) memory.

ACCEPTED
*/
#include <stdio.h>

#define i32 long

i32 n, max, height[100'001], stack[100'001], last;

void unstack(i32 pos) {
  // last == -1, then stack is empty
  while (last != -1 && height[pos] < height[stack[last]]) {
    auto prev_pos = (last > 0 ? (stack[last - 1]) : -1);
    auto area = height[stack[last]] * (pos - prev_pos - 1);
    if (area > max)
      max = area;
    last--;
  }
}

int main() {
  scanf("%ld", &n);
  while (n != 0) {
    for (i32 i = 0; i < n; i++) {
      scanf("%ld", height + i);
    }
    max = -1;
    height[n] = -1; // sentinel
    stack[0] = 0;
    last = 0;
    for (i32 pos = 1; pos < n + 1; pos++) {
      unstack(pos);
      stack[++last] = pos;
    }
    printf("%ld\n", max);

    scanf("%ld", &n);
  }
}