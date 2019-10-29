#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// runs EDF in the interval [start, end]
int EDF(vector<pair<int, int>> &jedis, int start, int end)
{
    int cnt = 0;
    int curr_end = start - 1;
    for (auto jedi : jedis)
    {
        if (jedi.second > end)
            break;

        if (jedi.first > curr_end)
        {
            cnt++;
            curr_end = jedi.second;
        }
    }
    return cnt;
}

void run()
{
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> jedis(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        jedis[i] = make_pair(a, b);

        // keep track of jedis per segment
        cnt[a]++;
        cnt[b + 1]--; // if b == n-1 we increase the counter for n which is out of bound but it doesn't matter (we never read that value again)
        if (a > b)
            cnt[0]++;
    }

    // find sector with fewest jedis covering it
    int min_jedis = INT32_MAX;
    int curr_jedis = 0;
    int best_sector = 0;
    for (auto it = cnt.begin(); it != cnt.end() && it->first < m; it++) // we could have an entry for n (see above), so iterate until end or until n-1
    {
        curr_jedis += it->second;
        if (curr_jedis < min_jedis)
        {
            min_jedis = curr_jedis;
            best_sector = it->first;
        }
    }

    // we now have a sector with at most 10 overlaps
    // find the jedis that overlap that segment and the ones that don't
    vector<pair<int, int>> overlap;
    vector<pair<int, int>> no_overlap;
    for (auto jedi : jedis)
    {
        int s = jedi.first;
        int e = jedi.second;
        int c = best_sector;

        int s_new = (s >= c ? s - c : s - c + m);
        int e_new = (e >= c ? e - c : e - c + m);

        if (s <= e && s < c && c <= e || s > e && (s < c || c <= e))
            overlap.push_back(make_pair(s_new, e_new));
        else
            no_overlap.push_back(make_pair(s_new, e_new));
    }

    // sort non-overlapping in EDF manner with respect to best_sector as starting point
    sort(no_overlap.begin(), no_overlap.end(), [](pair<int, int> j1, pair<int, int> j2) {
        return (j1.second < j2.second);
    });

    // take best_sector as starting point for EDF algorithm
    // for every overlaping jedi, pre-select it and run the algorithm from its end-point to its start-point with non-overlapping segments
    // or choose none of the overlapping segments
    int best = EDF(no_overlap, 0, m - 1);
    for (auto jedi : overlap)
        best = max(best, EDF(no_overlap, jedi.second + 1, jedi.first - 1) + 1);

    cout << best << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
