/*
STPAR - Street Parade
https://www.spoj.com/problems/STPAR/

Explanation:
- Uses a stack to simulated the side street
- At each iteration expects a number in ascending order starting from 1, and
check if the expected number is in the main street or side street
- If the number is not next in the main street nor in the side street, stack
main street number into side street
- If the number is next in the main street update current number and update
pointer in the main street
- If the number is next in the side street update current number and unstack
side street number

ACCEPTED
*/
#include <stdio.h>

int n, input[1'000];
struct Stack {
  int arr[1'000];
  int size = 0;
  bool empty() { return size == 0; }
  void clear() { size = 0; }
  int top() { return arr[size - 1]; }
  void pop() { size--; }
  void push(int i) { arr[size++] = i; }
} stack;
bool success;

void solve() {
  success = false;
  int expected = 1;
  int i = 0;
  // Iterate over main street values
  while (i < n) {
    if (!stack.empty() && stack.top() == expected) {
      // printf("Stack  matches %d\n", expected);
      stack.pop();
      expected++;
    } else if (input[i] != expected) {
      // printf("Main and Stack does not matches %d\n", expected);
      stack.push(input[i]);
      i++;
    } else {
      // printf("Main matches %d\n", expected);
      expected++;
      i++;
    }
  }
  // Unstack what is left in the side street
  while (!stack.empty() && stack.top() == expected) {
    stack.pop();
    expected++;
  }
  if (expected == n + 1)
    success = true;
}

int main() {
  while (true) {
    scanf("%d", &n);
    if (n == 0)
      break;
    for (int i = 0; i < n; i++)
      scanf("%d", input + i);
    stack.clear();
    solve();
    printf(success ? "yes\n" : "no\n");
  }
  return 0;
}