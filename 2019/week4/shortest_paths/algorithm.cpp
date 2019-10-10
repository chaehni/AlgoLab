//std
#include <iostream>
#include <vector>
#include <set>
#include <map>

// BGL
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> Graph;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef Graph::edge_descriptor Edge;

void run(){

    int n, m, q; cin >> n >> m >> q;
    Graph G(n);
    WeightMap weights = get(edge_weight, G);

    int ignore;
    for (int i = 0; i < n; i++){
        cin >> ignore >> ignore;
    }

    for (int i = 0; i < m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        bool added;
        Edge e;
        tie(e, added) = add_edge(u, v, G); weights[e] = c;
    }

    for (int i = 0; i < q; i++){
        int s, t;
        cin >> s >> t;

        vector<int> dists(n);
        dijkstra_shortest_paths(G, s, distance_map(make_iterator_property_map(dists.begin(), get(vertex_index, G))));

        int dist = dists[t];
        if (dist == INT32_MAX)
            cout << "unreachable" << "\n";
        else
            cout << dist << "\n";
    }
}

int main(){ 
    ios_base::sync_with_stdio(false);
    run();
}
