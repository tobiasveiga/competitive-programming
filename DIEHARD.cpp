/*
DIEHARD - DIE HARD
https://www.spoj.com/problems/DIEHARD/

Explanation:
- Use DP with memoization;
- Memo parameters are health, armor and place
- health can max up to 1003 and armor can max up to something around 1350
- place has only three values, 0,1,2
- DP function
    >> time(H, A, place) =
      1 + max(time(H+p_mod, A+p_mod, p) for all p with place != p)
- time(h, a, place) == 0 for h<=0 or a<=0

ACCEPTED
*/
#include <stdio.h>

int t, H, A, ans;
int memo[1004][1500][3]; // starts at 0

int get(int h, int a, int place) {
  if (h <= 0 || a <= 0)
    return 1; // counts death as 1 (subtract later)
  if (memo[h][a][place] != 0)
    return memo[h][a][place];
  int best = -1, temp;
  for (int p = 0; p < 3; p++) {
    if (p == place)
      continue;
    if (p == 0) // air
      temp = get(h + 3, a + 2, p);
    else if (p == 1) // water
      temp = get(h - 5, a - 10, p);
    else // fire
      temp = get(h - 20, a + 5, p);
    best = (temp > best ? temp : best);
  }
  memo[h][a][place] = best + 1;
  return best + 1;
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &H, &A);
    ans = get(H + 3, A + 2, 0); // always starts at air (0)
    printf("%d\n", ans - 1);
  }
}