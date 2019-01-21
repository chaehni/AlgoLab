#include <iostream>
#include <vector>
#include <map>

using namespace std;

void run()
{
    int N;
    cin >> N;

    vector<int> planks(N);
    long sum = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> planks[i];
        sum += planks[i];
    }

    // we must use all planks
    if (sum % 4 != 0)
    {
        cout << 0 << "\n";
        return;
    }

    map<vector<long>, long> memo;
    for (long i = 0; i < 1 << 2 * (N / 2); i++)
    {
        vector<long> p(4, 0);
        for (int s = 0; s < 2 * (N / 2); s += 2)
        {
            bool f = bool(i & 1 << s);
            bool g = bool(i & 1 << (s + 1));

            if (!f && !g)
                p[0] += planks[s / 2];
            else if (f && !g)
                p[1] += planks[s / 2];
            else if (!f && g)
                p[2] += planks[s / 2];
            else
                p[3] += planks[s / 2];
        }
        memo[p]++;
    }

    long cnt = 0;
    for (long i = 0; i < 1 << 2 * (N - N / 2); i++)
    {
        vector<long> p(4, sum / 4);
        for (int s = 0; s < 2 * (N - N / 2); s += 2)
        {
            bool f = bool(i & 1 << s);
            bool g = bool(i & 1 << (s + 1));

            if (!f && !g)
                p[0] -= planks[N / 2 + s / 2];
            else if (f && !g)
                p[1] -= planks[N / 2 + s / 2];
            else if (!f && g)
                p[2] -= planks[N / 2 + s / 2];
            else
                p[3] -= planks[N / 2 + s / 2];
        }
        cnt += memo[p];
    }

    cout << cnt / 24 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}