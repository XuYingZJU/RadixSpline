#include <iostream>

#include "include/rs/multi_map.h"

using namespace std;

void RadixSplineExample() {
  int findkey = 99999;
  // Create random keys.
  vector<uint64_t> keys(1e4);
  generate(keys.begin(), keys.end(), rand);
  keys.push_back(findkey-1);
  sort(keys.begin(), keys.end());

  // Build RadixSpline.
  uint64_t min = keys.front();
  uint64_t max = keys.back();
  rs::Builder<uint64_t> rsb(min, max);
  for (const auto& key : keys) rsb.AddKey(key);
  rs::RadixSpline<uint64_t> rs = rsb.Finalize();

  // Search using RadixSpline.
  rs::SearchBound bound = rs.GetSearchBound(findkey);
  cout << "The search key is in the range: [" << bound.begin << ", "
       << bound.end << ")" << endl;
  auto start = begin(keys) + bound.begin, last = begin(keys) + bound.end;
  // std::lower_bound() 区间内第一个大于等于value的值的位置，没找到就返回end()
  int pos = std::lower_bound(start, last, findkey) - begin(keys);
  cout << "The key is at position: " << pos << endl;
  cout << "CHECK " << keys[pos] << endl;
  cout << "The number of elems: " << keys.size() << endl;
  cout << "The number of points: " << rs.GetSplinePointsVecSize() << endl;
}

void MultiMapExample() {
  vector<pair<uint64_t, char>> data = {{1ull, 'a'},
                                       {12ull, 'b'},
                                       {7ull, 'c'},  // Unsorted.
                                       {42ull, 'd'}};
  rs::MultiMap<uint64_t, char> map(begin(data), end(data));

  cout << "find(7): '" << map.find(7)->second << "'" << endl;
  cout << "lower_bound(3): '" << map.lower_bound(3)->second << "'" << endl;
}

int main(int argc, char** argv) {
  RadixSplineExample();
  MultiMapExample();

  return 0;
}
