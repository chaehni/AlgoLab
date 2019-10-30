#include <iostream>
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_capacity_t, long,
                                              boost::property<boost::edge_residual_capacity_t, long,
                                                              boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>>
    graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}

    void add_edge(int from, int to, long capacity)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

using namespace std;

int letter_to_int(char l)
{
    return int(l) - 65;
}

void run()
{
    int h, w;
    cin >> h >> w;
    string note;
    cin >> note;

    // create vector of front-back pairs of letters
    vector<pair<char, char>> letters(h * w);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> letters[i * w + j].first;

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> letters[i * w + (w - j - 1)].second;

    graph G(26);
    edge_adder eag(G);
    int src = add_vertex(G);
    int sink = add_vertex(G);

    // count occurence of letters in note
    vector<int> note_cnt(26, 0);
    for (char c : note)
        note_cnt[letter_to_int(c)]++;

    // connect all letters from note to sink
    for (int i = 0; i < 26; i++)
        eag.add_edge(i, sink, note_cnt[i]);

    // note how many times, for a given letter, the same letters occur on its back
    // and how many times a letter occurs on the front
    vector<vector<int>> cnts(26, vector<int>(26, 0)); // keeps track of how many times a letter has a given letter on its back
    vector<int> on_front(26, 0);                      // keeps track of how many times a letter appears on the front
    for (auto p : letters)
    {
        cnts[letter_to_int(p.first)][letter_to_int(p.second)]++;
        on_front[letter_to_int(p.first)]++;
    }

    // for all letters in newspaper, add edges
    for (int i = 0; i < 26; i++)
    {
        eag.add_edge(src, i, on_front[i]);
        for (int j = 0; j < 26; j++)
            eag.add_edge(i, j, cnts[i][j]);
    }

    long flow = boost::push_relabel_max_flow(G, src, sink);

    if (flow == note.size())
        cout << "Yes\n";
    else
        cout << "No\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
