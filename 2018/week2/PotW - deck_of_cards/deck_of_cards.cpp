#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void sum()
{
    int n, k;
    cin >> n >> k;

    vector<int> partial;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        partial.push_back(sum += temp);
    }

    int score = INT_MAX;
    int res_i = 0;
    int res_j;
    int i = 0;
    int j = 0;

    while (j < n)
    {
        int temp = (i == 0 ? partial[j] : (partial[j] - partial[i - 1]));

        if (abs(temp - k) < score)
        {
            score = abs(temp - k);
            res_i = i;
            res_j = j;
        }

        if (temp == k)
            break;

        if (temp < k)
        {
            j++;
            continue;
        }

        if (temp > k)
        {
            if (i < j)
                i++;
            else
                j++;
        }
    }

    cout << res_i << " " << res_j << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        sum();
    }
}
