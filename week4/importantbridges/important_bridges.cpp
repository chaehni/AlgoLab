//std
#include <iostream>
#include <vector>

// BGL
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/graph/connected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef Graph::edge_descriptor Edge;

void correct_pair(vector<pair<int, int>> &crit, int a, int b){
    if (a < b)
        crit.push_back(make_pair(a, b));
    else crit.push_back(make_pair(b, a));
}

int compare(pair<int, int> p1, pair<int, int> p2){
    if (p1.first == p2.first)
        return p1.second < p2.second;
    else return p1.first < p2.first;

}

void run(){

    int n, m; cin >> n >> m;
    Graph G;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        edges[i] = make_pair(u,v);
        bool success;
        Edge e;
        tie(e, success) = add_edge(u, v, G);
    }

    vector<pair<int, int>> crit;
    // for every bridge, remove edge and run a connected_components
    for  (auto k: edges){
        int s = k.first;
        int t = k.second;
        remove_edge(s, t, G);
        vector<int> ccmap(n);
        int ncc = connected_components(G, make_iterator_property_map(ccmap.begin(), get(vertex_index, G)));
        if (ncc > 1){
            correct_pair(crit, s, t);
        }
        bool success;
        Edge e;
        tie(e, success) = add_edge(s, t, G);
    }

    sort(crit.begin(), crit.end(), compare);

    cout << crit.size() << "\n";
    for (auto e: crit){
        cout << e.first << " " << e.second << "\n";
    }

}

int main(){ 
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}