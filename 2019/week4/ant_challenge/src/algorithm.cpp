#include <iostream>
#include <vector>

// BGL
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int>>
    graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_iter;

using namespace std;

void run()
{
    int n, e, s, a, b;
    cin >> n >> e >> s >> a >> b;

    graph final_graph(n);
    weight_map wm_final = boost::get(boost::edge_weight, final_graph);

    vector<pair<int, int>> edges(e);
    vector<vector<int>> times(s, vector<int>(e));

    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        edges[i] = make_pair(u, v);
        for (int j = 0; j < s; j++)
        {
            int t;
            cin >> t;
            times[j][i] = t;
        }
    }

    vector<int> hives(s);
    for (int i = 0; i < s; i++)
        cin >> hives[i];

    // build a graph for every species and run prim on it and add all edges to final graph
    for (int i = 0; i < s; i++)
    {
        graph G(n);
        weight_map wm = boost::get(boost::edge_weight, G);
        for (int j = 0; j < e; j++)
        {
            edge_desc e;
            e = add_edge(edges[j].first, edges[j].second, G).first;
            wm[e] = times[i][j];
        }

        // run prim (well no, there is no code snippet. try kruskal instead)
        vector<edge_desc> mst; // vector to store MST edges (not a property map!)
        kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

        // add every edge with weight to final graph
        for (auto e : mst)
        {
            edge_desc ef = add_edge(source(e, G), target(e, G), final_graph).first;
            wm_final[ef] = wm[e];
        }
    }

    // after all this crap, finally run dijkstra from a to b
    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(final_graph, a,
                                   boost::distance_map(boost::make_iterator_property_map(
                                       dist_map.begin(), boost::get(boost::vertex_index, final_graph))));

    cout << dist_map[b] << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
