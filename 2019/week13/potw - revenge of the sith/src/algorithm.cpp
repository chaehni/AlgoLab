#include <iostream>
#include <vector>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef K::Point_2 Point;

using namespace std;

void run()
{
    int n;
    long r;
    cin >> n >> r;

    vector<Point> planets;
    planets.reserve(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        planets.emplace_back(x, y);
    }

    // start from last planet and go back in time
    // for every encountered planet join it with all clusters that it is in reach with
    map<int, int> clust_size;
    boost::disjoint_sets_with_storage<> uf(n);
    Triangulation t;
    int best = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        clust_size[i] = 1;
        // for every new node, add it to triangulation and check if its neigbours are within reach for the vessel
        // if yes, join the two sets
        auto v = t.insert(planets[i]);
        v->info() = i;
        Triangulation::Vertex_circulator c = t.incident_vertices(v);
        if (c != 0)
        {
            do
            {
                if (!t.is_infinite(c))
                {
                    int neighbour = c->info();
                    K::FT dist = CGAL::squared_distance(v->point(), c->point());
                    if (dist <= r * r)
                    {

                        int c1 = uf.find_set(i);
                        int c2 = uf.find_set(neighbour);
                        if (c1 != c2)
                        {
                            uf.link(c1, c2);
                            clust_size[uf.find_set(i)] = clust_size[c1] + clust_size[c2];
                        }
                    }
                }
            } while (++c != t.incident_vertices(v));
        }
        if (i < best)
            break;
        best = max(best, min(i, clust_size[uf.find_set(i)]));
    }
    cout << best << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}