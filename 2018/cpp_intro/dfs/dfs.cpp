#include <iostream>
#include <stack>
#include <list>
#include <climits>
#include <vector>

using namespace std;

void run()
{   
    int n; cin >> n;
    int m; cin >> m;
    int v; cin >> v;

    //read all edges
    list<pair<int, int>> l;
    for (int i = 0; i < m; i++){
        int a;
        int b;
        cin >> a >> b;
        l.push_back(make_pair(a, b));
    }
    
    //DFS algorithm
    stack<int> s;
    vector<int> visited(n);
    vector<int> discovered(n, -1);
    vector<int> finished(n, -1);

    int time = 0;
    s.push(v);
    visited[v] = 1;
    discovered[v] = time++;
    while (!s.empty()){
        int min = INT_MAX;
        int top = s.top();
        for (auto e: l){
            if (e.first == top || e.second == top){
                //is it the smallest edge?
                if ((e.first == top && e.second < min && !visited[e.second]) ||
                    (e.second == top && e.first < min && !visited[e.first])){
                        min = (e.first == top ? e.second : e.first);
                }
            }
        }
        if (min == INT_MAX){ //no node found
            finished[s.top()] = time++;
            s.pop();
        } else {
            s.push(min);
            visited[min] = 1;
            discovered[min] = time++;
        }
    }

    for(auto e: discovered){
        cout << e << " ";
    }
    cout << "\n";
    for(auto e: finished){
        cout << e << " ";
    }
    cout << "\n";
}

int main()
{
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        run();
    }
}
