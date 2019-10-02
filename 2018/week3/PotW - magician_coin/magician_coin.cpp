#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

double play(vector<double> &p, int wealth, int goal, int day, int N, vector<vector<double>> &memo)
{
    // if we played N times we need at least 'goal' money
    if (day == N && wealth < goal)
        return 0.0;

    if (wealth >= goal)
        return 1.0;

    // check memo
    if (memo[day][wealth] != -1)
        return memo[day][wealth];

    // else try to bet every amount and record max
    double best = 0;
    for (int i = 0; i <= wealth; i++)
        best = max(best, p[day] * play(p, wealth + i, goal, day + 1, N, memo) +
                             (1 - p[day]) * play(p, wealth - i, goal, day + 1, N, memo));

    memo[day][wealth] = best;
    return best;
}

void run()
{
    int N, K, M;
    cin >> N >> K >> M;

    // read probabilities
    vector<double> p(N);
    for (int i = 0; i < N; i++)
        cin >> p[i];

    vector<vector<double>> memo(N, vector<double>(M, -1));
    cout << play(p, K, M, 0, N, memo) << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(5);
    int n;
    cin >> n;
    while (n--)
        run();
}
