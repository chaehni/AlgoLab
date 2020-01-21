#include <iostream>
#include <vector>
#include <algorithm>

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
    void add_edge(int from, int to, long capacity, long cost)
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
    }
};

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;
    vector<int> cap(n - 1);
    vector<vector<vector<int>>> items(n - 1, vector<vector<int>>(n));
    int max_sig = 1 << 7;

    for (int i = 0; i < n - 1; i++)
        cin >> cap[i];

    for (int i = 0; i < m; i++)
    {
        int a, b, d;
        cin >> a >> b >> d;
        items[a][b].push_back(d);
    }

    graph G(n);
    edge_adder eag(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    int src = add_vertex(G);
    int dst = add_vertex(G);

    // connect all stops to src and sink
    for (int i = 0; i < n - 1; i++)
    {
        eag.add_edge(src, i, cap[i], 0);
        eag.add_edge(i + 1, dst, cap[i], 0);
    }

    // add capacity links between stops
    for (int i = 0; i < n - 1; i++)
        eag.add_edge(i, i + 1, cap[i], max_sig);

    // add links for every item
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // find bottle neck from i to j
            int min_cap = INT32_MAX;
            for (int l = i; l < j; l++)
                min_cap = min(min_cap, cap[l]);

            if (items[i][j].size() > min_cap)
            {
                sort(items[i][j].begin(), items[i][j].end(), [](int a, int b) { return a > b; });
                for (int k = 0; k < min_cap; k++)
                    eag.add_edge(i, j, 1, (j - i) * max_sig - items[i][j][k]);
            }
            else
            {
                for (int sig : items[i][j])
                    eag.add_edge(i, j, 1, (j - i) * max_sig - sig);
            }
        }
    }

    // calculate min cost flow
    boost::successive_shortest_path_nonnegative_weights(G, src, dst);
    long cost = boost::find_flow_cost(G);
    long flow = 0;
    out_edge_it e, eend;
    for (boost::tie(e, eend) = boost::out_edges(boost::vertex(src, G), G); e != eend; ++e)
        flow += c_map[*e] - rc_map[*e];

    cout << flow * max_sig - cost << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}