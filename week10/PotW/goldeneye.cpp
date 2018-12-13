#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

#include <boost/pending/disjoint_sets.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef boost::disjoint_sets_with_storage<> Uf;
typedef K::Point_2 P;
typedef K::Segment_2 S;

using namespace std;

struct Edge
{
    Edge(int s, int e, K::FT l) : start_id(s), end_id(e), length(l) {}
    int start_id, end_id;
    K::FT length;
};

void run()
{
    int n, m;
    cin >> n >> m;
    double p;
    cin >> p;

    // read jammers
    vector<P> jammers(n);
    map<P, int> jammer_id;
    for (int i = 0; i < n; i++)
    {
        cin >> jammers[i];
        jammer_id[jammers[i]] = i;
    }

    Triangulation t;
    t.insert(jammers.begin(), jammers.end());

    Uf ufp(n);

    // extract needed info from finite edges into a more accessible data structure
    vector<Edge> edges;
    for (auto it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it)
    {
        edges.push_back(Edge(jammer_id[t.segment(*it).source()], jammer_id[t.segment(*it).target()], t.segment(*it).squared_length()));
    }

    // sort edges by increasing length
    // we need this to make sure we update the the min_power correctly
    sort(edges.begin(), edges.end(), [](Edge e1, Edge e2) {
        return e1.length < e2.length;
    });

    // iterate over all edges and union the corresponding vertices if the distance is small enough
    for (auto e : edges)
    {
        if (e.length <= p)
        {
            //union the two vertices of this edge
            ufp.union_set(e.start_id, e.end_id);
        }
    }

    // answer missions
    K::FT min_power_a = 0;
    K::FT min_power_b = 0;
    Uf ufb(n);
    Uf ufa(n);
    auto itb = edges.begin();
    auto ita = edges.begin();
    for (int i = 0; i < m; i++)
    {
        P start, end;
        cin >> start >> end;

        auto nearest_s = t.nearest_vertex(start)->point();
        auto nearest_e = t.nearest_vertex(end)->point();
        int nearest_s_id = jammer_id[nearest_s];
        int nearest_e_id = jammer_id[nearest_e];

        // fail if either start or end point is not covered
        auto dist_to_start = CGAL::squared_distance(nearest_s, start);
        auto dist_to_end = CGAL::squared_distance(nearest_e, end);
        auto m = max(dist_to_start, dist_to_end);

        // mission is successful if start/end are covered and there is a path
        if (m <= p / 4 && ufp.find_set(nearest_s_id) == ufp.find_set(nearest_e_id))
        {
            cout << "y";
            // This mission is possible, find out the minimal power such that it still succeeds
            for (; itb != edges.end() && ufb.find_set(nearest_s_id) != ufb.find_set(nearest_e_id); itb++)
            {
                ufb.union_set(itb->start_id, itb->end_id);
            }
            // make sure minimal energy still covers start / end
            min_power_b = max(min_power_b, ceil(4 * m));
        }
        else
        {
            cout << "n";
            // This mission fails, see what power is need to make it succeed
            for (; ita != edges.end() && ufa.find_set(nearest_s_id) != ufa.find_set(nearest_e_id); ita++)
            {
                ufa.union_set(ita->start_id, ita->end_id);
            }
            // make sure minimal energy still covers start / end
            min_power_a = max(min_power_a, ceil(4 * m));
        }
    }
    if (itb != edges.begin())
        min_power_b = max(min_power_b, (itb - 1)->length);
    if (ita != edges.begin())
        min_power_a = max(min_power_a, (ita - 1)->length);
    cout << "\n";
    cout << max(min_power_a, min_power_b) << "\n";
    cout << min_power_b << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    size_t t;
    cin >> t;
    while (t--)
    {
        run();
    }
}