// STL includes
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
// Namespaces
// using namespace std;
// using namespace boost;

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, Traits::edge_descriptor>>>>
    Graph;
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder
{
    Graph &G;
    EdgeCapacityMap &capacitymap;
    ReverseEdgeMap &revedgemap;

  public:
    // to initialize the Object
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap) : G(G), capacitymap(capacitymap), revedgemap(revedgemap) {}

    // to use the Function (add an edge)
    Edge addEdge(int from, int to, long capacity)
    {
        Edge e, rev_e;
        bool success;
        boost::tie(e, success) = boost::add_edge(from, to, G);
        boost::tie(rev_e, success) = boost::add_edge(to, from, G);
        capacitymap[e] = capacity;
        capacitymap[rev_e] = 0; // reverse edge has no capacity!
        revedgemap[e] = rev_e;
        revedgemap[rev_e] = e;
        return e;
    }
};

using namespace std;

// maps A to 0, B to 1, C to 2, etc.
int CharToInt(char c)
{
    return (int)(c)-65;
}

void run()
{
    int h, w;
    cin >> h >> w;
    string note_string;
    cin >> note_string;

    // count occurence of every letter
    vector<int> letters(26);
    for (auto c : note_string)
        letters[CharToInt(c)]++;

    vector<char> front(h * w);
    vector<char> back(h * w);

    for (int i = 0; i < h * w; i++)
        cin >> front[i];

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> back[i * w + w - 1 - j];

    // Create Graph and Maps
    Graph G(26);
    Vertex src = boost::add_vertex(G);
    Vertex sink = boost::add_vertex(G);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eag(G, capacitymap, revedgemap);

    // add edge from source to specific letters with the demand of the repspective letter as capacity
    for (int i = 0; i < 26; i++)
        eag.addEdge(src, i, letters[i]);

    // for every double sided letter add an edge between these letters to a new helper node and from there to the sink
    map<pair<char, char>, Edge> combs;
    for (int i = 0; i < h * w; i++)
    {
        char first = front[i] < back[i] ? front[i] : back[i];
        char second = front[i] > back[i] ? front[i] : back[i];

        if (first == second)
        {
            eag.addEdge(CharToInt(front[i]), sink, 1);
            continue;
        }

        if (combs.find(make_pair(first, second)) != combs.end())
        {
            capacitymap[combs[make_pair(first, second)]]++;
            continue;
        }

        Vertex helper = boost::add_vertex(G);
        eag.addEdge(CharToInt(first), helper, INT32_MAX);
        eag.addEdge(CharToInt(second), helper, INT32_MAX);
        Edge e = eag.addEdge(helper, sink, 1);
        combs[make_pair(first, second)] = e;
    }

    // calculate flow
    long flow = boost::push_relabel_max_flow(G, src, sink);

    if (flow == note_string.length())
        cout << "Yes";
    else
        cout << "No";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
        run();
}