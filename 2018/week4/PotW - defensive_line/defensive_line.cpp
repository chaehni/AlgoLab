#include <iostream>
#include <vector>

using namespace std;

void run()
{
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> sum(N);
    int cum = 0;
    for (int i = 0; i < N; i++)
    {
        int temp;
        cin >> temp;
        cum += temp;
        sum[i] = cum;
    }

    // ends[i] contains the length of a defensive line of strength K that ends in i
    vector<int> ends(N, 0);
    int l = 0;
    int r = 0;

    while (r < N)
    {

        int value = r == 0 ? sum[0] : sum[r] - sum[l - 1];
        if (value == K)
        {
            ends[r] = r - l + 1;
            r++;
            l++;
        }

        if (value < K)
            r++;

        if (value > K)
        {
            if (l < r)
                l++;
            else
                r++;
        }
    }

    // DP table
    vector<vector<int>> table(M, vector<int>(N));

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int o1 = j > 0 ? table[i][j - 1] : 0;                                         // take the value from left
            int o2 = ends[j];                                                             //only take the line ending in j (initialization for one attacker)
            int o3 = i > 0 && j - ends[j] >= 0 ? ends[j] + table[i - 1][j - ends[j]] : 0; // take the line ending in j plus the max we can get with i-1 attackers up to
                                                                                          //the start of the line we took

            table[i][j] = max(max(o1, o2), o3);
        }
    }

    if (M >= 2 && table[M - 1][N - 1] == table[M - 2][N - 1]) // value has to increase for every additional attacker
        cout << "fail" << endl;
    else
        cout << table[M - 1][N - 1] << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}