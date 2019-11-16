#include <iostream>
#include <vector>
#include <queue>

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
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;

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
    int n, m;
    cin >> n >> m;
    graph G(n);
    edge_adder eag(G);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        eag.add_edge(a, b, c);
    }

    long min_flow = INT64_MAX;
    int start;
    int end;
    for (int i = 0; i < n; i++)
    {
        long flow = boost::push_relabel_max_flow(G, i, (i + 1) % n);
        if (flow < min_flow)
        {
            min_flow = flow;
            start = i;
            end = (i + 1) % n;
        }
        min_flow = min(min_flow, boost::push_relabel_max_flow(G, i, (i + 1) % n));
    }

    // run the best flow again to set edge and reverse edge capacity right
    // then run BFS to find all reachable nodes from start in residual graph
    long flow = boost::push_relabel_max_flow(G, start, end);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    int cnt = 1;
    std::vector<int> vis(n, false); // visited flags
    std::queue<int> q;              // BFS queue (from std:: not boost::)
    vis[start] = true;              // Mark the source as visited
    q.push(start);
    while (!q.empty())
    {
        const int u = q.front();
        q.pop();
        out_edge_it ebeg, eend;
        for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg)
        {
            const int v = boost::target(*ebeg, G);
            // Only follow edges with spare capacity
            if (rc_map[*ebeg] == 0 || vis[v])
                continue;
            vis[v] = true;
            cnt++;
            q.push(v);
        }
    }

    cout << min_flow << "\n";
    cout << cnt << " ";
    for (int i = 0; i < n; ++i)   
    {
        if (vis[i])
            cout << i << " ";
    }
    std::cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
