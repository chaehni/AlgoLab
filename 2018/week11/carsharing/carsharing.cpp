#include <iostream>
#include <set>
#include <map>

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

struct B
{
    int s, t, d, a, p;
};

using namespace std;

void run()
{
    int n, s;
    cin >> n >> s;

    vector<int> cars(s);
    for (int i = 0; i < s; i++)
        cin >> cars[i];

    int latest = 0;
    vector<B> b(n);
    vector<set<int>> times(s);

    for (int i = 0; i < n; i++)
    {
        int start, target, dep, arr, prof;
        cin >> start >> target >> dep >> arr >> prof;
        start--;
        target--; // make station indices zero-based
        b[i] = {start, target, dep, arr, prof};
        latest = max(latest, arr);
        times[start].insert(dep);
        times[target].insert(arr);
    }

    // add time 0 and latest to every set
    for (int i = 0; i < s; i++)
    {
        times[i].insert(0);
        times[i].insert(latest);
    }

    // crate a map mapping (station, time) to a vertice number
    map<pair<int, int>, int> indices;
    int cnt = 0;
    for (int i = 0; i < s; i++)
    {
        for (int t : times[i])
            indices[{i, t}] = cnt++;
    }

    // build the space-time graph
    Graph G(cnt);
    Vertex src = add_vertex(G);
    Vertex sink = add_vertex(G);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, weightmap, revedgemap);

    // add edge from source to time 0 of every station with number of cars
    for (int i = 0; i < s; i++)
        eag.addEdge(src, indices[{i, 0}], cars[i], 0);

    // add edge from latest time of every station to sink
    for (int i = 0; i < s; i++)
        eag.addEdge(indices[{i, latest}], sink, INT32_MAX, 0);

    // add edge between times for every station
    for (int i = 0; i < s; i++)
        for (auto it = times[i].begin(); it != prev(times[i].end()); it++)
            eag.addEdge(indices[{i, *it}], indices[{i, *next(it)}], INT32_MAX, (*next(it) - *it) * 100);

    // add edges for every booking request
    for (int i = 0; i < n; i++)
        eag.addEdge(indices[{b[i].s, b[i].d}], indices[{b[i].t, b[i].a}], 1,
                    (b[i].a - b[i].d) * 100 - b[i].p);

    // compute profit and flow
    boost::successive_shortest_path_nonnegative_weights(G, src, sink);
    long inv_profit = boost::find_flow_cost(G);

    long flow = 0;
    OutEdgeIt e, eend;
    for (boost::tie(e, eend) = boost::out_edges(boost::vertex(src, G), G); e != eend; ++e)
        flow += capacitymap[*e] - rescapacitymap[*e];

    cout << flow * latest * 100 - inv_profit << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}