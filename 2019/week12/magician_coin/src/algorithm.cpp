#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double recurse(vector<double> &p, vector<vector<double>> &memo, int n, int m, int day, int money)
{
    // base case
    if (day <= n && money >= m)
        return 1;
    if (day == n && money < m)
        return 0;

    if (memo[day][money] != -1)
        return memo[day][money];

    // bet every amount of money and record max probability to have more than m by the end of day n
    double max_prob = 0;
    for (int i = 0; i <= money; i++)
        max_prob = max(max_prob, p[day] * recurse(p, memo, n, m, day + 1, money + i) + (1 - p[day]) * recurse(p, memo, n, m, day + 1, money - i));

    memo[day][money] = max_prob;
    return max_prob;
}

void run()
{
    int n, k, m;
    cin >> n >> k >> m;
    vector<double> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];

    vector<vector<double>> memo(n, vector<double>(m, -1));
    cout << recurse(p, memo, n, m, 0, k) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(5);
    int t;
    cin >> t;
    while (t--)
        run();
}