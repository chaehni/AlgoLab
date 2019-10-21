#include <iostream>
#include <vector>
#include <map>

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;

    vector<int> target(m);
    for (int i = 0; i < m; i++)
        cin >> target[i];

    vector<vector<int>> switches(n, vector<int>(2 * m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2 * m; j++)
            cin >> switches[i][j];

    // split & list to try all combinations of swicht flips
    // 0 -> not flipped, 1 -> flipped
    map<vector<int>, int> memo; // maps lights in room to min number of flips to get this configuration
    for (long i = 0; i < 1 << n / 2; i++)
    {
        vector<int> rooms(m, 0);
        int flipped = 0;
        for (int b = 0; b < n / 2; b++)
        {
            bool flip = i & (1 << b);
            if (flip)
                flipped++;

            // add lights corresponding to this switch to rooms
            for (int l = 0; l < m; l++)
                rooms[l] += (!flip ? switches[b][2 * l] : switches[b][2 * l + 1]);
        }

        // update map for given config
        auto it = memo.find(rooms);
        if (it == memo.end())
            memo[rooms] = flipped;
        else
            memo[rooms] = min(memo[rooms], flipped);
    }

    int min_flips = INT32_MAX;
    bool possible = false;
    for (long i = 0; i < 1 << n - (n / 2); i++)
    {
        vector<int> rest(target);
        int flipped = 0;
        for (int b = 0; b < n - (n / 2); b++)
        {
            bool flip = i & (1 << b);
            if (flip)
                flipped++;

            // add lights corresponding to this switch to rooms
            for (int l = 0; l < m; l++)
                rest[l] -= (!flip ? switches[n / 2 + b][2 * l] : switches[n / 2 + b][2 * l + 1]);
        }

        // find missing piece in map
        auto it = memo.find(rest);
        if (it != memo.end())
        {
            min_flips = min(min_flips, memo[rest] + flipped);
            possible = true;
        }
    }

    if (!possible)
        cout << "impossible\n";
    else
        cout << min_flips << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
