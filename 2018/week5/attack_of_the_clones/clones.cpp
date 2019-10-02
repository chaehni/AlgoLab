#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Jedi
{
    int start;
    int end;
};

// calculates the max number of segments that fit in the range [start, end]
int EDF(vector<Jedi> &data, int start, int end)
{
    int right_end = start - 1;
    int cnt = 0;
    for (auto j : data)
    {
        if (j.start > right_end && j.end <= end)
        {
            right_end = j.end;
            cnt++;
        }
    }
    return cnt;
}

void run()
{
    int n, m;
    cin >> n >> m;

    vector<Jedi> jedis(n);
    map<int, int> count;

    for (int i = 0; i < n; i++)
    {
        int s, e;
        cin >> s >> e;

        jedis[i].start = s;
        jedis[i].end = e;

        count[s]++;
        count[e]--;

        if (s > e)
        {
            count[1]++;
        }
    }

    // Find segment with at most 10 overlaps
    int c = -1;
    int overlaps = 0;
    for (auto it = count.begin(); it != count.end(); ++it)
    {
        overlaps += it->second;
        if (overlaps <= 10)
            c = it->first + 1;
    }

    // we found the segment, adapt the start- and end points for every jedi to start from there
    vector<Jedi> centered;
    vector<Jedi> overlap;
    for (int i = 0; i < n; i++)
    {
        int s, e;
        s = jedis[i].start;
        e = jedis[i].end;

        int s_new, e_new;

        if (s > c)
            jedis[i].start = s - c;
        else
            jedis[i].start = s - c + m;

        if (e > c)
            jedis[i].end = e - c;
        else
            jedis[i].end = e - c + m;

        if (s <= e && s <= c && c <= e || s > e && (s <= c || e >= c))
        {
            overlap.push_back(jedis[i]);
            continue;
        }
        centered.push_back(jedis[i]);
    }

    sort(centered.begin(), centered.end(), [](Jedi j1, Jedi j2) {
        return j1.end < j2.end;
    });

    // Run a EDF scheduler on centered data
    int cnt_max = EDF(centered, 0, m);
    // For each of the overlaping segments pick it and run EDF on non-overlapping segments
    for (auto it = overlap.begin(); it != overlap.end(); ++it)
    {
        cnt_max = max(cnt_max, EDF(centered, it->end + 1, it->start - 1) + 1);
    }

    cout << cnt_max << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int tests;
    cin >> tests;
    while (tests--)
    {
        run();
    }
}