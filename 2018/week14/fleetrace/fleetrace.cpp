#include <iostream>
#include <vector>
#include <algorithm>

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

struct Combi
{
    int b, s, c;
};

using namespace std;

void run()
{
    int B, S, P;
    cin >> B >> S >> P;

    vector<Combi> p(P);
    for (int i = 0; i < P; i++)
    {
        int b, s, c;
        cin >> b >> s >> c;
        p[i] = Combi{b, s, c};
    }

    // build Graph
    Graph G(B + S);
    Vertex src = add_vertex(G);
    Vertex sink = add_vertex(G);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, weightmap, revedgemap);

    // add edge between source and every boat
    // additionally, add an edge between the boat and the sink directly
    // the first goal of the max flow algorithm is to maximize the flow, only then minimize the cost
    // this way we give it an easy way to maximize the flow
    for (int i = 0; i < B; i++)
    {
        eag.addEdge(src, i, 1, 0);
        eag.addEdge(i, sink, 1, 50);
    }

    // add edge between sailor and every sink
    for (int i = 0; i < S; i++)
        eag.addEdge(B + i, sink, 1, 0);

    for (int i = 0; i < P; i++)
        eag.addEdge(p[i].b, B + p[i].s, 1, 50 - p[i].c);

    boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    int inv_spectacle = boost::find_flow_cost(G);

    long flow = 0;
    OutEdgeIt e, eend;
    for (boost::tie(e, eend) = boost::out_edges(boost::vertex(src, G), G); e != eend; ++e)
        flow += capacitymap[*e] - rescapacitymap[*e];

    cout << flow * 50 - inv_spectacle << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}