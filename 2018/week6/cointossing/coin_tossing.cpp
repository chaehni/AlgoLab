// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, Traits::edge_descriptor>>>>
    Graph;
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder
{
    Graph &G;
    EdgeCapacityMap &capacitymap;
    ReverseEdgeMap &revedgemap;

  public:
    // to initialize the Object
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap) : G(G), capacitymap(capacitymap), revedgemap(revedgemap) {}

    // to use the Function (add an edge)
    void addEdge(int from, int to, long capacity)
    {
        Edge e, rev_e;
        bool success;
        boost::tie(e, success) = boost::add_edge(from, to, G);
        boost::tie(rev_e, success) = boost::add_edge(to, from, G);
        capacitymap[e] = capacity;
        capacitymap[rev_e] = 0; // reverse edge has no capacity!
        revedgemap[e] = rev_e;
        revedgemap[rev_e] = e;
    }
};

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;

    // Create Graph and Maps
    Graph G(n + 2);
    Vertex src = n;
    Vertex sink = n + 1;
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, revedgemap);

    // place edges for each round
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (c == 1) // a wins and has one point for sure
            eag.addEdge(src, a, 1);
        if (c == 2) // b wins and has one point for sure
            eag.addEdge(src, b, 1);
        if (c == 0) // we don't know who won, make one point available to either a or b
        {
            // add intermediary node
            Vertex inter = boost::add_vertex(G);
            eag.addEdge(src, inter, 1);
            eag.addEdge(inter, a, 1);
            eag.addEdge(inter, b, 1);
        }
    }

    // add links from players to sink depending on scoreboard
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int score;
        cin >> score;
        sum += score;
        eag.addEdge(i, sink, score); // player i claims s points
    }

    if (sum != m) // they trivially lied about score
    {
        cout << "no\n";
        return;
    }

    int flow = boost::push_relabel_max_flow(G, src, sink);

    if (flow == m)
        cout << "yes";
    else
        cout << "no";
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