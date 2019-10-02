#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
     property<edge_capacity_t, long,
         property<edge_residual_capacity_t, long,
             property<edge_reverse_t, Traits::edge_descriptor>
                 > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap; 
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap; 
typedef graph_traits<Graph>::vertex_descriptor Vertex; 
typedef graph_traits<Graph>::edge_descriptor Edge;

 class EdgeAdder {
        Graph &G;
        EdgeCapacityMap	&capacitymap;
        ReverseEdgeMap	&revedgemap;

    public:
        // to initialize the Object
        EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
            G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

        // to use the Function (add an edge)
        void addEdge(int from, int to, long capacity) {
            Edge e, rev_e;
            bool success;
            tie(e, success) = add_edge(from, to, G);
            tie(rev_e, success) = add_edge(to, from, G);
            capacitymap[e] = capacity;
            capacitymap[rev_e] = 0; // reverse edge has no capacity!
            revedgemap[e] = rev_e;
            revedgemap[rev_e] = e;
        }
};

void run (){

   int l, p; cin >> l >> p;
   vector<int> loc(l);

    Graph G(l + 2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, revedgemap);

    // read the demand/capacity at each location
    // satisfy node condition by subtracting (reserving) the amount of needed soldiers
    for (int i = 0; i < l; i++){
        int stationed, needed; cin >> stationed >> needed;
        loc[i] = stationed - needed;
    }

    // add new source, sink nodes
    Vertex source = add_vertex(G);
    Vertex sink = add_vertex(G);

    // read all edges and their demand
    // "fast forward" flow algorithm to a state where demand of every edge is already met
    for (int i = 0; i < p; i++){
        int from, to, demand, capacity; cin >> from >> to >> demand >> capacity;

        // move demand soldiers along the edge from "from" to "to"
        loc[from] -= demand;
        loc[to] += demand;

        // add edge to graph
        eaG.addEdge(from, to, capacity-demand);
    }

    int flow_needed = 0;

    // Add edges between nodes and source/sink
    for (int i = 0; i < l; i++){
       if (loc[i] >= 0){ // this location has more than engough soldiers; it's a source
            eaG.addEdge(source, i, loc[i]);
       } else {
            eaG.addEdge(i, sink, -loc[i]); // this location needs soldiers; make sure we can drain the needed amount from here in the end
            flow_needed -= loc[i]; // add the number of missing soldiers to the expected flow
       }              
    }

    // Finally, calculate flow and compare to needed_flow
    long flow = push_relabel_max_flow(G, source, sink);

    if (flow >= flow_needed)
        cout << "yes\n";
    else
        cout << "no\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n--){
        run();
    }
    return 0;
}
