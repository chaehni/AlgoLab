#include <iostream>
#include <vector>

using namespace std;

void run()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> vals(n);
    vector<int> cum_vals(n);

    cin >> vals[0];
    cum_vals[0] = vals[0];
    for (int i = 1; i < n; i++)
    {
        int v;
        cin >> v;
        vals[i] = v;
        cum_vals[i] = cum_vals[i - 1] + v;
    }

    // segs[i] contains the length of a segment of defense value k which ends in i
    vector<int> segs(n, 0);

    // run sliding window to find all consecutive values that up to k
    int l = 0;
    int r = 0;

    while (r < n)
    {
        int def = cum_vals[r] - cum_vals[l] + vals[l];
        if (def == k)
        {
            segs[r] = r - l + 1;
            l++;
            r++;
        }
        else if (def < k)
        {
            r++;
        }
        else
        {
            l++;
            if (l > r)
                r++;
        }
    }

    // memo[i][j] contains the maximum value of a legal strategy for a defensive line up to defender i with j attackers
    vector<vector<int>> memo(n, vector<int>(m, 0));

    // initialize memo table
    for (int j = 0; j < m; j++)
        memo[0][j] = segs[0];
    for (int i = 1; i < n; i++)
        memo[i][0] = max(memo[i - 1][0], segs[i]);

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            // two cases: take this segment or don't
            int remaining = (i - segs[i] > 0 ? memo[i - segs[i]][j - 1] : 0);
            memo[i][j] = max(memo[i - 1][j], segs[i] + remaining);
        }
    }

    if (memo[n - 1][m - 1] == memo[n - 1][m - 2])
        cout << "fail\n";
    else
        cout << memo[n - 1][m - 1] << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
