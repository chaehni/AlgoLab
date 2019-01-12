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

    int n, m, k, t; cin >> n >> m >> k >> t;
    Graph G(2*n);
    WeightMap weights = get(edge_weight, G);

    set<int> telnet;
    for (int i = 0; i < t; i++){
        int temp; cin >> temp;
        telnet.insert(temp);
    }

    for (int i = 0; i < m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        bool added;
        Edge e;
        tie(e, added) = add_edge(v, u, G); weights[e] = c; // add edges in reverse
    }

    vector<int> scc(2*n);
    int c = boost::strong_components(G, make_iterator_property_map(scc.begin(), get(boost::vertex_index, G)));

    vector<int> comps(c);

    // keep track of how many nodes are in each component (used for weight of added edges)
    for (auto e: telnet){
        comps[scc[e]]++;
    }

    // add "middle man" nodes per component to avoid nested loop
    // every node of the same component connects to a new node via edge with weight t(u)
    // from that new node it can reach every other node in the same component for free
    for (auto i: telnet){
        bool added;
        Edge e;
        tie(e, added) = add_edge(i, n + scc[i], G); weights[e] = comps[scc[i]]-1;
        Edge f;
        tie(f, added) = add_edge(n + scc[i], i, G); weights[f] = 0;
    }

    // all edges added, run Dijkstra all k factories to find solution
    // start is delivery planet (n-1)
    vector<int> dists(2*n);
    dijkstra_shortest_paths(G, n-1, distance_map(make_iterator_property_map(dists.begin(), get(vertex_index, G))));
    int deliver = 1000001;
    for (int i = 0; i < k; i++){
        if (dists[i] < deliver)
            deliver = dists[i];
    }

    if (deliver > 1000000)
        cout << "no" << "\n";
    else cout << deliver << "\n";
    

}

int main(){ 
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}