#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

pair<int, int> recurse(vector<vector<int>> &trans, vector<int> &cost, vector<int> &memo, int pos)
{
    // if endpoint, return cost for that city
    if (trans[pos].size() == 0)
        return make_pair(cost[pos], 0);

    // case 1: taking root
    int sumRoot = cost[pos];
    for (int child : trans[pos])
    {
        auto p = recurse(trans, cost, memo, child);
        sumRoot += min(p.first, p.second);
    }

    // case 2: not taking root
    int sumNotRoot = INT32_MAX;
    for (int child : trans[pos])
    {
        // take this child
        auto p = recurse(trans, cost, memo, child);
        int c = p.first;
        // cout << "in: child cost is " << c << endl;
        // recurse on grand-children
        /* for (int grand_child : trans[child])
        {
            auto p = recurse(trans, cost, memo, grand_child);
            if (trans[grand_child].size() == 0)
                c += p.first;
            else
                c += min(p.first, p.second);
        } */

        // recurse on all siblings
        for (int sibling : trans[pos])
        {
            if (sibling != child)
            {
                auto p = recurse(trans, cost, memo, sibling);
                if (trans[sibling].size() == 0)
                    c += p.first;
                else
                    c += min(p.first, p.second);
            }
        }
        sumNotRoot = min(sumNotRoot, c);
    }

    cout << "returnigng for node " << pos << ": " << sumRoot << " " << sumNotRoot << endl;
    return make_pair(sumRoot, sumNotRoot);
}

void run()
{
    int n;
    cin >> n;

    vector<vector<int>> trans(n);
    for (int k = 0; k < n - 1; k++)
    {
        int i, j;
        cin >> i >> j;
        trans[i].push_back(j);
    }

    vector<int> cost(n);
    for (int i = 0; i < n; i++)
        cin >> cost[i];

    vector<int> memo(n, -1);

    auto p = recurse(trans, cost, memo, 0);
    cout << p.first << " " << p.second << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
