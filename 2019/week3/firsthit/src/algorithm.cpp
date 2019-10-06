#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 Seg;
typedef K::Ray_2 Ray;
typedef K::Point_2 P;

using namespace std;

double floor_to_double(const K::FT &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

void run(int n)
{
    long x, y, a, b;
    cin >> x >> y >> a >> b;
    Ray r(P(x, y), P(a, b));
    Seg rs;

    vector<pair<P, P>> points(n);
    for (int i = 0; i < n; i++)
    {
        long r, s, t, u;
        cin >> r >> s >> t >> u;
        points[i] = make_pair(P(r, s), P(t, u));
    }

    random_shuffle(points.begin(), points.end());
    bool hit = false;

    for (int i = 0; i < n; i++)
    {
        if (hit)
        {
            if (CGAL::do_intersect(rs, Seg(points[i].first, points[i].second)))
            {
                auto o = CGAL::intersection(rs, Seg(points[i].first, points[i].second));
                if (const P *op = boost::get<P>(&*o))
                    rs = Seg(P(x, y), *op);
                else if (const Seg *os = boost::get<Seg>(&*o))
                {
                    if (CGAL::squared_distance(P(x, y), os->source()) < CGAL::squared_distance(P(x, y), os->target()))
                        rs = Seg(P(x, y), os->source());
                    else
                        rs = Seg(P(x, y), os->target());
                }
            }
        }
        else
        {
            if (CGAL::do_intersect(r, Seg(points[i].first, points[i].second)))
            {
                auto o = CGAL::intersection(r, Seg(points[i].first, points[i].second));
                if (const P *op = boost::get<P>(&*o))
                    rs = Seg(P(x, y), *op);
                else if (const Seg *os = boost::get<Seg>(&*o))
                {
                    if (CGAL::squared_distance(P(x, y), os->source()) < CGAL::squared_distance(P(x, y), os->target()))
                        rs = Seg(P(x, y), os->source());
                    else
                        rs = Seg(P(x, y), os->target());
                }
                hit = true;
            }
        }
    }
    if (hit)
        cout << floor_to_double(rs.target().x()) << " " << floor_to_double(rs.target().y()) << endl;
    else
        cout << "no" << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}
