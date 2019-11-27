#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;
    vector<int> friends(n);
    auto comp = [](int a, int b) { return a > b; };
    multiset<int, decltype(comp)> books(comp);
    for (int i = 0; i < n; i++)
        cin >> friends[i];
    for (int i = 0; i < m; i++)
    {
        int b;
        cin >> b;
        books.insert(b);
    }

    // sort friends
    sort(friends.begin(), friends.end(), [](int a, int b) { return a > b; });

    if (*books.begin() > friends[0])
    {
        cout << "impossible\n";
    }
    else
    {
        int rounds = 0;
        // go through all friends, every friend picks heaviest box he can lift
        while (!books.empty())
        {
            // in every round, all friends take the heaviest box they can
            for (int f : friends)
            {
                auto it = books.lower_bound(f);
                if (it != books.end())
                    books.erase(it);
                else
                    // break since only weaker friends follow
                    break;
            }
            rounds++;
        }
        cout << rounds * 3 - 1 << "\n";
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
