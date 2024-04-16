#include <stdio.h>
#include <string.h>

char line[201];
int ncols, nrows, n;
char ans[201];

int main() {
  while (true) {
    scanf("%d", &ncols);
    if (ncols == 0)
      break;
    scanf("%s", line);
    n = strlen(line);
    nrows = n / ncols;
    for (int i = 0; i < n; i++) {
      auto row_num = (i / ncols);
      auto col_num =
          (row_num % 2 == 0 ? (i % ncols) : (ncols - 1 - (i % ncols)));
      ans[col_num * nrows + row_num] = line[i];
    }
    ans[n] = 0;
    printf("%s\n", ans);
  }
  return 0;
}