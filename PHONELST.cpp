/*
PHONELST - Phone List
https://www.spoj.com/problems/PHONELST/

Explanation:
- After reading all numbers, try adding each number to a Trie
- The last char points to a end of string
- If during insertion a end of string is found, then list is not consitent,
since there was a previous number which is a substring of the current one
- Also if after insertion, no new char was added to the Trie, then the list is
not consistent, since the current string must be a substring of a previous added
string
- Otherwise the list is consistent (success).

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

const i32 N = 110'001; // max expected characters in total with \0 + 1
int t, n;
i32 c[N][10]; // tree represented as child array
bool str_end[N];
std::string input[10'000];

i32 cnt;
bool success;

void insert(std::string num) {
  success = false;
  i32 node = 0;
  i32 before = cnt;
  for (auto d : num) {
    if (str_end[node]) // reached end of another string
      return;
    if (c[node][d - '0'] == 0)
      c[node][d - '0'] = ++cnt;
    node = c[node][d - '0'];
  }
  if (cnt == before) // word is not an increment
    return;
  str_end[node] = true; // add end of string
  success = true;
  return;
}

void solve() {
  success = true;
  for (i32 i = 0; i < n; i++) {
    insert(input[i]);
    if (!success)
      break;
  }
}

int main() {
  std::cin >> t;
  while (t--) {
    std::cin >> n;
    cnt = 0;
    memset(str_end, 0, sizeof(bool) * (n * 10 + 1));
    memset(c, 0, sizeof(i32) * (n * 10 + 1) * 10);
    for (i32 i = 0; i < n; i++)
      std::cin >> input[i];
    solve();
    printf("%s\n", (success ? "YES" : "NO"));
  }
}