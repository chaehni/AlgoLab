#include <iostream>
#include <vector>
#include <cassert>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
                              boost::no_property,                         // interior properties of vertices
                              boost::property<boost::edge_weight_t, int>  // interior properties of edges
                              >
    Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;                 // Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;             // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;                 // to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIt;          // to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap; // property map to access the interior property edge_weight_t

using namespace std;

int const IN = 0;
int const OUT = 1;

int getIndex(int i, int j, int inOut)
{
    // return i * (i + 1) + 2 * j + inOut;
    return i * k + 2 * j + inOut;
}

Edge addEdge(int from, int to, int weight, Graph &G, WeightMap &wm)
{
    Edge e;
    bool success;
    boost::tie(e, success) = boost::add_edge(from, to, G);
    wm[e] = weight;
    return e;
}

void tryAdd(int out, int i, int j, int k, int weight, Graph &G, WeightMap &wm)
{
    if (!(i >= k || i < 0 || j > i || j < 0))
        addEdge(out, getIndex(i, j, IN), weight, G, wm);
}

void run()
{
    int k;
    cin >> k;
    int V = k * (k + 1);
    Graph G(V); // we split vertices into in- and out-nodes to modell the vertex weight
    WeightMap wm = boost::get(boost::edge_weight, G);

    // build the graph
    // the out-vertex index is in-vertex index + 1
    vector<int> in_nodes;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            // create a get index function
            int w;
            cin >> w;

            // add edge between in and out
            in_nodes.push_back(getIndex(i, j, IN));
            int out = getIndex(i, j, OUT);
            addEdge(getIndex(i, j, IN), out, w, G, wm);

            // try adding upto 6 neighbouring edges
            tryAdd(out, i - 1, j - 1, k, 0, G, wm);
            tryAdd(out, i - 1, j, k, 0, G, wm);
            tryAdd(out, i, j - 1, k, 0, G, wm);
            tryAdd(out, i, j + 1, k, 0, G, wm);
            tryAdd(out, i + 1, j, k, 0, G, wm);
            tryAdd(out, i + 1, j + 1, k, 0, G, wm);
        }
    }

    // run Dijkstra from all 3 corners
    vector<vector<int>> distmaps(3, vector<int>(V));
    boost::dijkstra_shortest_paths(G, getIndex(0, 0, IN),
                                   distance_map(boost::make_iterator_property_map(distmaps[0].begin(), boost::get(boost::vertex_index, G))));
    boost::dijkstra_shortest_paths(G, getIndex(k - 1, 0, IN),
                                   distance_map(boost::make_iterator_property_map(distmaps[1].begin(), boost::get(boost::vertex_index, G))));
    boost::dijkstra_shortest_paths(G, getIndex(k - 1, k - 1, IN),
                                   distance_map(boost::make_iterator_property_map(distmaps[2].begin(), boost::get(boost::vertex_index, G))));

    // find the middle node which minimizes the distance to the 3 corners
    int min_dist = INT32_MAX;
    for (auto n : in_nodes)
    {
        int dist = distmaps[0][n] + distmaps[1][n] + distmaps[2][n + OUT];
        min_dist = min(min_dist, dist);
    }

    cout << min_dist << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}