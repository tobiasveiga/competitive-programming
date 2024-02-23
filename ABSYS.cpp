#include <stdio.h>
#include <string.h>

int TC;
const int N = 100;
char a[N], b[N], c[N];

bool has_machula(char *word) { return strchr(word, 'm') != NULL; }

int get_num(char *x) {
  int out = 0;
  int n = strlen(x);
  for (int i = 0; i < n; i++) {
    out *= 10;
    out += (x[i] - '0');
  }
  return out;
}

void get_string(int num, char *out) {
  int n = 0;
  for (int aux = num; aux > 0; aux /= 10)
    out[n++] = (aux % 10) + '0';
  out[n] = 0;
  for (int i = 0; i < n / 2; i++) {
    auto aux = out[i];
    out[i] = out[n - i - 1];
    out[n - i - 1] = aux;
  }
}

int main() {
  scanf("%d", &TC);
  while (TC--) {
    scanf("%s + %s = %s", a, b, c);
    if (has_machula(a))
      get_string(get_num(c) - get_num(b), a);
    else if (has_machula(b))
      get_string(get_num(c) - get_num(a), b);
    else
      get_string(get_num(a) + get_num(b), c);
    printf("%s + %s = %s\n", a, b, c);
  }
}