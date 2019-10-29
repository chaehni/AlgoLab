#include <iostream>
#include <vector>

using namespace std;

int play(vector<int> &coins, vector<vector<int>> &memo, int l, int r, int player, int k, int m)
{

    if (memo[l][r] != -1)
        return memo[l][r];

    int ret;

    if (player == k) // player can get a coin
    {
        if (l == r)
            ret = coins[l];
        else
            ret = max(coins[l] + play(coins, memo, l + 1, r, (player + 1) % m, k, m), coins[r] + play(coins, memo, l, r - 1, (player + 1) % m, k, m));
    }
    else // player doesn't get a coin
    {
        if (l == r)
            ret = 0;
        else
            ret = min(play(coins, memo, l + 1, r, (player + 1) % m, k, m), play(coins, memo, l, r - 1, (player + 1) % m, k, m));
    }
    memo[l][r] = ret;
    return ret;
}

void run()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];

    // memotable
    vector<vector<int>> memo(n, vector<int>(n, -1));
    cout << play(coins, memo, 0, n - 1, 0, k, m) << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
