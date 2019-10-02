#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cassert>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
                              boost::no_property,                           // interior properties of vertices
                              boost::property<boost::edge_weight_t, int>    // interior properties of edges
                              >
    Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;                 // Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;             // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;                 // to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIt;          // to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap; // property map to access the interior property edge_weight_t

using namespace std;

// returns the largest edge between u and v in a spanning tree G
void largestSegment(Graph &G, int n, int from, vector<vector<int>> &weights, vector<vector<int>> &store)
{
    stack<int> s;
    unordered_map<int, bool> visited; // normal map is too slow
    s.push(from);
    vector<int> max_segment(n);
    store[from][from] = 0;
    visited[from] = true;

    while (!s.empty())
    {
        int current = s.top();
        s.pop();

        // find all neighbours
        OutEdgeIt oebeg, oeend;
        for (boost::tie(oebeg, oeend) = boost::out_edges(current, G); oebeg != oeend; ++oebeg)
        {
            Vertex u = boost::source(*oebeg, G);
            Vertex v = boost::target(*oebeg, G);
            if (visited[v])
                continue;

            store[from][v] = max(store[from][current], weights[u][v]);
            visited[v] = true;
            s.push(v);
        }
    }
}

void run()
{
    int n, i;
    cin >> n >> i;
    i--; // Fucking 1 indexing

    Graph G(n);
    WeightMap weightmap = boost::get(boost::edge_weight, G);
    vector<vector<int>> weights(n, vector<int>(n, -1));

    // build graph
    for (int j = 0; j < n - 1; j++)
    {
        for (int k = j + 1; k < n; k++)
        {
            int cost;
            cin >> cost;
            Edge e;
            bool success;
            boost::tie(e, success) = boost::add_edge(j, k, G);
            weightmap[e] = cost;
            weights[j][k] = cost;
            weights[k][j] = cost;
        }
    }

    // Princess Leia basically runs Prims MST algorithm, get her spanning tree (must not even be hers, just some minimal)
    vector<Vertex> primpredmap(n);
    boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(primpredmap.begin(), boost::get(boost::vertex_index, G)),
                                      boost::root_vertex(i));

    // iterate over all edges of the original graph, if edge is in spanning tree add it to new graph
    // if not, add it to a vector

    vector<pair<int, int>> notMST;
    vector<vector<bool>> added(n, vector<bool>(n, false));
    Graph Spanning(n);
    int weight_optimal = 0;

    for (int i = 0; i < n; ++i)
    {
        Vertex u = i;
        OutEdgeIt oebeg, oeend;
        for (boost::tie(oebeg, oeend) = boost::out_edges(u, G); oebeg != oeend; ++oebeg)
        {
            Vertex v = boost::target(*oebeg, G);
            if (primpredmap[u] == v) // in spanning tree
            {
                boost::add_edge(u, v, Spanning);
                weight_optimal += weights[u][v];
            }
            else if (primpredmap[v] != u) // u-v not in spanning tree and v-u not in spanning tree
            {
                // make sure to only add this edge once
                if (!added[u][v] && !added[v][u])
                {
                    notMST.push_back(make_pair(u, v));
                    added[u][v] = true;
                }
            }
        }
    }

    // for all the (u, v) not in the spanning tree, "add" them to the spanning tree and remove the largest edge between u and v
    // in the original spanning tree to be cycle free again
    int second_min = INT32_MAX;
    vector<vector<int>> largest_segment(n, vector<int>(n, -1));
    for (auto edge : notMST)
    {
        int w = weights[edge.first][edge.second];
        if (largest_segment[edge.first][edge.second] == -1)
            largestSegment(Spanning, n, edge.first, weights, largest_segment);
        second_min = min(second_min, weight_optimal - largest_segment[edge.first][edge.second] + w);
    }

    cout << second_min << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}