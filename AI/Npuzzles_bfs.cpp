#include <bits/stdc++.h>

using namespace std;

template<typename T>
using matrix = vector<vector<T>>;

long long move_count = 0;

pair<int,int> find_zero(const matrix<int>& curr, int puzzle_size) {
  for(int i=0; i<puzzle_size; i++) {
    for(int j=0; j<puzzle_size; j++) {
      if(curr[i][j] == 0)
        return {i,j};
    }
  }
  return {-1,-1};
}

bool is_safe(int x, int y, int puzzle_size) {
  return (x>=0 && x<puzzle_size && y>=0 && y<puzzle_size);
}

vector<matrix<int>> Expand(const matrix<int> &curr, int puzzle_size) {
  pair<int,int> loc = find_zero(curr,puzzle_size);
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

vector<matrix<int>> DFS(const matrix<int> &start, const matrix<int> &goal, int puzzle_size) {
  queue<matrix<int>> q;
  map<matrix<int>,bool> seen;
  vector<matrix<int>> ans;
  q.push(start);
  while (!q.empty()) {
    move_count++;
    matrix<int> curr = q.front();
    q.pop();
    seen[curr] = true;
    ans.push_back(curr);
    if (curr==goal) {
      return ans;
    }
    else {
      for(auto i: Expand(curr,puzzle_size)) {
        if(!seen[i]) {
          q.push(i);
        }
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
  auto ans = DFS(start, goal,puzzle_size);
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
