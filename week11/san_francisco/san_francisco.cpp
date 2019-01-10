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
    Graph; // new!
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t>::type EdgeWeightMap; // new!
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

    void addEdge(int u, int v, long c, long w)
    {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e;
        revedgemap[rev_e] = e;
    }
};

using namespace std;

void run()
{
    int n, m, x, k;
    cin >> n >> m >> x >> k;

    // Create Graph and Maps
    Graph G(n + 2);
    Vertex src = n;
    Vertex sink = n + 1;
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, weightmap, revedgemap);

    vector<int> outgoing(n, 0);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        int p;
        cin >> u >> v >> p;
        eag.addEdge(u, v, 1, -p);
        outgoing[u]++;
    }

    // connect source node
    eag.addEdge(src, 0, 1, 0);

    // add edge for every node that has no outgoing edge to sink
    for (int i = 0; i < n; i++)
    {
        if (outgoing[i] == 0)
        {
            eag.addEdge(i, sink, 1, 0);
        }
    }

    // send one unit through network
    // boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    long flow = boost::push_relabel_max_flow(G, src, sink);
    boost::cycle_canceling(G);
    int cost_slow = boost::find_flow_cost(G);
    //long cost = boost::find_flow_cost(G);

    //long points = INT32_MAX * k - cost;
    long points = -cost_slow;

    cout << points << endl;
    if (points < x)
        cout << "possible";
    else
        cout << "impossible";
    cout << "\n";
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