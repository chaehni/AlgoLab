#include <iostream>
#include <vector>
#include <queue>

// Boost
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

void run()
{
    int g, s, l;
    cin >> g >> s >> l;
    Graph G(g + s);

    for (int i = 0; i < l; i++)
    {
        int from, to;
        cin >> from >> to;
        Edge e;
        bool success;
        tie(e, success) = add_edge(from, to + g, G);
        assert(success);
    }

    // In a bipartite graph the number of vertices in a min-vertex-cover equals the size of a maximum matching and can be constructed from the same
    // Compute maximum matching
    vector<int> mates(g + s);
    checked_edmonds_maximum_cardinality_matching(G, &mates[0]);

    // Step 1: Find all unmatched vertices in L (ground stations) and label them as visited (in next step)
    queue<int> q;
    vector<int> visited(g + s, false);
    for (int i = 0; i < g; ++i)
    {
        if (mates[i] == graph_traits<Graph>::null_vertex())
        {
            q.push(i);
        }
    }

    // Step 2: For all visited vertices in L, follow edges not contained in matching to R (satellites),
    // mark satellite as visited and follow back edge in matching and mark ground station
    while (!q.empty())
    {
        int from = q.front();
        q.pop();
        visited[from] = true;

        OutEdgeIt oeit, oeend;
        for (tie(oeit, oeend) = out_edges(from, G); oeit != oeend; ++oeit)
        {
            int to = target(*oeit, G);
            int m = mates[from];
            if (visited[to])
                continue;

            // either from is in L -> push neighbours not in matching
            // or from is in R -> push neighbours in matching
            if ((from < g && to != m) || (from >= g && to == m))
                q.push(to);
        }
    }

    // Step 3: MinVC are all unvisited in L and all visited in R
    vector<int> unvGround;
    vector<int> visSatellite;
    for (int i = 0; i < g; i++)
    {
        if (!visited[i])
            unvGround.push_back(i);
    }
    for (int i = g; i < g + s; i++)
    {
        if (visited[i])
            visSatellite.push_back(i - g);
    }

    cout << unvGround.size() << " " << visSatellite.size() << "\n";
    for (int i = 0; i < unvGround.size(); i++)
        cout << unvGround[i] << " ";
    for (int i = 0; i < visSatellite.size(); i++)
        cout << visSatellite[i] << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
    {
        run();
    }
}