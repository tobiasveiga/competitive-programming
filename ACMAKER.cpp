/*
ACMAKER - ACM (ACronymMaker)
https://www.spoj.com/problems/ACMAKER/

DP approach
Option:
- select letter from string to fill current acr. character
- success if all letters from acr. are filled,
  AND only significant words were used
  AND all significant words were used
Therefore need to know which characters are from insignificant words -> just use
a boolean array
Need to know for which word each character belongs to -> use array of char idx
to word idx. Then whenever a char is picked, store the last word idx picked

f by priority:
f(idx_phrase, N_acr, N_word) = 1
f(N_phrase, idx_acr, idx_word) = 0
f(idx_phrase, N_acr, idx_word) = 0
f(idx_phrase, idx_acr, idx_word) = 0 if char2word[idx_phrase] > idx_word+1
  ^- checks if a word was skipped
f(idx_phrase, idx_acr, idx_word) =
    f(idx_phrase+1, idx_acr, idx_word)
    if char2word[idx_phrase] is invalid or characters do not match
f(idx_phrase, idx_acr, idx_word) =
    f(idx_phrase+1, idx_acr+1, char2word[idx_phrase])
    + f(idx_phrase+1, idx_acr, idx_word)

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

int n;
std::string i_word;
std::unordered_set<std::string> i_words;
std::string acr, phrase;
i32 char2word[150];
i32 n_words;

i32 memo[150][150][151];

char lower(char in) { return in - ('Z' - 'z'); }
i32 f(i32 idx_phrase, i32 idx_acr, i32 idx_word) {
  if (idx_acr == acr.size() && idx_word == n_words) {
    return 1;
  }
  if (idx_phrase == phrase.size())
    return 0;
  if (idx_acr == acr.size())
    return 0;
  if (char2word[idx_phrase] > (idx_word + 1))
    return 0; // missed a word

  if (memo[idx_phrase][idx_acr][idx_word] != -1)
    return memo[idx_phrase][idx_acr][idx_word];

  i32 temp = 0;
  if (phrase.at(idx_phrase) == lower(acr.at(idx_acr)) &&
      char2word[idx_phrase] != 0)
    temp += f(idx_phrase + 1, idx_acr + 1, char2word[idx_phrase]);
  temp += f(idx_phrase + 1, idx_acr, idx_word);

  memo[idx_phrase][idx_acr][idx_word] = temp;
  return temp;
}
void preprocess() {
  i32 curr = 1;
  memset(char2word, 0, phrase.size() * sizeof(i32));
  for (int i = 0, j = 0;; j++) {
    if (phrase.at(i) != ' ' && (j == phrase.size() || phrase.at(j) == ' ')) {
      if (i_words.find(phrase.substr(i, j - i)) == i_words.end()) {
        while (i < j)
          char2word[i++] = curr;
        curr++;
      } else {
        i = j;
      }
      if (j == phrase.size())
        break;
    }
    if (phrase.at(i) == ' ' && phrase.at(j) != ' ')
      i = j;
  }
  n_words = curr - 1;
  for (int i = 0; i < phrase.size(); i++)
    for (int j = 0; j < acr.size(); j++)
      for (int k = 0; k <= n_words; k++)
        memo[i][j][k] = -1;
}
int main() {
  while (scanf("%d", &n) != EOF) {
    if (n == 0)
      break;
    i_words.clear();
    for (int i = 0; i < n; i++)
      std::cin >> i_word, i_words.insert(i_word);
    while (true) {
      scanf(" ");
      std::cin >> acr;
      scanf(" ");
      std::getline(std::cin, phrase);
      if (acr == "LAST" && phrase == "CASE")
        break;
      preprocess();
      auto ans = f(0, 0, 0);
      if (ans > 0)
        printf("%s can be formed in %ld ways\n", acr.c_str(), ans);
      else
        printf("%s is not a valid abbreviation\n", acr.c_str());
    }
  }
}
