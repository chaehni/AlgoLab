#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

long max_score(vector<vector<pair<int, int>>> &canals, int pos, long moves, vector<vector<long>> &memo)
{
    // if we have no moves left
    if (moves == 0)
        return 0;

    if (memo[pos][moves] != -1)
        return memo[pos][moves];

    // if we are at a leaf, go back to 0
    if (canals[pos].size() == 0)
        return max_score(canals, 0, moves, memo);

    // for every canal, take it and record max score
    long best = 0;
    for (auto c : canals[pos])
        best = max(best, c.second + max_score(canals, c.first, moves - 1, memo));

    memo[pos][moves] = best;
    return best;
}

void run()
{
    int N, M, K;
    long X;
    cin >> N >> M >> X >> K;

    // for each hole keep a list of all the canals usable from there: pair (dest, points)
    vector<vector<pair<int, int>>> canals(N);
    map<pair<int, int>, int> canal_map;
    for (int i = 0; i < M; i++)
    {
        int u, v, p;
        cin >> u >> v >> p;
        canals[u].push_back({v, p});
    }

    vector<vector<long>> memo(N, vector<long>(K + 1, -1)); // maps position p and moves m to the max amount of points one can score with m moves from point p
    assert(K > 0);

    long m = max_score(canals, 0, K, memo);

    if (m < X)
    {
        cout << "Impossible\n";
        return;
    }

    // use binary search to find smallest number of moves, such that score is >= X
    int l = 1;
    int r = K;

    while (l != r)
    {
        int m = (l + r) / 2;
        if (max_score(canals, 0, m, memo) < X)
            l = m + 1;
        else
            r = m;
    }

    cout << l << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
    {
        run();
    }
}