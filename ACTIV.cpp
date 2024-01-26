/*
ACTIV - Activities
https://www.spoj.com/problems/ACTIV/

DP approach
Options: pick activity or not
Return: total possibilities (non empty), which is sum of:
 all following non empty sets if current activity was picked
 + all non empty sets if not picked
 + 1 if the following is empty set

Inductive function:
f(activity_i) = 1 + f(next(activity_i)) + f(activity_(i+1))
f(activity_i) = 0 if i > N (no more activities == empty set)

next(activity_i) :=
  find next next activity_j with activity_j.start >= activity_i.end

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

int N;
i32 S, E;
struct ClassActiv {
  i32 start;
  i32 end;
  bool operator<(ClassActiv b) { return start < b.start; }
  bool operator<(i32 key) { return start < key; }
};
std::vector<ClassActiv> classes;
i32 memo[100'000];
const i32 M = (i32)1e8;

i32 next_class(i32 idx) {
  auto key = classes.at(idx).end;
  auto lb = std::lower_bound(classes.begin() + idx, classes.end() - 1, key);
  // left is < key
  if (lb->start < key)
    return N;
  return lb - classes.begin();
}
i32 f(i32 idx) {
  if (idx == N)
    return 0;
  if (memo[idx] != -1)
    return memo[idx];
  auto temp = (f(next_class(idx)) + (1 + f(idx + 1) % M)) % M;
  memo[idx] = temp;
  return temp;
}

void solve() {
  for (i32 i = 0; i < N; i++)
    memo[i] = -1;
  f(0);
}

int main() {
  while (scanf("%d", &N) != EOF) {
    if (N == -1)
      break;
    classes.clear();
    for (int i = 0; i < N; i++)
      scanf("%ld %ld", &S, &E), classes.push_back({S, E});
    std::sort(classes.begin(), classes.end());
    solve();
    printf("%08ld\n", (memo[0]) % M);
  }
  return 0;
}