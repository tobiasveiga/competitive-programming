/*
PARTY - Party Schedule
https://www.spoj.com/problems/PARTY/

Explanation:
- Top down recursive DP solution
- DP works as following
- Given the P parties in any order,
- Iterate over P, at each iteration at a party p, decide:
- Skip p or Keep P?
- If p is skipped, total_fee remains and move to next party
- If p is kept, total_fee is updated fee[p] and move to next party
- Take the max fun min cost of the two options

ACCEPTED
*/
#include <iostream>
#define i32 long

i32 max_budget, n_parties;
bool taken[501][100];
struct PartySet {
  i32 fee;
  i32 fun;
};
PartySet party[100], memo[501][100], optimal;

void reset() {
  for (i32 i = 0; i <= max_budget; i++)
    for (i32 j = 0; j < n_parties; j++)
      memo[i][j].fee = -1;
}

bool get_a_gt_b(PartySet a, PartySet b) {
  if (a.fun == b.fun)
    return a.fee < b.fee;
  else
    return a.fun > b.fun;
}

PartySet get(i32 total_fee, i32 idx) {
  if (idx == n_parties)
    return {total_fee, 0};

  auto memo_curr = &(memo[total_fee][idx]);

  if (memo_curr->fee != -1)
    return *memo_curr;

  auto case_skip = get(total_fee, idx + 1);
  *memo_curr = case_skip;
  if (total_fee + party[idx].fee > max_budget) {
    taken[total_fee][idx] = false;
    return *memo_curr;
  }

  auto case_keep = get(total_fee + party[idx].fee, idx + 1);
  case_keep.fun += party[idx].fun;
  if (get_a_gt_b(case_keep, case_skip)) {
    *memo_curr = case_keep;
    taken[total_fee][idx] = true;
  }
  return *memo_curr;
}

void solve() { optimal = get(0, 0); }

void show_solution() {
  std::cout << "\n";
  i32 f = 0;
  for (i32 i = 0; i < n_parties; i++) {
    std::cout << "MEMO " << f << " " << memo[f][i].fee << " " << memo[f][i].fun
              << "\n";
    if (taken[f][i]) {
      f += party[i].fee;
      std::cout << "X " << party[i].fee << " " << party[i].fun << "\n";
      continue;
    }
    std::cout << "O " << party[i].fee << " " << party[i].fun << "\n";
  }
  std::cout << "\n";
}

int main() {
  while (true) {
    std::cin >> max_budget >> n_parties;
    if (max_budget == 0 && n_parties == 0)
      break;
    for (i32 i = 0; i < n_parties; i++)
      std::cin >> party[i].fee >> party[i].fun;
    reset();
    solve();
    // show_solution();
    std::cout << optimal.fee << " " << optimal.fun << "\n";
  }
  return 0;
}