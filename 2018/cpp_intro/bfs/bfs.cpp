#include <iostream>
#include <queue>
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
    
    //BFS algorithm
    queue<int> q;
    vector<int> visited(n);
    vector<int> distance(n, -1);

    q.push(v);
    visited[v] = 1;
    distance[v] = 0;
    while (!q.empty()){
        int min = INT_MAX;
        int front = q.front();
        for (auto e: l){
            if (e.first == front || e.second == front){
                //is it the smallest edge?
                if ((e.first == front && e.second < min && !visited[e.second]) ||
                    (e.second == front && e.first < min && !visited[e.first])){
                        min = (e.first == front ? e.second : e.first);
                }
            }
        }
        if (min == INT_MAX){ //no node found
            q.pop();
        } else {
            q.push(min);
            visited[min] = 1;
            distance[min] = distance[front] + 1;
        }
    }

    for(auto e: distance){
        cout << e << " ";
    }
    cout << "\n";
}

int main()
{
    int n_tests;
    cin >> n_tests;
    while(n_tests--){run();}
}
