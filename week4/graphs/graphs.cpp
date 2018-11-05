//std
#include <iostream>
#include <vector>
#include <set>
#include <map>

// BGL
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> Graph;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef Graph::edge_descriptor Edge;

void run(){

    int n, m; cin >> n >> m;
    Graph G(n);
    WeightMap weights = get(edge_weight, G);

   
    for (int i = 0; i < m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        bool added;
        Edge e;
        tie(e, added) = add_edge(u, v, G); weights[e] = c; // add edges in reverse
    }

    vector<Edge> mst;
    kruskal_minimum_spanning_tree(G, back_inserter(mst));
    int sync_with_stdio = 0;
    int w = 0;
    for (auto e: mst){
        w += get(edge_weight_t(), G, e);
    }

    vector<int> dists(n);
    dijkstra_shortest_paths(G, 0, distance_map(make_iterator_property_map(dists.begin(), get(vertex_index, G))));
    int d = *max_element(dists.begin(), dists.end());

    cout << w << " " << d << "\n";
}

int main(){ 
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}