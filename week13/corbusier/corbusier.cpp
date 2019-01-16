#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

void run()
{
    int n, i, k;
    cin >> n >> i >> k;

    vector<int> disks(n);
    for (int i = 0; i < n; i++)
        cin >> disks[i];

    vector<vector<bool>> table(n, vector<bool>(k, 0)); // entry (i,j) saves if with first i disks we can achieve a height congruent to j mod k (height mod k = j)

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            /* OPTIONS:
                * we can achieve the congruency with with the first i-1 disks already
                * we can achieve the congruency with disk i alone
                * we can achieve the congruency with disk i and some of the first i-1 disks
            */

            bool o1 = i > 0 ? table[i - 1][j] : false;
            bool o2 = disks[i] % k == j;
            bool o3 = i > 0 ? table[i - 1][(k + j - (disks[i] % k)) % k] : false;

            table[i][j] = o1 || o2 || o3;
        }
    }

    if (table[n - 1][i])
        cout << "yes";
    else
        cout << "no";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}