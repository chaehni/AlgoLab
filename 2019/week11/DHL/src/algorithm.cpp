#include <iostream>
#include <vector>

using namespace std;

void run()
{
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);
    vector<int> suma(n);
    vector<int> sumb(n);

    cin >> a[0];
    suma[0] = a[0];
    for (int i = 1; i < n; i++)
    {
        cin >> a[i];
        suma[i] = suma[i - 1] + a[i];
    }
    cin >> b[0];
    sumb[0] = b[0];
    for (int i = 1; i < n; i++)
    {
        cin >> b[i];
        sumb[i] = sumb[i - 1] + b[i];
    }

    // DP table
    vector<vector<int>> memo(n, vector<int>(n));

    // handle cases with only 1 packet left on either stack

    // a has only one left
    for (int i = 0; i < n; i++)
        memo[0][i] = (suma[0] - 1) * (sumb[i] - (i + 1));

    // b has only one left
    for (int i = 0; i < n; i++)
        memo[i][0] = (suma[i] - (i + 1)) * (sumb[0] - 1);

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            int o1 = memo[i - 1][j - 1];
            int o2 = memo[i][j - 1];
            int o3 = memo[i - 1][j];
            int min_cost = min(min(o1, o2), o3);
            memo[i][j] = min_cost + (a[i] - 1) * (b[j] - 1);
        }
    }

    cout << memo[n - 1][n - 1] << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
