/*
ORDERSET - Order statistic set
https://www.spoj.com/problems/ORDERSET/

Explanation:
- Offline approach
- (Online approach would require implementing Self Balancing Binary Search Tree)
- Assume all values were already stored and sorted
- Each value has a position in the sorted array
- A map provides the map from value to position => num_pos
- A array provides the map from position to value => pos_num
- Use a Fenwick Tree (aka BIT) to solve the queries
- Values that were inserted have value 1, otherwise 0;
- A BIT query(position) provides the number of inserted elements up to the
position
- Count(x) becomes a matter of finding an equivalent position of x in the array
o values, which can be done computing the lowerbound of x in all values, then
using the lb position -1 to query the BIT. (-1 since strict less)
    >> Count(x) = BIT.query(lowerbound(x, all_values) - 1)
- K-th becomes a matter of finding the lowerbound of K in all the BIT.query()
values

ACCEPTED
*/
#include <map>
#include <stdio.h>
#define i32 long

const i32 N = 200'000; // Can't insert more than this
std::map<i32, i32> num_pos;
i32 pos_num[N];
i32 Q;
struct Instruction {
  char code;
  i32 value;
} instruction[200'000];

struct BIT {
  i32 n;
  i32 arr[N + 1];
  void update(i32 pos, i32 delta) {
    for (; pos < n; pos += (pos & -pos))
      arr[pos] += delta;
  }
  i32 query(i32 pos) {
    i32 sum = 0;
    for (; pos > 0; pos -= (pos & -pos))
      sum += arr[pos];
    return sum;
  }
  i32 get(i32 pos) {
    // if pos < 0, query(pos) returns 0;
    return query(pos) - query(pos - 1);
  }
  i32 lower_bound(i32 value) {
    i32 low = 0, high = n - 1;
    i32 mid = high / 2;
    for (; low < high; mid = (low + high) / 2)
      if (query(mid) < value)
        low = mid + 1;
      else
        high = mid;
    return low;
  }
} bit;

void build() {
  for (i32 i = 0; i < Q; i++)
    if (instruction[i].code == 'I')
      num_pos[instruction[i].value] = 0;
  i32 pos = 1;
  for (const auto &it : num_pos) {
    auto num = it.first;
    pos_num[pos] = num;
    num_pos[num] = pos;
    pos++;
  }
  bit.n = pos; // BIT skips the 0
  // bit starts initialized with 0s
}

void execute(char code, i32 value) {
  if (code == 'I') {
    if (bit.get(num_pos[value]) == 0)
      bit.update(num_pos[value], 1);
  } else if (code == 'D') {
    if (bit.get(num_pos[value]) == 1)
      bit.update(num_pos[value], -1);
  } else if (code == 'C') {
    i32 low = 0, high = bit.n - 1;
    i32 mid = high / 2;
    for (; low < high; mid = (low + high) / 2)
      if (pos_num[mid] < value) // lowerbound
        low = mid + 1;
      else
        high = mid;
    if (value > pos_num[bit.n - 1])
      low++;
    printf("%ld\n", bit.query(low - 1));
  } else {
    if (value > bit.query(bit.n - 1))
      printf("invalid\n");
    else
      printf("%ld\n", pos_num[bit.lower_bound(value)]);
  }
}

int main() {

  scanf("%ld", &Q);
  for (i32 i = 0; i < Q; i++)
    scanf(" %c %ld", &instruction[i].code, &instruction[i].value);
  // needed to specify that white space should be consumed before the %c

  build();

  for (i32 i = 0; i < Q; i++)
    execute(instruction[i].code, instruction[i].value);

  return 0;
}