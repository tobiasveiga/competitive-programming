#include <stdio.h>

int a, b;

int main() {
  while (true) {
    scanf("%d %d", &a, &b);
    if (a == -1 && b == -1)
      break;
    int ans = 0;
    if (a == b) {
      if (a == 0)
        printf("0\n");
      else
        printf("1\n");
      continue;
    }

    if (a < b) {
      auto aux = a;
      a = b;
      b = aux;
    }
    auto slots = b + 1;
    ans = a / slots;
    if (a % slots != 0)
      ans++;
    printf("%d\n", ans);
  }
  return 0;
}