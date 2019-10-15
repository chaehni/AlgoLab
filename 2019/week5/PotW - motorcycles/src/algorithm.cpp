#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Biker
{
    int idx;
    long origin;
    long x;
    long delta_y;
    bool neg;
};

bool smaller(Biker &b1, Biker &b2)
{
    __int128_t v1 = (__int128_t)b1.delta_y * b2.x;
    __int128_t v2 = (__int128_t)b2.delta_y * b1.x;
    if (v1 < 0 || v2 < 0)
        cout << "QBORT!!" << endl;
    return v1 < v2;
}

bool equal(Biker &b1, Biker &b2)
{
    __int128_t v1 = (__int128_t)b1.delta_y * b2.x;
    __int128_t v2 = (__int128_t)b2.delta_y * b1.x;
    return v1 == v2;
}

void run()
{
    int n;
    cin >> n;

    vector<Biker> bikers(n);
    for (int i = 0; i < n; i++)
    {
        long y0, x1, y1;
        cin >> y0 >> x1 >> y1;
        Biker b;
        b.idx = i;
        b.origin = y0;
        b.x = x1;
        b.delta_y = (y1 >= y0 ? y1 - y0 : y0 - y1);
        b.neg = y1 < y0;
        bikers[i] = b;
    }
    vector<int> result;

    // sort bikers with increasing slope, if same slope put the one lower first because of precedence rule
    sort(bikers.begin(), bikers.end(), [](Biker &fst, Biker &snd) {
        if (smaller(fst, snd))
        {
            return true;
        }
        else if (equal(fst, snd))
        {
            if (fst.neg != snd.neg && !fst.neg) // precedence for the one coming from the right (aka upwards)
                return true;
            if (!fst.neg && !snd.neg && fst.origin < snd.origin)
                return true;
            if (fst.neg && snd.neg && fst.origin > snd.origin)
                return true;
        }
        return false;
    });

    // iterate over rays with increasing slope
    result.push_back(bikers[0].idx);
    long maxy = bikers[0].origin;
    long miny = bikers[0].origin;

    for (int i = 1; i < n; i++)
    {
        // Biker rides forever if...
        if ((equal(bikers[i], bikers[0]) && bikers[i].neg == bikers[0].neg) || // ...if exactly the same slope as very first one
            (bikers[i].neg && bikers[i].origin < miny) ||                      // ...biker starts below miny and goes downwards
            (!bikers[i].neg && bikers[i].origin > maxy))                       // ...biker starts above maxy and goes upwards
            result.push_back(bikers[i].idx);

        maxy = max(maxy, bikers[i].origin);
        miny = min(miny, bikers[i].origin);
    }

    // print result
    sort(result.begin(), result.end());
    for (int r : result)
        cout << r << " ";
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
