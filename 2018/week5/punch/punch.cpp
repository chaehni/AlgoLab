#include <iostream>
#include <vector>

using namespace std;

pair<int, int> compare(const pair<int, int> e1, const pair<int, int> e2)
{
    if (e1.first < e2.first)
        return e1;
    if (e2.first < e1.first)
        return e2;
    if (e1.second > e2.second)
        return e1;
    return e2;
}

void run()
{
    int n, k;
    cin >> n >> k;

    const int inf = INT32_MAX; // worst case: every beverage costs 10^4 and is one liter only (cannot use INT32_MAX because we add to it and it would overflow)

    // read drinks
    vector<int> cost(n);
    vector<int> vol(n);
    for (int i = 0; i < n; i++)
        cin >> cost[i] >> vol[i];

    // DP table n*k, for every entry i,j store the minimum cost to get at least i liters with the first j beverages and also the number of beverages used for the punch
    vector<vector<pair<int, int>>> table(k + 1, vector<pair<int, int>>(n));

    // fill the table
    for (int i = 1; i < k + 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // we have 3 options:
            // * don't take the jth beverage and use just beverages 0 to j-1
            // * we take  beverage j and one unit is enough to get i liters
            // * we take  beverage j and one unit is not enough to get i liters, cover the rest with beverages 0 to j
            // in the end, compare options and choose best

            pair<int, int> o1 = (j != 0 ? table[i][j - 1] : make_pair(inf, 0));                                                               // take same as before
            pair<int, int> o2 = (i - vol[j] <= 0 ? make_pair(cost[j], 1) : make_pair(inf, 0));                                                // take one of current drink                                                                                                                                                                                                  // take one of j and fill up rest with drinks 0 to j-1
            pair<int, int> o3 = (i - vol[j] > 0 ? make_pair(table[i - vol[j]][j].first + cost[j],                                             // take one of j and fill up rest with drinks 0 to j
                                                            table[i - vol[j]][j].second + (table[i - vol[j]][j] == table[i - vol[j]][j - 1])) // if we took the value from the left, this is the first time we take drink j -> add one to second
                                                : make_pair(inf, 0));

            table[i][j] = compare(compare(o1, o2), o3);
        }
    }
    cout << table[k][n - 1].first << " " << table[k][n - 1].second << "\n";
}

int main()
{
    int n;
    cin >> n;
    while (n--)
        run();
}