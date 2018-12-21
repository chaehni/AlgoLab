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
    Triangulation t;
    vector<K::Point_2> points(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i];
    }
    t.insert(points.begin(), points.end());

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        Point p;
        cin >> p;
        Point v = t.nearest_vertex(p)->point();
        cout << CGAL::squared_distance(p, v) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    while (true)
    {
        int n;
        cin >> n;
        if (n != 0)
            run(n);
        else
            break;
    }
}