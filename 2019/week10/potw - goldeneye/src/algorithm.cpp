#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef std::pair<K::Point_2, Index> IPoint;
typedef K::Point_2 Point;
typedef std::tuple<Index, Index, K::FT> Edge;
typedef std::vector<Edge> EdgeV;

using namespace std;

void run()
{
    int n, m;
    long p;
    cin >> n >> m >> p;

    std::vector<IPoint> points;
    points.reserve(n);
    for (Index i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points.emplace_back(K::Point_2(x, y), i);
    }
    Triangulation tri;
    tri.insert(points.begin(), points.end());

    EdgeV edges;
    edges.reserve(3 * n); // there can be no more in a planar graph
    for (auto e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e)
    {
        Index i1 = e->first->vertex((e->second + 1) % 3)->info();
        Index i2 = e->first->vertex((e->second + 2) % 3)->info();
        // ensure smaller index comes first
        if (i1 > i2)
            std::swap(i1, i2);
        edges.emplace_back(i1, i2, tri.segment(e).squared_length());
    }
    std::sort(edges.begin(), edges.end(),
              [](const Edge &e1, const Edge &e2) -> bool {
                  return std::get<2>(e1) < std::get<2>(e2);
              });

    // setup and initialize union-find data structure
    boost::disjoint_sets_with_storage<> uf(n);
    // Index n_components = n;
    // ... and process edges in order of increasing length
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e)
    {
        if (std::get<2>(*e) > p)
            break;
        Index c1 = uf.find_set(std::get<0>(*e));
        Index c2 = uf.find_set(std::get<1>(*e));
        if (c1 != c2)
            uf.link(c1, c2);
    }

    // iterator for all missions output
    EdgeV::const_iterator e_all = edges.begin();
    // reqired power for all missions
    K::FT req_power = 0;
    boost::disjoint_sets_with_storage<>
        uf_all(n);
    // iterator for same missions output
    EdgeV::const_iterator e_same = edges.begin();
    // reqired power for same missions
    K::FT same_power = 0;
    boost::disjoint_sets_with_storage<>
        uf_same(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        int u, v;
        cin >> x >> y >> u >> v;
        Point s = Point(x, y);
        Point t = Point(u, v);

        // find indices nearest jammers for start and target
        auto nearest_s = tri.nearest_vertex(s);
        auto nearest_t = tri.nearest_vertex(t);

        Index i1 = uf.find_set(nearest_s->info());
        Index i2 = uf.find_set(nearest_t->info());
        bool possible;
        // check if start and target are covered by umbrella and if there nearest jammers are in same component
        if (CGAL::squared_distance(s, nearest_s->point()) * 4 > p ||
            CGAL::squared_distance(t, nearest_t->point()) * 4 > p ||
            i1 != i2)
            possible = false;
        else
            possible = true;

        // to find power to cover all missions, add edges until mission becomes possible
        // first, set required power such that start and target are covered
        req_power = max(req_power, max(CGAL::squared_distance(s, nearest_s->point()) * 4, CGAL::squared_distance(t, nearest_t->point()) * 4));
        for (; e_all != edges.end();)
        {
            // check if our mission is already possible
            Index i1 = uf_all.find_set(nearest_s->info());
            Index i2 = uf_all.find_set(nearest_t->info());
            if (i1 == i2)
                break;

            Index c1 = uf_all.find_set(std::get<0>(*e_all));
            Index c2 = uf_all.find_set(std::get<1>(*e_all));
            if (c1 != c2)
                uf_all.link(c1, c2);
            req_power = max(req_power, std::get<2>(*e_all));
            ++e_all;
        }

        // to find power to cover same missions, add edges until mission becomes possible
        // first, set required power such that start and target are covered
        if (possible)
        {
            same_power = max(same_power, max(CGAL::squared_distance(s, nearest_s->point()) * 4, CGAL::squared_distance(t, nearest_t->point()) * 4));
            for (; e_same != edges.end();)
            {
                // check if our mission is already possible
                Index i1 = uf_same.find_set(nearest_s->info());
                Index i2 = uf_same.find_set(nearest_t->info());
                if (i1 == i2)
                    break;

                Index c1 = uf_same.find_set(std::get<0>(*e_same));
                Index c2 = uf_same.find_set(std::get<1>(*e_same));
                if (c1 != c2)
                    uf_same.link(c1, c2);
                same_power = max(same_power, std::get<2>(*e_same));
                ++e_same;
            }
        }

        // output
        if (possible)
            cout << "y";
        else
            cout << "n";
    }
    cout << "\n"
         << CGAL::to_double(req_power) << "\n"
         << CGAL::to_double(same_power) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int t;
    cin >> t;
    while (t--)
        run();
}
