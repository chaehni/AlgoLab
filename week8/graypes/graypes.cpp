#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

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

    auto min = t.segment(t.finite_edges_begin()).squared_length();
    for (auto it = t.finite_edges_begin(); it != t.finite_edges_end(); it++)
    {
        if (t.segment(*it).squared_length() < min)
            min = t.segment(*it).squared_length();
    }

    cout << ceil(sqrt(CGAL::to_double(min)) / 2 * 100) << "\n";
}

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        else
            run(n);
    }
}