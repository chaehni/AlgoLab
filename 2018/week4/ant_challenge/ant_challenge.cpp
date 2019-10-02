//std
#include <iostream>
#include <vector>

// BGL
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, allow_parallel_edge_tag, property<edge_weight_t, int>> Graph;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef Graph::edge_descriptor Edge;

void run(){

    int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
    Graph species_graphs[s];
    Graph F(n);
    WeightMap species_wm[s];
    WeightMap wmf = get(edge_weight, F);

    for (int i = 0; i < e; i++){
        int t1, t2; cin >> t1 >> t2;
        for (int j = 0; j < s; j++){
            species_wm[j] = get(edge_weight, species_graphs[j]);
            int temp; cin >> temp;

            bool success;
            Edge e;
            tie(e, success) = add_edge(t1, t2, species_graphs[j]);
            species_wm[j][e] = temp;
        }
    }

    // waste the the hive locations
    for (int i = 0; i < s; i++){
        int temp; cin >> temp;
    }
   
    // run Kruskal for every species and add all edges to the final graph
    for (int i = 0; i < s; i++){
        vector<Edge> mst;
        kruskal_minimum_spanning_tree(species_graphs[i], back_inserter(mst));
        for (auto k: mst){
            bool success;
            Edge e;
            tie(e, success) = add_edge(source(k, species_graphs[i]), target(k, species_graphs[i]), F);
            wmf[e] = get(edge_weight_t(), species_graphs[i], k);
        }
    }

    vector<int> dists(n);
    dijkstra_shortest_paths(F, a, distance_map(make_iterator_property_map(dists.begin(), get(vertex_index, F))));

    cout << dists[b] << "\n";
}

int main(){ 
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}