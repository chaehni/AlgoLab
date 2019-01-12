#include <iostream>
#include <vector>
#include <map>

using namespace std;

int countUnsetBits(int i, int length)
{
    int cnt = 0;
    for (int s = 0; s < length; s++)
        cnt += !(bool)(i & 1 << s);
    return cnt;
}

void run()
{
    int n, k;
    cin >> n >> k;
    vector<int> skills(n);
    for (int i = 0; i < n; i++)
        cin >> skills[i];

    // brute force first half
    // generate all bitstrings of length n with at most k zeroes (1 at position i means player i plays, 0 doesn't play)
    map<pair<int, int>, int> store; // map the difference in team strenght and the refree count to the number this config occurs
    for (int i = 0; i < 1 << n / 2; i++)
    {
        // count number of refrees
        int refs = countUnsetBits(i, n / 2);
        if (refs > k)
            continue;

        // store players with a '1' and use them to build teams
        vector<int> chosen;
        for (int s = 0; s < n / 2; s++)
        {
            if (i & 1 << s)
                chosen.push_back(skills[s]);
        }

        // use another brute force to explore all possible teams with chosen players
        for (int j = 0; j < 1 << chosen.size(); j++)
        {
            int teamA = 0;
            int teamB = 0;
            for (int t = 0; t < chosen.size(); t++)
            {
                if (j & 1 << t)
                    teamA += chosen[t];
                else
                    teamB += chosen[t];
            }
            // store to map
            store[make_pair(teamA - teamB, refs)]++;
        }
    }

    long fair_teams = 0;
    // brute force second half
    // generate all bitstrings of length n with at most 0 zeroes (1 at position i means player i plays, 0 doesn't play)
    for (int i = 0; i < 1 << n - n / 2; i++)
    {
        //count number refrees
        int refs = countUnsetBits(i, n - n / 2);
        if (refs > k)
            continue;

        // store players with a '1' and use them to build teams
        vector<int> chosen;
        for (int s = 0; s < n - n / 2; s++)
        {
            if (i & 1 << s)
                chosen.push_back(skills[n / 2 + s]);
        }

        // use another brute force to explore all possible teams with chosen players
        for (int j = 0; j < 1 << chosen.size(); j++)
        {
            int teamA = 0;
            int teamB = 0;
            for (int t = 0; t < chosen.size(); t++)
            {
                if (j & 1 << t)
                    teamA += chosen[t];
                else
                    teamB += chosen[t];
            }
            // for these partial teams, find matching parts from first half with at most k-ref refrees
            for (int r = 0; r + refs <= k; r++)
            {
                fair_teams += store[make_pair(teamB - teamA, r)];
            }
        }
    }
    cout << fair_teams << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}