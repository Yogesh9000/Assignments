#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> UCS(vector<vector<pair<int,int>>> &graph, int start, int goal) {
  vector<pair<int,int>> ans;
  set<pair<int,int>> s;
  map<int,bool> m;
  s.insert({start,0});
  while(!s.empty()) {
    auto curr = *(s.begin());
    if(!m[curr.second]) {
      m[curr.second] = true;
      ans.push_back(curr);
      if(curr.second == goal) {
        return ans;
      }
      else {
        for (size_t i=0; i<graph[curr.second].size(); i++) {
          s.insert({graph[curr.second][i].first+curr.first, graph[curr.second][i].second});
        }
      }
      s.erase(s.begin());
    }
  }
  ans.clear();
  return ans;
}

int main() {
  return 0;
}
