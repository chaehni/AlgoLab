#include <iostream>
#include <vector>

using namespace std;

void run()
{
    int n, m, k;
    long x;
    cin >> n >> m >> x >> k;

    vector<vector<pair<int, long>>> trans(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long p;
        cin >> u >> v >> p;
        trans[u].emplace_back(v, p);
    }

    vector<vector<long>> memo(k, vector<long>(n, 0));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // try out all possibilities from this position
            long best = 0;
            if (i == 0)
            {
                if (trans[j].size() == 0)
                    best = memo[i][0];
                else
                    for (auto t : trans[j])
                        best = max(best, t.second);
            }
            else
            {
                if (trans[j].size() == 0)
                    best = memo[i][0];
                else
                    for (auto t : trans[j])
                        best = max(best, t.second + memo[i - 1][t.first]);
            }
            memo[i][j] = best;
        }
    }

    if (memo[k - 1][0] < x)
    {
        cout << "Impossible\n";
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            if (memo[i][0] >= x)
            {
                cout << i + 1 << "\n";
                break;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
