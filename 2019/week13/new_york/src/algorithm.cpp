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
    vector<int> safe;
    int last_index = -1;

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
            safe.push_back(leg[last_index - m + 1]);

        // push children
        for (auto c : tree[cur])
            s.push(c);
    }

    // sort points
    sort(safe.begin(), safe.end());

    // output
    if (safe.size() == 0)
    {
        cout << "Abort mission\n";
    }
    else
    {
        cout << safe[0] << " ";
        for (int i = 1; i < safe.size(); i++)
            if (safe[i] != safe[i - 1])
                cout << safe[i] << " ";
        cout << "\n";
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
