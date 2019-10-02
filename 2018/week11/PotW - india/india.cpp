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
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIt;

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
    int c, g, b, k, a;
    cin >> c >> g >> b >> k >> a;

    // Create Graph and Maps
    Graph G(c);
    Vertex sink = a;
    Vertex src = boost::add_vertex(G);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, weightmap, revedgemap);

    // add edges for each guide
    for (int i = 0; i < g; i++)
    {
        int x, y, d, e;
        cin >> x >> y >> d >> e;

        eag.addEdge(x, y, e, d); // guide with c elephants between cities x, y and cost d per elephant
    }

    // find upper bound for number of suitcases
    long max = boost::push_relabel_max_flow(G, k, sink);

    // add control node to be able to control number of suitcases sent
    Edge control = eag.addEdge(src, k, 1, 0);

    // we have an upper bound on number of suitcases, use binary search to find exact number
    int l = 0;
    int u = max;

    while (l != u)
    {
        int middle = (l + u + 1) / 2;
        capacitymap[control] = middle;
        boost::successive_shortest_path_nonnegative_weights(G, src, sink);
        int cost = boost::find_flow_cost(G);

        if (cost > b)
            u = middle - 1;
        else
            l = middle;
    }

    cout << l << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}