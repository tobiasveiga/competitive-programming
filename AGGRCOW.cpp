/*
AGGRCOW - Aggressive cows
https://www.spoj.com/problems/AGGRCOW/
ACCEPTED
*/
#include <algorithm> // sort
#include <iostream>
using namespace std;

int t, n, c;
int32_t stalls[100'000]; // max signed 32bit int is 2e9

bool getIsAcceptableDistance(int distance) {
  int prevCowPosition = stalls[0];
  int nCows = 1;
  for (int i = 1; i < n; i++) {
    int prevCowDistance = stalls[i] - prevCowPosition;
    if (prevCowDistance >= distance) {
      nCows += 1;
      prevCowPosition = stalls[i];
    }
    if (nCows == c)
      return true;
  }
  return false;
}

int getLargestMinimumDistance(int l, int u) {
  int mid, remainder;
  while (l < u) {
    remainder = ((l + u) % 2 == 0 ? 0 : 1);
    mid = (l + u) / 2 + remainder;
    if (getIsAcceptableDistance(mid)) {
      l = mid;
    } else
      u = mid - 1;
  }
  return u; // could be l, does not matter
}

int main() {

  cin >> t;
  while (t--) {
    cin >> n >> c;
    for (int i = 0; i < n; i++)
      cin >> stalls[i];

    sort(stalls, stalls + n);
    cout << getLargestMinimumDistance(0, stalls[n - 1]) << endl;
  }
  return 0;
}