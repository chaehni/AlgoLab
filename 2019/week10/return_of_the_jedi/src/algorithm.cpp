#include <iostream>
#include <vector>
#include <stack>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int>>
    graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::out_edge_iterator OutEdgeIt;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

using namespace std;

void largest(graph &G, vector<vector<int>> &w, int start, vector<vector<int>> &memo)
{
    stack<int> s;
    vector<bool> visited(num_vertices(G));
    vector<int> max_seg(num_vertices(G), -1); // max_seg[i] contains the weight of the largest segment between start and i

    s.push(start);
    while (!s.empty())
    {
        int curr = s.top();
        s.pop();
        visited[curr] = true;

        // find neighbours
        OutEdgeIt beg, end;
        for (tie(beg, end) = out_edges(curr, G); beg != end; beg++)
        {
            int v = target(*beg, G);
            if (visited[v])
                continue;
            max_seg[v] = max(max_seg[curr], w[curr][v] + w[v][curr]);
            s.push(v);
        }
    }
    memo[start] = max_seg;
}

void run()
{
    int n, r;
    cin >> n >> r;
    r--;

    graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    vector<vector<int>> wgt(n, vector<int>(n, 0));

    // building the full graph
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int w;
            cin >> w;
            auto e = boost::add_edge(i, j, G).first;
            weights[e] = w;
            wgt[i][j] = w;
        }
    }

    vector<vertex_desc> pred_map(n);
    auto p = boost::make_iterator_property_map(pred_map.begin(), boost::get(boost::vertex_index, G));
    boost::prim_minimum_spanning_tree(G, p, boost::root_vertex(r));

    // build Leila's MST and save unused edges for later
    graph GL(n);
    int weight_optimal = 0;
    vector<pair<int, int>> not_mst;
    edge_it beg, end;

    for (boost::tie(beg, end) = boost::edges(G); beg != end; ++beg)
    {
        int u, v;
        u = source(*beg, G);
        v = target(*beg, G);
        if (pred_map[u] == v || pred_map[v] == u)
        {
            weight_optimal += wgt[u][v] + wgt[v][u];
            add_edge(u, v, GL);
        }
        else
        {
            not_mst.emplace_back(u, v);
        }
    }

    // for every edge (u, v) that is not in the optimal spanning tree, add it and in turn remove the most expensive edge between u and v that is in the spanning tree.
    vector<vector<int>> memo(n, vector<int>(n, -1));
    int best = INT32_MAX;
    for (auto e : not_mst)
    {
        int u = e.first;
        int v = e.second;
        if (memo[u][v] == -1)
            largest(GL, wgt, u, memo);
        best = min(best, weight_optimal + wgt[u][v] + wgt[v][u] - memo[u][v]);
    }

    cout << best << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
