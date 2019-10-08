#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

int recurse(vector<vector<int>> &trans, vector<int> &cost, vector<int> &memo, int pos)
{

    if (memo[pos] != -1)
        return memo[pos];

    // cout << "entering with pos: " << pos << endl;
    // if endpoint, return cost for that city
    if (trans[pos].size() == 0)
        return 0;

    // case 1: taking root
    int sumRoot = cost[pos];
    for (int child : trans[pos])
    {
        sumRoot += recurse(trans, cost, memo, child);
    }

    // case 2: not taking root
    int sumNotRoot = INT32_MAX;
    for (int child : trans[pos])
    {
        int c = cost[child];
        for (int grand_child : trans[child])
        {
            if (trans[grand_child].size() == 0)
                c += cost[grand_child];
            else
                c += recurse(trans, cost, memo, grand_child);
        }

        for (int sibling : trans[pos])
        {
            if (sibling != child)
            {
                if (trans[sibling].size() == 0)
                    c += cost[sibling];
                else
                    c += recurse(trans, cost, memo, sibling);
            }
        }
        sumNotRoot = min(sumNotRoot, c);
    }

    // case 2: not taking root
    int sumNotChild = INT32_MAX;
    for (int child : trans[pos])
    {
        for (int grand_child : trans[child])
        {
            int c = cost[grand_child];
            for (int grand_grand_child : trans[grand_child])
            {
                if (trans[grand_grand_child].size() == 0)
                    c += cost[grand_grand_child];
                else
                    c += recurse(trans, cost, memo, grand_grand_child);
            }

            for (int grand_sibling : trans[child])
            {
                if (grand_sibling != grand_child)
                {
                    if (trans[grand_sibling].size() == 0)
                        c += cost[grand_sibling];
                    else
                        c += recurse(trans, cost, memo, grand_sibling);
                }
            }

            for (int child2 : trans[pos])
            {
                if (child2 != child)
                {
                    if (trans[child2].size() == 0)
                        c += cost[child2];
                    else
                        c += recurse(trans, cost, memo, child2);
                }
            }
            sumNotChild = min(sumNotChild, c);
        }
    }

    //  cout << "returnigng for node " << pos << ": " << sumRoot << " " << sumNotRoot << endl;
    memo[pos] = min(sumNotChild, min(sumRoot, sumNotRoot));
    return min(sumNotChild, min(sumRoot, sumNotRoot));
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

    cout << recurse(trans, cost, memo, 0) << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
