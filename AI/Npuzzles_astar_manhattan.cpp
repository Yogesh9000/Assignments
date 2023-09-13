#include <bits/stdc++.h>

using namespace std;

template<typename T>
using matrix = vector<vector<T>>;

template<typename T>
using container = vector<matrix<T>>;

long long move_count = 0;

pair<int,int> find_num(const matrix<int>& curr, int puzzle_size, int target) {
  for(int i=0; i<puzzle_size; i++) {
    for(int j=0; j<puzzle_size; j++) {
      if(curr[i][j] == target)
        return {i,j};
    }
  }
  return {-1,-1};
}

bool is_safe(int x, int y, int puzzle_size) {
  return (x>=0 && x<puzzle_size && y>=0 && y<puzzle_size);
}

vector<matrix<int>> Expand(const matrix<int> &curr, int puzzle_size) {
  pair<int,int> loc = find_num(curr,puzzle_size,0);
  vector<matrix<int>> next;
  if (is_safe(loc.first-1, loc.second,puzzle_size)) {
    matrix<int> a = curr;
    swap(a[loc.first][loc.second],a[loc.first-1][loc.second]);
    next.push_back(a);
  }
  if (is_safe(loc.first+1, loc.second,puzzle_size)) {
    matrix<int> a = curr;
    swap(a[loc.first][loc.second],a[loc.first+1][loc.second]);
    next.push_back(a);
  }
  if (is_safe(loc.first, loc.second-1,puzzle_size)) {
    matrix<int> a = curr;
    swap(a[loc.first][loc.second],a[loc.first][loc.second-1]);
    next.push_back(a);
  }
  if (is_safe(loc.first, loc.second+1,puzzle_size)) {
    matrix<int> a = curr;
    swap(a[loc.first][loc.second],a[loc.first][loc.second+1]);
    next.push_back(a);
  }
  return next;
}

int manhattan(matrix<int> &curr, matrix<int> &goal, int target) {
  pair<int,int> c = find_num(curr,(int)curr.size(),target);
  pair<int,int> g = find_num(goal,(int)curr.size(),target);
  int mh=0;
  if(c.first == g.first) {
    mh = 2 + abs(c.second-g.second);
  }
  else if (c.second == g.second) {
    mh = 2 + abs(c.first-g.first);
  }
  else {
    mh = abs(c.first-g.first)+abs(c.second-g.second);
  }
  return mh;
}

int h(matrix<int> &curr, matrix<int> &goal) {
  int hr = 0;
  for(size_t i=0; i<curr.size(); i++) {
    for(size_t j=0; j<curr.size(); j++) {
      if(curr[i][j] != goal[i][j]) {
        hr += manhattan(curr,goal,curr[i][j]);
      }
    }
  }
  return hr;
}

container<int> Astar(matrix<int> &start, matrix<int> &goal, int puzzle_size) {
  priority_queue<pair<int,pair<matrix<int>,int>>, vector<pair<int,pair<matrix<int>,int>>>, greater<pair<int,pair<matrix<int>,int>>>> p;
  map<matrix<int>,bool> seen;
  container<int> ans;
  int t = h(start, goal);
  p.push({t,{start,0}});
  while (!p.empty()) {
    move_count++;
    auto curr = p.top();
    p.pop();
    if(seen[curr.second.first])
      continue;
    seen[curr.second.first] = true;
    ans.push_back(curr.second.first);
    if(curr.second.first == goal)
      return ans;
    else {
      for(auto i: Expand(curr.second.first,puzzle_size)) {
        int f = h(i,goal) + curr.second.second;
        p.push({f,{i,curr.second.second+1}});
      }
    }
  }
  return {};
}

int main() {
  ifstream in("in.txt");
  ofstream out("out.txt");
  matrix<int> start;
  matrix<int> goal;

  int puzzle_size;
  in>>puzzle_size;

  for (int i=0; i<puzzle_size; i++) {
    vector<int> temp;
    for (int j=0; j<puzzle_size; j++) {
      int t;in>>t;
      temp.push_back(t);
    }
    start.push_back(temp);
  }

  for (int i=0; i<puzzle_size; i++) {
    vector<int> temp;
    for (int j=0; j<puzzle_size; j++) {
      int t;in>>t;
      temp.push_back(t);
    }
    goal.push_back(temp);
  }
  auto beg = chrono::high_resolution_clock::now();
  auto ans = Astar(start, goal,puzzle_size);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end-beg);
  for(auto i: ans) {
    for(auto j: i) {
      for(auto k: j) {
        out<<k<<" ";
      }
      out<<"\n";
    }
    out<<"***********************\n";
  }

  out<<"\nmove count: "<<move_count<<"\n";
  out<<"time: "<<duration.count()<<"\n";
  return 0;
}
