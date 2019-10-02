#include <iostream>
#include <vector>
#include <map>

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;
    vector<int> target(m);

    // read target brightness for every room
    for (int i = 0; i < m; i++)
        cin >> target[i];

    // read switches and lights they control
    vector<vector<pair<int, int>>> switches(n, vector<pair<int, int>>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int on, off;
            cin >> on >> off;
            switches[i][j] = make_pair(on, off);
        }
    }

    // brute force all combinations with first half of switches and record for every configuration
    // the number of lights turned on in every room and the number of switch flips
    map<vector<int>, int> configs;
    for (int i = 0; i < 1 << n / 2; i++)
    {
        int flip_count = 0;
        vector<int> current_lights(m, 0);
        // for this configuration, flip corresponding switches
        for (int s = 0; s < n / 2; s++)
        {
            bool flipped = (bool)(i & 1 << s);
            flip_count += flipped;

            // for this configuration compute the lights in every room
            for (int r = 0; r < m; r++)
            {
                int lights = (!flipped ? switches[s][r].first : switches[s][r].second);
                current_lights[r] += lights;
            }
        }
        // we set all switches according to current config, save lights to map
        if (configs.find(current_lights) == configs.end() || configs[current_lights] > flip_count)
            configs[current_lights] = flip_count;
    }

    // brute force second half of switches and find overall correct configurations with minimum switch flips
    bool possible = false;
    int min_flips = INT32_MAX;
    for (int i = 0; i < 1 << (n - n / 2); i++)
    {
        int flip_count = 0;
        vector<int> missing(target);
        // for this configuration, flip corresponding switches
        for (int s = 0; s < (n - n / 2); s++)
        {
            bool flipped = (bool)(i & 1 << s);
            flip_count += flipped;

            // for this configuration compute the lights in every room
            for (int r = 0; r < m; r++)
            {
                int lights = (!flipped ? switches[n / 2 + s][r].first : switches[n / 2 + s][r].second);
                missing[r] -= lights;
            }
        }

        // we set all switches according to current config, try to find matching config from first half
        if (configs.find(missing) != configs.end())
        {
            min_flips = min(min_flips, configs[missing] + flip_count);
            possible = true;
        }
    }

    if (possible)
        cout << min_flips;
    else if (!possible)
        cout << "impossible";
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