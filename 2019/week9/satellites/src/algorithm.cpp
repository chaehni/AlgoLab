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
    int g, s, l;
    cin >> g >> s >> l;
    graph G(g + s);
    int src = add_vertex(G);
    int sink = add_vertex(G);
    edge_adder eag(G);

    for (int i = 0; i < g; i++)
        eag.add_edge(src, i, 1);

    for (int i = 0; i < s; i++)
        eag.add_edge(g + i, sink, 1);

    for (int i = 0; i < l; i++)
    {
        int a, b;
        cin >> a >> b;
        eag.add_edge(a, g + b, 1);
    }

    long flow = boost::push_relabel_max_flow(G, src, sink);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    std::vector<int> vis(g + s + 2, false); // visited flags
    std::queue<int> q;                      // BFS queue (from std:: not boost::)
    vis[src] = true;                        // Mark the source as visited
    q.push(src);
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
            q.push(v);
        }
    }

    vector<int> ground;
    vector<int> sat;
    for (int i = 0; i < g; i++)
        if (!vis[i]) // unvisited in left
            ground.push_back(i);

    for (int i = 0; i < s; i++)
        if (vis[g + i]) // visited in right
            sat.push_back(i);

    cout << ground.size() << " " << sat.size() << "\n";
    for (int g : ground)
        cout << g << " ";
    for (int s : sat)
        cout << s << " ";
    if (ground.size() + sat.size() > 0)
        cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
