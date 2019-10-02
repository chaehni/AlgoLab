#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Segment_2.h>

// Kernels
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;

// Delauny
typedef CGAL::Triangulation_vertex_base_with_info_2<K::FT, K> vertex_t;         // vertices with info
typedef CGAL::Triangulation_face_base_2<K> face_t;                              // regular faces
typedef CGAL::Triangulation_data_structure_2<vertex_t, face_t> triangulation_t; // datastructure using new vertices and faces
typedef CGAL::Delaunay_triangulation_2<K, triangulation_t> delaunay_t;          // delauny triangualtion

// Primitives
typedef K::Point_2 P;

using namespace std;

SK::FT to_hours(SK::FT s)
{
    return ceil(CGAL::to_double(CGAL::sqrt((CGAL::sqrt(s) - 1) / 2)));
}

void run(int n)
{
    int l, b, r, t;
    cin >> l >> b >> r >> t;

    delaunay_t tri;
    vector<K::Point_2> points(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i];
    }
    tri.insert(points.begin(), points.end());

    // For every point calcualte the time it dies
    // This is either by touching another germ with which it shares an edge in the delauny triangulation or by touching a wall
    for (auto v = tri.finite_vertices_begin(); v != tri.finite_vertices_end(); ++v)
    {
        P p = v->point();
        K::FT next_wall = min(min(p.x() - l, r - p.x()), min(p.y() - b, t - p.y()));
        v->info() = 4 * next_wall * next_wall;
    }

    for (auto e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e)
    {
        auto v1 = e->first->vertex(tri.cw(e->second));
        auto v2 = e->first->vertex(tri.ccw(e->second));
        P g1 = v1->point();
        P g2 = v2->point();

        K::FT dist = CGAL::squared_distance(g1, g2);
        v1->info() = min(v1->info(), dist);
        v2->info() = min(v2->info(), dist);
    }

    vector<K::FT> die_time;
    for (auto v = tri.finite_vertices_begin(); v != tri.finite_vertices_end(); ++v)
    {
        die_time.push_back(v->info());
    }
    sort(die_time.begin(), die_time.end());
    cout << to_hours(SK::FT(die_time[0])) << " ";
    cout << to_hours(SK::FT(die_time[n / 2])) << " ";
    cout << to_hours(SK::FT(die_time[n - 1])) << "\n";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
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