#include <iostream>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>
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
    int w, n;
    cin >> w >> n;
    graph G(2 * (w + 1));
    int src = 1;
    int sink = 2 * w;
    edge_adder eag(G);

    /*
    ### Node layout ###
    0  --1->  1     2  --1->  3     4  --1->  5  ...   2w  --1->  2w-1 
    |__node0__|     |__node1__|     |__node2__|        |____nodew____|
       
              ^                                        ^
              |                                        |
            source                                    sink
    */

    // add vertex capacities
    for (int i = 0; i <= w; i++)
        eag.add_edge(2 * i, 2 * i + 1, 1);

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (b < a)
            swap(a, b);
        eag.add_edge(2 * a + 1, 2 * b, 1);
    }

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
