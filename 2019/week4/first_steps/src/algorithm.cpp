#include <iostream>
#include <vector>
#include <algorithm>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int>>
    Graph;
typedef boost::property_map<Graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<Graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

using namespace std;

void run()
{
    int n, m;
    cin >> n >> m;
    Graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge_desc e;
        e = boost::add_edge(u, v, G).first;
        weights[e] = w;
    }

    vector<int> dist_map(n);
    dijkstra_shortest_paths(G, 0,
                            boost::distance_map(boost::make_iterator_property_map(
                                dist_map.begin(), boost::get(boost::vertex_index, G))));

    int max_dist = 0;
    for (int dist : dist_map)
        max_dist = max(max_dist, dist);

    vector<edge_desc> mst;
    kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    int weight = 0;
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it)
    {
        weight += weights[*it];
    }

    cout << weight << " " << max_dist << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
