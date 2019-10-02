#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>

struct Bomb
{
    int index, t;
};

using namespace std;

void run()
{
    int n;
    cin >> n;

    vector<Bomb> bombs(n);
    vector<bool> defused(n, false);

    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        bombs[i] = {i, t};
    }

    // sort bombs by explode time
    vector<Bomb> sorted(bombs);
    sort(sorted.begin(), sorted.end(), [](Bomb b1, Bomb b2) {
        return b1.t < b2.t;
    });

    // defuse bomb in explode time order, if a bomb needs other bombs to be defused first, defuse them recursively in explode time order
    int elapsed = 0;
    bool explosion = false;
    stack<Bomb> s;
    for (int i = 0; i < n; i++)
    {
        Bomb b = sorted[i];

        // did we have an explosion?
        if (explosion)
            break;

        // this bomb has been defused
        if (defused[b.index])
            continue;

        // check if this bomb exploded
        if (b.t <= elapsed)
        {
            explosion = true;
            break;
        }

        // bomb has no dependency (on ground)
        if (b.index >= (n - 1) / 2)
        {
            defused[b.index] = true;
            elapsed++;
            continue;
        }

        // bomb stands on other bombs
        s.push(sorted[i]);
        map<int, bool> visited;

        // defuse dependencies recursively
        while (!s.empty())
        {
            Bomb current = s.top();

            // if we have seen this bomb it means we have defused its dependencies -> try to defuse current
            if (visited[current.index])
            {
                if (current.t <= elapsed)
                {
                    explosion = true;
                    break;
                }

                defused[current.index] = true;
                s.pop();
                elapsed++;
                continue;
            }

            visited[current.index] = true; // after all cases below, the bomb is considered visited, mark it here to not repeat it for every if

            // current is a ground bomb -> no dependencies
            if (current.index >= (n - 1) / 2)
                continue;

            Bomb b1 = bombs[2 * current.index + 1];
            Bomb b2 = bombs[2 * current.index + 2];

            // dependencies have been defused already
            if (defused[b1.index] && defused[b2.index])
                continue;

            // one dependency has been defused
            if (defused[b1.index])
            {
                s.push(b2);
                continue;
            }
            if (defused[b2.index])
            {
                s.push(b1);
                continue;
            }

            // no dependency has been defused, push the dependencies onto the stack such that earlier bomb is on top
            if (b1.t <= b2.t)
            {
                s.push(b2);
                s.push(b1);
            }
            else
            {
                s.push(b1);
                s.push(b2);
            }
        }
    }

    if (explosion)
        cout << "no";
    else
        cout << "yes";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}