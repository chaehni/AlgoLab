#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void run()
{
    int n;
    cin >> n;
    vector<int> sols(n);
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        sols[i] = temp + 10e6;
    }
    sort(sols.begin(), sols.end());

    int l = 0, r = 0;
    int most = 1;
    int min_max = 0;
    vector<int> pos;

    while (r < sols.size())
    {
        int dist = sols[r] - sols[l];
        if (dist <= 200)
        {
            int num_sols = r - l + 1;
            int dist_divided = dist % 2 == 0 ? dist / 2 : dist / 2 + 1;
            if (num_sols > most)
            {
                most = num_sols;
                min_max = dist_divided;
                pos.clear();
                pos.push_back((sols[r] + sols[l]) / 2);
                if ((sols[r] + sols[l]) % 2 == 1)
                    pos.push_back((sols[r] + sols[l]) / 2 + 1);
            }
            else if (num_sols == most && dist_divided < min_max)
            {
                min_max = dist_divided;
                pos.clear();
                pos.push_back((sols[r] + sols[l]) / 2);
                if ((sols[r] + sols[l]) % 2 == 1)
                    pos.push_back((sols[r] + sols[l]) / 2 + 1);
            }
            else if (num_sols == most && dist_divided == min_max)
            {
                pos.push_back((sols[r] + sols[l]) / 2);
                if ((sols[r] + sols[l]) % 2 == 1)
                    pos.push_back((sols[r] + sols[l]) / 2 + 1);
            }
            r++;
        }
        else
        {
            l++;
        }
    }
    cout << most << " " << min_max << endl;
    cout << pos[0] - 10e6;
    for (int i = 1; i < pos.size(); i++)
        cout << " " << pos[i] - 10e6;
    cout << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
        run();
}
