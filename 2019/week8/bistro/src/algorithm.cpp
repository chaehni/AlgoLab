#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

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

    // test new locations
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        Point p = Point(x, y);
        Point nearest = t.nearest_vertex(p)->point();
        cout << CGAL::squared_distance(p, nearest) << "\n";
    }
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
