//std
#include <iostream>
#include <vector>
#include <set>

// BGL
#include<boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor VertexDescriptor;
const VertexDescriptor NULL_VERTEX = boost::graph_traits<Graph>::null_vertex(); 

bool common (vector<string> &h1, vector<string> &h2, int k){
    int i1 = 0;
    int i2 = 0;

    while (i1 < h1.size() && i2 < h2.size() && k > 0){
        if (h1[i1] == h2[i2]){
            k--;
            i1++;
            i2++;
            continue;
        }
        if (h1[i1] < h2[i2]){
            i1++;
            continue;
        }
        if (h1[i1] > h2[i2]){
            i2++;
            continue;
        }
    }
    return k <= 0;
}

void run(){

    int n, c, f; cin >> n >> c >> f;
    Graph G(n);

    vector<vector<string>> interests(n, vector<string>(c));

    // read interests of buddies
    for (int i = 0; i < n; i++){
        for(int j = 0; j < c; j++){
            cin >> interests[i][j];
        }
        sort(interests[i].begin(), interests[i].end());
    }

    // add an edge between two buddies if they share at least f+1 interests
    for (int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if (common(interests[i], interests[j], f+1)){
                add_edge(i, j, G);
            }
        }
    } 

    // compute a maximum matching
    vector<VertexDescriptor> mate(n);
    edmonds_maximum_cardinality_matching(G, &mate[0]);

    // check if matching is perfect
    bool full = true;
    for (int i = 0; i < n; i++){
        if (mate[i] == NULL_VERTEX){
            full = false;
            break;
        }
    }

   cout << (full ? "not optimal" : "optimal") << "\n";
}

int main(){ 
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}
