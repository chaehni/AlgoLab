// STL includes
#include <iostream>
#include <cstdlib>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                                                                              boost::property<boost::edge_weight_t, long>>>>>
    Graph;
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t>::type EdgeWeightMap;
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder
{
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap &revedgemap;

  public:
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap)
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    Edge addEdge(int u, int v, long c, long w)
    {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w;
        revedgemap[e] = rev_e;
        revedgemap[rev_e] = e;
        return e;
    }
};

using namespace std;

void run()
{

    int n, m, s, f;
    cin >> n >> m >> s >> f;

    // Create Graph and Maps
    Graph G(n + 1);
    Vertex artifical_src = n;
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, weightmap, revedgemap);

    // add streets
    for (int i = 0; i < m; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        eag.addEdge(a, b, c, d);
        eag.addEdge(b, a, c, d); // streets are bidirectional
    }

    // find shortest path
    Edge e = eag.addEdge(artifical_src, s, 1, 0); // let one runner run the marathon, we need Edge handle to update capacity map
    boost::successive_shortest_path_nonnegative_weights(G, artifical_src, f);

    long length = boost::find_flow_cost(G);            // this is the shortest path, every runner should run exactly this distance
    long flow = boost::push_relabel_max_flow(G, s, f); // max number of people who can run the marathon (not necessarily all run the same length)

    if (flow == 0) // if finish is unreachable
    {
        cout << 0 << "\n";
        return;
    }

    // find the amount of runners that can run the same distance using binary search (e.g. largest flow, such that still everyone runs the same distance)
    long l = 1;
    long r = flow;
    long index = r;

    while (l != r)
    {
        index = (l + r + 1) / 2; // integer division rounding up (towards larger numbers since we look for the largest flow)
        capacitymap[e] = index;  // set amount of runners to middle point
        boost::successive_shortest_path_nonnegative_weights(G, artifical_src, f);
        long combined_length = boost::find_flow_cost(G); // total length of all runners

        if (combined_length > index * length) // too big, some runners had to run further
            r = index - 1;
        else
            l = index;
    }
    cout << r << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
    {
        run();
    }
}