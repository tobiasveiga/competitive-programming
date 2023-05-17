/*
PALIN - The Next Palindrome
https://www.spoj.com/problems/PALIN/
ACCEPTED
*/
#include <stdio.h>
#include <string.h>

long getExtra(char *word) {
  long n = strlen(word);
  long leftLower = n / 2 - 1;       // 2 -> 0, 3 -> 0
  long rightHigher = n / 2 + n % 2; // 2 -> 1, 3 -> 2
  for (long i = leftLower, j = rightHigher; i >= 0; i--, j++)
    if (word[i] < word[j])
      return 1;
    else if (word[i] > word[j])
      return 0;
  return 0;
}
bool evalIsPalindrome(char *word) {
  long extra = 0;
  long n = strlen(word);
  long leftLower = n / 2 - 1;       // 2 -> 0, 3 -> 0
  long rightHigher = n / 2 + n % 2; // 2 -> 1, 3 -> 2
  for (long i = leftLower, j = rightHigher; i >= 0; i--, j++)
    if (word[i] != word[j])
      return false;
  return true;
}

void addExtra(char *word, long extra) {
  long n = strlen(word);
  long mid = n / 2 + n % 2 - 1; // 2 -> 0, 3 -> 1
  long inc = extra;
  long aux;
  for (long i = mid; i >= 0; i--) {
    aux = (word[i] - '0') + inc;
    inc = aux / 10;
    word[i] = (aux % 10) + '0';
  }
}
void print(char *word) {
  long n = strlen(word);
  long leftLower = n / 2 - 1; // 2 -> 0, 3 -> 0
  // left
  for (long i = 0; i <= leftLower; i++)
    printf("%c", word[i]);
  // mid
  if (n % 2 == 1)
    printf("%c", word[leftLower + 1]);
  // left reflected
  for (long i = leftLower; i >= 0; i--)
    printf("%c", word[i]);
  printf("\n");
  return;
}

bool eval9Only(char *word) {
  long n = strlen(word);
  for (long i = 0; i < n; i++)
    if (word[i] != '9')
      return false;
  return true;
}
void print9OnlySolution(char *word) {
  long n = strlen(word);
  printf("%c", '1');
  for (long i = 0; i < n - 1; i++)
    printf("%c", '0');
  printf("%c\n", '1');
  return;
}

int main() {
  char word[1'000'001];
  long extra = 0;
  int t = 0;
  scanf("%d", &t);
  while (t--) {
    scanf("%s", word);
    if (eval9Only(word)) {
      print9OnlySolution(word);
      continue;
    }
    extra = getExtra(word);
    if (evalIsPalindrome(word)) {
      extra = 1;
      // printf("Is Palindrome ");
    }
    addExtra(word, extra);
    print(word);
  }
  return 0;
}