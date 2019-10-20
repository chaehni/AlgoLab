#include <iostream>
#include <vector>
#include <map>

using namespace std;

void run()
{
    int n;
    cin >> n;

    vector<int> planks(n);
    long sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> planks[i];
        sum += planks[i];
    }

    // eumerate all possible squares with split & list: we need 2 bits per plank
    // 00 -> top, 01 -> right, 10 -> bottom, 11 -> left

    map<vector<long>, int> memo;
    for (long i = 0; i < 1 << 2 * (n / 2); i++)
    {
        vector<long> r(4, 0);
        for (int b = 0; b < 2 * (n / 2); b += 2)
        {
            bool one = i & 1 << b;
            bool two = i & 1 << (b + 1);

            if (!one && !two)
                r[0] += planks[b / 2];
            else if (one && !two)
                r[1] += planks[b / 2];
            else if (!one && two)
                r[2] += planks[b / 2];
            else
                r[3] += planks[b / 2];
        }
        memo[r]++;
    }

    int cnt = 0;
    for (long i = 0; i < 1 << 2 * (n - n / 2); i++)
    {
        vector<long> r(4, sum / 4);
        for (int b = 0; b < 2 * (n - n / 2); b += 2)
        {
            bool one = i & 1 << b;
            bool two = i & 1 << (b + 1);

            if (!one && !two)
                r[0] -= planks[n / 2 + b / 2];
            else if (one && !two)
                r[1] -= planks[n / 2 + b / 2];
            else if (!one && two)
                r[2] -= planks[n / 2 + b / 2];
            else
                r[3] -= planks[n / 2 + b / 2];
        }
        cnt += memo[r];
    }

    cout << cnt / 24 << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
