/*
ASSIGN - Assignments
https://www.spoj.com/problems/ASSIGN/

Explanation:
- DP top-down approach
- Each node of the recursion tree represents a topic assigned to a student
- We want the count of the leaves which are in a full assignment path.
- Memoization is applied to nodes that have the same equivalent ancestor path
from the root, which avoids repeating whole subtrees.
- An equivalent ancestor path means that the same set topics was taken before
- Implementation uses a state variable to store the set of assigned topics
as bits in an single integer

ACCEPTED
*/
#include <algorithm>
#include <iostream>
#include <math.h>
#define i32 long
#define i64 long long

i32 T, N, input[20][20];
i64 ans;
i64 memo[1'048'576]; // 2 ** 20 = 1048576 -> max pos =  1...1b

void reset() {
  for (i32 i = 0; i < pow(2, N); i++)
    memo[i] = -1;
  memo[(i32)pow(2, N) - 1] = 1; // 2**N - 1 = all topics assigned
}

bool eval_topic_taken(i32 state, i32 topic) {
  return ((state >> topic) & 1) == 1;
}
i32 include_topic(i32 state, i32 topic) { return state | (1 << topic); }

i64 assign_student(i32 student, i32 state) {
  if (memo[state] != -1)
    return memo[state];
  memo[state] = 0;
  for (i32 topic = 0; topic < N; topic++) {
    if (input[student][topic] == 1 && !eval_topic_taken(state, topic)) {
      auto new_state = include_topic(state, topic);
      memo[state] += assign_student(student + 1, new_state);
    }
  }
  return memo[state];
}
void solve() { ans = assign_student(0, 0); }
int main() {
  std::cin >> T;
  while (T--) {
    std::cin >> N;
    for (i32 i = 0; i < N; i++)
      for (i32 j = 0; j < N; j++)
        std::cin >> input[i][j];
    reset();
    solve();
    std::cout << ans << "\n";
  }
  return 0;
}