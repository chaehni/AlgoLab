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

void run(){

    int n, c, f; cin >> n >> c >> f;
    Graph G(n);

    vector<set<string>> interests(n);

    for (int i = 0; i<n; i++){
        for(int j = 0; j<c; j++){
            string temp;
            cin >> temp;
            interests[n].insert(temp);
        }
    }

    for (int i = 0; i<n; i++){
        for(int j = 0; j<c; j++){
            set<string> intersect;
            set_intersection(interests[i].begin(), interests[i].end(),interests[j].begin(), interests[j].end(), inserter(intersect, intersect.begin()));
            if (intersect.size() > f){
                add_edge(i, j, G);
            }
        }
    }

    vector<VertexDescriptor> mate(n);
    edmonds_maximum_cardinality_matching(G, &mate[0]);

    bool all = true;
    for (int i = 0; i < n; i++){
        if (mate[i] == NULL_VERTEX){
            all = false;
            break;
        }
    }

    cout << (all ? "optimal" : "not optimal") << "\n";
}

int main(){ 
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}
