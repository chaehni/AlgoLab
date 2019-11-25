#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                                                                              boost::property<boost::edge_weight_t, long>>>>>
    graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it; // Iterator

// Custom edge adder class
class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}
    edge_desc add_edge(int from, int to, long capacity, long cost)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        auto w_map = boost::get(boost::edge_weight, G); // new!
        const edge_desc e = boost::add_edge(from, to, G).first;
        const edge_desc rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
        w_map[e] = cost;      // new assign cost
        w_map[rev_e] = -cost; // new negative cost
        return e;
    }
};

using namespace std;

void run()
{
    int c, g, b, k, a;
    cin >> c >> g >> b >> k >> a;
    graph G(c);
    edge_adder eag(G);
    int ctrl = add_vertex(G);
    auto e = eag.add_edge(ctrl, k, 0, 0);
    auto c_map = boost::get(boost::edge_capacity, G);

    // add edges between cities
    for (int i = 0; i < g; i++)
    {
        int x, y, d, e;
        cin >> x >> y >> d >> e;
        eag.add_edge(x, y, e, d);
    }

    // find upper bound for a binary search
    long flow = boost::push_relabel_max_flow(G, k, a);

    // binary search to find the biggest flow that does not exceed budget
    long l = 0;
    long u = flow;

    while (l != u)
    {
        long m = (l + u + 1) / 2; // round up so that we try the bigger value if it is .5
        c_map[e] = m;
        boost::successive_shortest_path_nonnegative_weights(G, ctrl, a);
        long cost = boost::find_flow_cost(G);
        if (cost <= b)
            l = m;
        else
            u = m - 1;
    }

    cout << l << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
