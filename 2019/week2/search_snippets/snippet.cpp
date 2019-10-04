#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void run()
{
    int n; // words
    cin >> n;

    vector<int> w_count(n);
    for (int i = 0; i < n; i++)
    {
        cin >> w_count[i];
    }
    vector<pair<int, int>> words;
    for (int word = 0; word < n; word++)
    {
        for (int i = 0; i < w_count[word]; i++)
        {
            int index;
            cin >> index;
            words.push_back(make_pair(index, word));
        }
    }

    // sort words by position
    sort(words.begin(), words.end());

    int l = 0;
    int r = 0;
    int shortest = INT32_MAX;
    int count = 1;
    vector<int> covered(n, 0);
    covered[words[0].second] = 1;

    while (r < words.size())
    {
        if (count == n)
        {
            shortest = min(shortest, words[r].first - words[l].first + 1);

            covered[words[l].second]--;
            if (covered[words[l].second] == 0)
            {
                count--;
            }
            l++;
        }
        else if (count < n)
        {
            r++;
            if (covered[words[r].second] == 0)
            {
                count++;
            }
            covered[words[r].second]++;
        }
    }
    cout << shortest << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}