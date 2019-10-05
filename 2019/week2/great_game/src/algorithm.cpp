#include <iostream>
#include <vector>

using namespace std;

// red = 0
// black = 1

int play(vector<vector<int>> &trans, vector<int> &min_memo, vector<int> &max_memo, int pos, bool even, int target)
{
    if (pos == target)
        return 0;

    if (even) // player wants to minimize
    {
        // check memo
        if (min_memo[pos] != -1)
            return min_memo[pos];

        int min_moves = INT32_MAX;
        // test all transitions
        for (int t : trans[pos])
        {
            min_moves = min(min_moves, 1 + play(trans, min_memo, max_memo, t, false, target));
        }
        min_memo[pos] = min_moves;
        return min_moves;
    }
    else // player wants to maximize
    {
        // check memo
        if (max_memo[pos] != -1)
            return max_memo[pos];

        int max_moves = 0;
        // test all 0
        for (int t : trans[pos])
        {
            max_moves = max(max_moves, 1 + play(trans, min_memo, max_memo, t, true, target));
        }
        max_memo[pos] = max_moves;
        return max_moves;
    }
}

void run()
{
    int n, m;
    cin >> n >> m;
    int r, b;
    cin >> r >> b;

    vector<vector<int>> trans(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        trans[u].push_back(v);
    }

    // memo tables
    vector<int> min_memo(n + 1, -1);
    vector<int> max_memo(n + 1, -1);

    int holmes = play(trans, min_memo, max_memo, r, true, n);
    int moriarty = play(trans, min_memo, max_memo, b, true, n);

    if (holmes < moriarty)
        cout << 0;
    if (holmes > moriarty)
        cout << 1;
    if (holmes == moriarty)
    {
        if (holmes % 2 == 1)
            cout << 0;
        if (holmes % 2 == 0)
            cout << 1;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
