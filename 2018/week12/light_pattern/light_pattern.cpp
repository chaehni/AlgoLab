#include <iostream>
#include <vector>

using namespace std;

// returns the number of wrong bulbs in the range l l+k-1 based on the original lights or the inverted lights
int wrong(vector<bool> &bulbs, vector<bool> &pattern, int l, int r, bool inverse)
{
    int cnt = 0;
    if (!inverse)
    {
        for (int i = l; i < r; i++)
            if (bulbs[i] != pattern[i - l])
                cnt++;
    }
    else
    {
        for (int i = l; i < r; i++)
            if (bulbs[i] == pattern[i - l])
                cnt++;
    }

    return cnt;
}

void run()
{
    int N, K, X;
    cin >> N >> K >> X;

    // read bulbs into vector
    vector<bool> bulbs(N);
    for (int i = 0; i < N; i++)
    {
        int b;
        cin >> b;
        bulbs[i] = b;
    }

    // create required pattern by repeating the K least significant bits of X  N/K times
    vector<bool> pattern(K);
    for (int i = 0; i < K; i++)
        pattern[K - i - 1] = X & 1 << i;

    int groups = N / K;
    vector<vector<int>> table(groups, vector<int>(2)); // two fileds per group, index 0: min for lights as in input, index 1: min for inverted lights
    for (int i = 0; i < groups; i++)
    {
        /* We have two options:
            * We don't flip lights up to and including our group i -> we coun't wrong bulbs and add the count for groups 0 to i-1 with unflipped lights
            * We flip all bulbs up to and including our group i -> we count 1 flip plus wrong bulbs in inverted state and add count for inverted groups 0 to i-1 with flipped light
        */

        if (i == 0)
        {
            table[0][0] = min(wrong(bulbs, pattern, 0, K, false), wrong(bulbs, pattern, 0, K, true) + 1);
            table[0][1] = min(wrong(bulbs, pattern, 0, K, true), wrong(bulbs, pattern, 0, K, false) + 1);
            continue;
        }

        table[i][0] = min(wrong(bulbs, pattern, i * K, i * K + K, false) + table[i - 1][0], wrong(bulbs, pattern, i * K, i * K + K, true) + table[i - 1][1] + 1);
        table[i][1] = min(wrong(bulbs, pattern, i * K, i * K + K, true) + table[i - 1][1], wrong(bulbs, pattern, i * K, i * K + K, false) + table[i - 1][0] + 1);
    }

    cout << min(table[groups - 1][0], table[groups - 1][1] + 1) << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}