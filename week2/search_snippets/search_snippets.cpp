#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void testcase()
{
    int n, pos;
    cin >> n;
    vector<int> occurs(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> occurs[i];
    }

    vector<pair<int, int>> word_pos;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < occurs[i]; ++j)
        {
            cin >> pos;
            word_pos.push_back(make_pair(pos, i));
        }
    }

    sort(word_pos.begin(), word_pos.end());

    // slide over ordered words to find all contiguous intervals containing all keywords
    int l = 0, r = 0;
    int cnt = 1;
    vector<int> occurences(n, 0);
    occurences[word_pos[0].second] = 1;
    int best = INT32_MAX;

    while (r < word_pos.size())
    {

        if (cnt < n && r == word_pos.size() - 1) // we don't have all words and can't take new ones -> done
            break;
        if (cnt < n && r < word_pos.size() - 1) // we don't have all words, add new words from right
        {
            r++;
            int w = word_pos[r].second;
            int o = occurences[w]++;
            if (o == 0) // we found an new word
                cnt++;
        }
        else if (cnt == n) // we have all words, try to remove from left
        {
            int w = word_pos[l].second;
            int o = --occurences[w];
            if (o < 0)
                "Abort!!";
            if (o == 0) // we lost a word
                cnt--;
            l++;
        }

        if (cnt == n) // check if we can update shortest interval
            best = min(best, word_pos[r].first - word_pos[l].first + 1);
    }

    cout << best << endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        testcase();
}