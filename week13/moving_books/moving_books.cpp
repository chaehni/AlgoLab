#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;

    vector<int> friends(n);
    multiset<int, greater<int>> boxes;

    int strongest = 0;
    int heaviest = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> friends[i];
        strongest = max(strongest, friends[i]);
    }
    for (int i = 0; i < m; i++)
    {
        int box;
        cin >> box;
        boxes.insert(box);
        heaviest = max(heaviest, box);
    }

    if (heaviest > strongest)
    {
        cout << "impossible\n";
        return;
    }

    // we need friends sorted such that we can break out of the below loop early
    sort(friends.begin(), friends.end(), [](int a, int b) { return a > b; });

    // in every round everyone takes the heaviest box he can
    int rounds = 0;
    while (!boxes.empty())
    {
        for (int i = 0; i < n; i++)
        {
            // for every friend find heaviest box that is not too heavy
            auto it = boxes.lower_bound(friends[i]);
            if (it != boxes.end())
                boxes.erase(it);
            else
                break;
        }
        rounds++;
    }

    cout << rounds * 3 - 1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}