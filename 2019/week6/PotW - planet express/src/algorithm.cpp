#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int>>
    graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;

void run()
{
    int n, m, k, t;
    cin >> n >> m >> k >> t;

    vector<int> telnet(t);
    for (int i = 0; i < t; i++)
        cin >> telnet[i];

    // build graph
    graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        edge_desc e = boost::add_edge(v, u, G).first; // add edge in reverse because we run dijkstra from target to all warehouses
        weights[e] = c;
    }

    // get strong components (meaining sets of vertices which are reachable from each other in both directions)
    // scc_map[i]: index of SCC containing i-th vertex
    vector<int> scc_map(n); // exterior property map
    // nscc: total number of SCCs
    int nscc = boost::strong_components(G,
                                        boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));

    vector<int> num(nscc, 0);
    for (int node : telnet)
        num[scc_map[node]]++;

    // for every strong component add a central hub node
    vector<int> hub(nscc);
    for (int i = 0; i < nscc; i++)
        hub[i] = boost::add_vertex(G);

    // add additional edges between nodes in telnet to the hub of their strong component
    for (int node : telnet)
    {
        // add edge to hub
        edge_desc e;
        e = boost::add_edge(node, hub[scc_map[node]], G).first;
        weights[e] = num[scc_map[node]] - 1; // -1 because node is not linked with itself
        // add reverse edge for free
        e = boost::add_edge(hub[scc_map[node]], node, G).first;
        weights[e] = 0;
    }

    // graph is built, now run dijkstra
    vector<int> dist_map(n + nscc);
    boost::dijkstra_shortest_paths(G, n - 1,
                                   boost::distance_map(boost::make_iterator_property_map(
                                       dist_map.begin(), boost::get(boost::vertex_index, G))));

    // check 0 to k-1 warehouse locations
    int min_time = INT32_MAX;
    for (int i = 0; i < k; i++)
        min_time = min(min_time, dist_map[i]);

    // output
    if (min_time > 1 * 1000000)
        cout << "no\n";
    else
        cout << min_time << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
