#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

void run()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> temp(n);
    for (int i = 0; i < n; i++)
        cin >> temp[i];

    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
    }

    // do DFS and keep track of temperatures along legs of m critical points
    // if tempereature difference is ok, mark the root of the leg as starting point
    stack<int> s;
    s.push(0);
    vector<int> leg;
    multiset<int> t;
    map<int, bool> visited;
    int last_index = -1;
    vector<bool> starting_point(n);

    while (!s.empty())
    {
        int cur = s.top();
        if (visited[cur])
        {
            s.pop();
            t.erase(t.find(temp[cur]));
            if (last_index - m >= 0)
                t.insert(temp[leg[last_index - m]]);
            leg.pop_back();
            last_index--;
            continue;
        }
        visited[cur] = true;
        leg.push_back(cur);
        last_index++;
        t.insert(temp[cur]);
        if (t.size() > m)
            t.erase(t.find(temp[leg[last_index - m]]));

        // check for temperature diff
        if (t.size() >= m && abs(*(--t.end()) - *t.begin()) <= k)
            starting_point[leg[last_index - m + 1]] = true;

        // push children
        for (auto c : tree[cur])
            s.push(c);
    }

    bool possible = false;
    for (int i = 0; i < n; i++)
    {
        if (starting_point[i])
        {
            possible = true;
            cout << i << " ";
        }
    }
    if (!possible)
        cout << "Abort mission";
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
