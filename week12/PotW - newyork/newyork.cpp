#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>

using namespace std;

struct Point
{
    int index;
    int temp;
    vector<int> children;
};

void run()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<Point> points(n);
    vector<bool> root(n, true);
    vector<bool> starting_point(n, false);

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        points[i] = {i, t, vector<int>()};
    }
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        root[v] = false;
        points[u].children.push_back(v);
    }

    bool possible = false;
    // for every root node start a DFS
    for (int i = 0; i < n; i++)
    {
        if (!root[i])
            continue;

        stack<Point> s;
        s.push(points[i]);
        vector<int> indices; // over the full DFS it will contain all the branches of the tree
        map<int, bool> visited;
        multiset<int> temp_set; // stores the last m temperatures in ordered fashion so we can compute difference using first and last element
        int oldest_temp;

        while (!s.empty())
        {

            Point current = s.top();

            // if we've seen this point already it means we have handled all its children -> undo this node
            if (visited[current.index])
            {
                s.pop();
                indices.pop_back();
                temp_set.erase(temp_set.find(current.temp));

                // we removed current temperature, we need to restore the one dropped by current node
                if (indices.size() >= m)
                    temp_set.insert(points[indices[indices.size() - m]].temp);

                continue;
            }

            // this node is new, push its index to the vector and update temps
            indices.push_back(current.index);

            // if we already have m temperatures, the oldest needs to go
            if (temp_set.size() == m)
            {
                oldest_temp = points[indices[indices.size() - m - 1]].temp;
                temp_set.erase(temp_set.find(oldest_temp));
            }
            // add current temperature
            temp_set.insert(current.temp);

            //check if we can find a new starting point and then push children
            if (indices.size() >= m && abs(*temp_set.begin() - *(--temp_set.end())) <= k)
            {
                starting_point[indices[indices.size() - m]] = true;
                possible = true;
            }

            for (int c : current.children)
                s.push(points[c]);

            visited[current.index] = true;
        }
    }

    if (!possible)
    {
        cout << "Abort mission\n";
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (starting_point[i])
            cout << i << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}