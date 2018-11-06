//std
#include <iostream>
#include <vector>

// BGL
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_index_t, int>> Graph;
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
        tie(e, success) = add_edge(u, v, i, G);
    }

    vector<pair<int, int>> crit;
    vector<int> bcc(m);
    int nbc = boost::biconnected_components(G, make_iterator_property_map(bcc.begin(), get(boost::edge_index, G)));
    vector<vector<pair<int, int>>> bridges_in_component(nbc);

    auto es = boost::edges(G);
    int cnt = 0;
    for (auto eit = es.first; eit!=es.second; ++eit){
        auto s = source(*eit, G);
        auto t = target(*eit, G);

        correct_pair(bridges_in_component[bcc[cnt]], s, t);
        cnt++;
    }

    for (int i=0; i < nbc; i++){
        if(bridges_in_component[i].size() == 1){
            // found critical bridge
            crit.push_back(bridges_in_component[i][0]);
        }
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
