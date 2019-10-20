#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Boat
{
    int len;
    int ring;
};

void run()
{
    int n;
    cin >> n;
    vector<Boat> boats(n);
    for (int i = 0; i < n; i++)
    {
        Boat b;
        cin >> b.len;
        cin >> b.ring;
        boats[i] = b;
    }

    sort(boats.begin(), boats.end(), [](Boat b1, Boat b2) {
        return b1.ring < b2.ring;
    });

    int left_boundery = INT32_MIN; // marks the end of the last fixed boat
    int right_end = INT32_MIN;     // marks the right end of boats to take. Must be minimised.

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        Boat b = boats[i];

        if (b.ring >= right_end)
        {
            cnt++;
            left_boundery = right_end;
            right_end = (b.ring - b.len > left_boundery ? b.ring : left_boundery + b.len);
        }
        else
        {
            int temp_right = (b.ring - b.len > left_boundery ? b.ring : left_boundery + b.len);
            right_end = min(right_end, temp_right);
        }
    }
    cout << cnt << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
