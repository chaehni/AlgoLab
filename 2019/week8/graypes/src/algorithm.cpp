#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

double ceil_to_double(SK::FT x)
{
    double a = ceil(CGAL::to_double(x));
    while (a < x)
        a++;
    while (a >= x + 1)
        a--;
    return a;
}

void run(int n)
{
    vector<Point> loc(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        loc[i] = Point(x, y);
    }

    Triangulation t;
    t.insert(loc.begin(), loc.end());

    // loop over all edges in triangulation and find the shortest one
    K::FT min_dist = long(INT64_MAX);
    for (auto e = t.edges_begin(); e != t.edges_end(); e++)
        min_dist = min(min_dist, t.segment(e).squared_length());

    cout << ceil_to_double(CGAL::sqrt(SK::FT(min_dist)) / 2 * 100) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << setprecision(0) << fixed;
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}
