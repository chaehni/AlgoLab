#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

int recurse(vector<vector<int>> &trans, vector<int> &cost, vector<vector<int>> &memo, int pos, bool parent)
{

    if (parent)
        if (memo[0][pos] != -1)
            return memo[0][pos];
    if (!parent)
        if (memo[1][pos] != -1)
            return memo[1][pos];

    // precalc some values
    int sumRoot = cost[pos];
    for (int child : trans[pos])
        sumRoot += recurse(trans, cost, memo, child, true);

    int sumNotRoot = 0;
    for (int child : trans[pos])
        sumNotRoot += recurse(trans, cost, memo, child, false);

    int res = INT32_MAX;
    // case 1: parent covered
    if (parent)
    {
        res = min(sumRoot, sumNotRoot);
    }
    // case 2: parent not covered
    else
    {
        int c_min = INT32_MAX;
        for (int child : trans[pos])
        {
            int c = cost[child];
            for (int grand_child : trans[child])
                c += recurse(trans, cost, memo, grand_child, true);

            c += sumNotRoot - recurse(trans, cost, memo, child, false);

            c_min = min(c_min, c);
        }
        res = res = min(sumRoot, c_min);
    }

    if (parent)
        memo[0][pos] = res;
    else
        memo[1][pos] = res;

    return res;
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

    vector<vector<int>> memo(2, vector<int>(n, -1));

    cout << recurse(trans, cost, memo, 0, false) << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
