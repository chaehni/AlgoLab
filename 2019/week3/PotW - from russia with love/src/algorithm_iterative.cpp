#include <iostream>
#include <vector>

using namespace std;

void testcase()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> sovereign;
    for (int i = 0; i < n; ++i)
    {
        int tmp;
        cin >> tmp;
        sovereign.push_back(tmp);
    }

    // initialize the dp table - max win for sequence sovereign from i to j stored at position (i,j)
    vector<vector<int>> max_win_ij(n, vector<int>(n, -1));
    for (int l = 0; l < n; l++)
    {
        if ((n - 1) % m == k)
            max_win_ij[l][l] = sovereign[l];
        else
            max_win_ij[l][l] = 0;
    }
    // fill in the rest of the dp table
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            int round = n - 1 - (j - i);
            if (round % m == k)
                max_win_ij[i][j] = max(sovereign[i] + max_win_ij[i + 1][j], sovereign[j] + max_win_ij[i][j - 1]);
            else
                max_win_ij[i][j] = min(max_win_ij[i + 1][j], max_win_ij[i][j - 1]);
        }
    }

    cout << max_win_ij[0][n - 1] << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    while (n--)
        testcase();
}
