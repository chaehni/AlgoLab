#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 Seg;
typedef K::Ray_2 Ray;
typedef K::Point_2 P;

using namespace std;

void run(int n)
{
    double x, y, a, b;
    cin >> x >> y >> a >> b;

    Ray r(P(x, y), P(a, b));
    vector<Seg> segs(n);

    for (int i = 0; i < n; i++)
    {
        double r, s, t, u;
        cin >> r >> s >> t >> u;
        segs[i] = Seg(P(r, s), P(t, u));
    }

    bool intersect = false;
    for (int i = 0; i < n; i++)
    {
        if (CGAL::do_intersect(r, segs[i]))
        {
            intersect = true;
            break;
        }
    }
    cout << (intersect ? "yes" : "no") << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}
