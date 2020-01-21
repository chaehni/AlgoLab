#include <iostream>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}

    void add_edge(int from, int to, long capacity)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

using namespace std;

void run()
{
    int n, m, s, d;
    cin >> n >> m >> s >> d;

    graph G(2 * n);
    edge_adder eag(G);
    int src = add_vertex(G);
    int sink = add_vertex(G);

    // build graph
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        eag.add_edge(2 * u + 1, 2 * v, INT32_MAX);
    }

    // connect all possible starts to source
    for (int i = 0; i < s; i++)
    {
        int start;
        cin >> start;
        eag.add_edge(src, 2 * start, 1);
    }

    // connect all possible destinations to sink
    for (int i = 0; i < d; i++)
    {
        int dest;
        cin >> dest;
        eag.add_edge(2 * dest + 1, sink, 1);
    }

    // connect node-in to node-out
    for (int i = 0; i < n; i++)
        eag.add_edge(2 * i, 2 * i + 1, 1);

    // calculate max flow
    long flow = boost::push_relabel_max_flow(G, src, sink);

    cout << flow << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
