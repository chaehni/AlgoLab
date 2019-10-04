#include <iostream>
#include <vector>

using namespace std;

void run()
{
    int n;
    cin >> n;
    vector<int> coins(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];

    // two tables, one where I go first, other where they go first
    vector<vector<int>> first(n, vector<int>(n, 0));  // max I can get when going first
    vector<vector<int>> second(n, vector<int>(n, 0)); // max I can get when going second

    //init first with values of coins on diagonal
    for (int i = 0; i < n; i++)
        first[i][i] = coins[i];

    // iterate over tables in diagonal fashion and fill in values
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int ind_i = j;
            int ind_j = j - i;

            first[ind_i][ind_j] = max(coins[ind_i] + second[ind_i - 1][ind_j], coins[ind_j] + second[ind_i][ind_j + 1]);
            second[ind_i][ind_j] = min(first[ind_i - 1][ind_j], first[ind_i][ind_j + 1]);
        }
    }

    cout << first[n - 1][0] << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}