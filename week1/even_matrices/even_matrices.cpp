#include <iostream>
#include <vector>

using namespace std;

void run()
{
    int n;
    cin >> n;

    vector<vector<int>> M(n + 1, vector<int>(n + 1));
    vector<vector<int>> pM(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; j++)
            cin >> M[i][j];

    for (int i = 0; i <= n; i++)
    {
        pM[0][i] = 0;
        pM[i][0] = 0;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pM[i][j] = pM[i - 1][j] + pM[i][j - 1] - pM[i - 1][j - 1] + M[i][j];

    int solution = 0;
    for (int i1 = 1; i1 <= n; ++i1)
    {
        for (int i2 = i1; i2 <= n; ++i2)
        {                        // We reduce the problem to one dimension.
            vector<int> S(201);  // We do Even Pairs on array S.
            vector<int> pS(201); // pS contains partial sums of S.
            pS[0] = 0;
            for (int k = 1; k <= n; ++k)
            {
                S[k] = pM[i2][k] - pM[i2][k - 1] - pM[i1 - 1][k] + pM[i1 - 1][k - 1];
                pS[k] = pS[k - 1] + S[k];
            }
            // Do Even Pairs O(n) algorithm on array S.
            int even = 0, odd = 0;
            for (int j = 1; j <= n; ++j)
            {
                // even = number of partial sums of array
                // (S[1], ..., S[j - 1]) that are even.
                // odd = number of partial sums of array
                // (S[1], ..., S[j - 1]) that are odd.
                if (pS[j] % 2 == 0)
                    ++even;
                else
                    ++odd;
            }
            solution += even * (even - 1) / 2;
            solution += odd * (odd - 1) / 2;
            solution += even;
        }
    }
    cout << solution << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}
