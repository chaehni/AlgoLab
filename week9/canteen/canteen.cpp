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
typedef boost::graph_traits<Graph>::in_edge_iterator InEdgeIt;

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
        weightmap[e] = w;
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w;
        revedgemap[e] = rev_e;
        revedgemap[rev_e] = e;
    }
};

using namespace std;

void run()
{
    int days;
    cin >> days;

    // Create Graph and Maps
    Graph G(days + 2);
    int src = days;
    int sink = days + 1;
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, weightmap, revedgemap);

    int students_to_feed = 0;

    // add edge between source and days
    for (int i = 0; i < days; i++)
    {
        int menus, cost;
        cin >> menus >> cost;
        eag.addEdge(src, i, menus, cost);
    }

    // add edge between days and sink
    for (int i = 0; i < days; i++)
    {
        int students, price;
        cin >> students >> price;
        students_to_feed += students;
        eag.addEdge(i, sink, students, 20 - price); // 20 is maximum price -> invert price to not use negative numbers
    }

    // add edges between days
    for (int i = 0; i < days - 1; i++)
    {
        int storage, cost;
        cin >> storage >> cost;
        eag.addEdge(i, i + 1, storage, cost);
    }

    // compute served students and profit
    int flow = boost::push_relabel_max_flow(G, src, sink);
    boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    int cost = boost::find_flow_cost(G);

    int profit = flow * 20 - cost;

    if (flow < students_to_feed)
        cout << "impossible ";
    else
        cout << "possible ";
    cout << flow << " " << profit << "\n";
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