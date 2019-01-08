#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

struct Species
{
    string name;
    int age;
    vector<string> children;
};

struct Query
{
    int index;
    int age;
    string species;
};

void run()
{
    int n, q;
    cin >> n >> q;
    map<string, Species> species;
    int max_age = 0;
    string luca;

    // read species
    for (int i = 0; i < n; i++)
    {
        string name;
        int age;
        cin >> name >> age;
        species[name] = {name, age, vector<string>()};
        if (age > max_age)
        {
            max_age = age;
            luca = name;
        }
    }

    // read offspring relations
    for (int i = 0; i < n - 1; i++)
    {
        string off, ances;
        cin >> off >> ances;
        species[ances].children.push_back(off);
    }

    // read queries
    vector<string> results(q);
    map<string, vector<Query>> query_species;
    for (int i = 0; i < q; i++)
    {
        string s;
        int age;
        cin >> s >> age;
        Query q = {i, age, s};
        query_species[s].push_back({i, age, s});
    }

    // run DFS starting from root and for every found species run all queries for that species in a binary search
    stack<Species> s;
    vector<pair<string, int>> segment; // this contains the ages from root to current species
    map<string, bool> visited;
    s.push(species[luca]);
    visited[luca] == true;

    while (!s.empty())
    {
        Species current = s.top();

        // if we have seen this node already, we are done with children and can remove this species from stack and segment
        // (Note: we can not pop it immediately the first time we see it, since we have to leave the age value in the segment for the children queries to succeed)
        if (visited[current.name])
        {
            s.pop();
            segment.pop_back();
            continue;
        }

        // add current species to segment
        segment.push_back(make_pair(current.name, current.age));

        // the segment now contains ages for all species from root to current species
        // run all queries for current species

        for (Query q : query_species[current.name])
        {
            int l = segment.size() - 1;
            int u = 0;
            while (l != u)
            {
                int m = (l + u) / 2; // rounding down since we want the largest that is not too large and larger numbers have smaller indices
                if (segment[m].second > q.age)
                    u = m + 1;
                else
                    l = m;
            }
            results[q.index] = segment[u].first;
        }

        // for each of the children push them on to the stack
        for (auto c : current.children)
            s.push(species[c]);

        visited[current.name] = true;
    }

    // print all query results
    for (auto q : results)
        cout << q << " ";
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