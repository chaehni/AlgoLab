#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Drink
{
    int cost;
    int vol;
};

pair<int, int> compare(pair<int, int> p1, pair<int, int> p2)
{
    if (p1.first < p2.first)
        return p1;
    else if (p1.first == p2.first && p1.second > p2.second)
        return p1;
    else
        return p2;
}

void run()
{
    int n, k;
    cin >> n >> k;

    vector<Drink> bevs(n);
    for (int i = 0; i < n; i++)
    {
        Drink d;
        cin >> d.cost;
        cin >> d.vol;
        bevs[i] = d;
    }

    // DP with table k * n, entry (i, j) contains tuple with <min cost for i liters with first j drinks, max diversity>
    vector<vector<pair<int, int>>> table(k + 1, vector<pair<int, int>>(n, make_pair(-1, -1)));
    for (int i = 0; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // ege cases:
            // 1. row
            if (i == 0)
            {
                table[i][j] = make_pair(0, 0);
                continue;
            }
            // 1. column
            if (j == 0)
            {
                double bottles = ceil(double(i) / bevs[j].vol);
                table[i][j] = make_pair(bottles * bevs[j].cost, 1);
                continue;
            }

            // otherwise we have two options:
            // o1: take don't take current bottle -> use only 0 to j-1
            // o2: take current bootle -> take bottle, and fill remaining liters with bottles 0 to j

            // o1:
            pair<int, int> o1 = table[i][j - 1];

            // o2:
            pair<int, int> o2;
            int remaining = i - bevs[j].vol;

            // if one of new bottles is enough take only this:
            if (remaining <= 0)
                o2 = make_pair(bevs[j].cost, 1);
            // else we fill the rest
            else
                o2 = make_pair(bevs[j].cost + table[remaining][j].first,
                               (table[remaining][j] != table[remaining][j - 1] ? table[remaining][j].second : table[remaining][j].second + 1));

            table[i][j] = compare(o1, o2);
        }
    }

    cout << table[k][n - 1].first << " " << table[k][n - 1].second << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
