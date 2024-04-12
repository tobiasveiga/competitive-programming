/*
DISUBSTR - Distinct Substrings
https://www.spoj.com/problems/DISUBSTR/

Explanation:
- Uses the trie data structure
- Adds each substring to the trie and counts the number of tree nodes

ACCEPTED
*/
#include <stdio.h>
#include <string.h>
#include <unordered_map>

long T, ans;
char word[1001];
std::unordered_map<char, long> t[500'501]; // N * (N+1) / 2 + 1 (root)

void solve() {
  auto n = strlen(word);
  long cnt = 0;
  for (long i = 0; i < n; i++) {
    long curr = 0;
    for (long j = i; j < n; j++) {
      if (t[curr].find(word[j]) == t[curr].end())
        t[curr][word[j]] = cnt + 1, cnt++;
      curr = t[curr][word[j]];
    }
  }
  ans = cnt;
  for (long i = 0; i <= cnt; i++)
    t[i].clear();
  return;
}

int main() {
  scanf("%ld", &T);
  while (T--) {
    scanf("%s", word);
    solve();
    printf("%ld\n", ans);
  }
}