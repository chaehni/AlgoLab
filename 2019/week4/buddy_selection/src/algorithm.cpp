#include <iostream>
#include <vector>
#include <algorithm>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;

int match(vector<string> &a, vector<string> &b)
{
    int fst = 0;
    int snd = 0;
    int cnt = 0;

    while (fst < a.size() && snd < b.size())
    {
        if (a[fst] == b[snd])
        {
            cnt++;
            fst++;
            snd++;
        }
        else if (a[fst] < b[snd])
        {
            fst++;
        }
        else
        {
            snd++;
        }
    }
    return cnt;
}

void run()
{
    int n, c, f;
    cin >> n >> c >> f;

    graph G(n);

    vector<vector<string>> hobbies(n, vector<string>(c));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < c; j++)
            cin >> hobbies[i][j];

        // sort vector
        sort(hobbies[i].begin(), hobbies[i].end());
    }

    // compare all students with each other
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (match(hobbies[i], hobbies[j]) > f)
                add_edge(i, j, G);

    // try to find a matching
    vector<vertex_desc> mate_map(n);
    boost::edmonds_maximum_cardinality_matching(G,
                                                boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,
                                             boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    if (matching_size == n / 2)
        cout << "not optimal\n";
    else
        cout << "optimal\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
