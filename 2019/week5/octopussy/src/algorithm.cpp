#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

struct Bomb
{
    int idx;
    int t;
    int l;
    int r;
    bool defused;
};

using namespace std;

void run()
{
    int n;
    cin >> n;

    vector<Bomb> bombs(n);
    for (int i = 0; i < n; i++)
    {
        Bomb b;
        cin >> b.t;
        b.defused = false;
        b.idx = i;
        if (i <= (n - 3) / 2)
        {
            b.l = 2 * i + 1;
            b.r = 2 * i + 2;
        }
        else
        {
            b.l = -1;
            b.r = -1;
        }
        bombs[i] = b;
    }
    vector<Bomb> sorted(bombs);

    // sort bombs with increasing timer time
    sort(sorted.begin(), sorted.end(), [](Bomb b1, Bomb b2) {
        return b1.t < b2.t;
    });

    int time = 0;
    bool kaboom = false;
    for (int i = 0; i < n; i++)
    {

        int index = sorted[i].idx;

        // if defused, continue
        if (bombs[index].defused)
            continue;

        // if time is over -> boom!
        if (time >= bombs[index].t)
        {
            kaboom = true;
            break;
        }

        // defuse
        // cout << "left " << b.l << endl;
        if (bombs[index].l == -1)
        {
            bombs[index].defused = true;
            time++;
            continue;
        }
        else
        {
            stack<int> s;
            s.push(index);
            while (!s.empty())
            {

                int cur = s.top();
                if (bombs[cur].defused)
                {
                    s.pop();
                    continue;
                }

                // this bomb has dependencies which are not defused-> push children
                if (cur <= (n - 3) / 2 && (!bombs[2 * cur + 1].defused || !bombs[2 * cur + 2].defused))
                {
                    if (bombs[2 * cur + 1].t < bombs[2 * cur + 2].t)
                    {
                        s.push(2 * cur + 2);
                        s.push(2 * cur + 1);
                    }
                    else
                    {
                        s.push(2 * cur + 1);
                        s.push(2 * cur + 2);
                    }
                }
                // this bomb has no dependencies -> defuse bomb
                else
                {
                    if (time >= bombs[cur].t)
                    {
                        kaboom = true;
                        break;
                    }
                    else
                    {
                        bombs[cur].defused = true;
                        time++;
                        s.pop();
                    }
                }
            }
        }
        if (kaboom)
            break;
    }

    if (kaboom)
        cout << "no\n";
    else
        cout << "yes\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
