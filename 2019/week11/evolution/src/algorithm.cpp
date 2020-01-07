#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

struct speciesy
{
    int index;
    int age;
    string name;
};

void run()
{
    int n, q;
    cin >> n >> q;
    unordered_map<string, specie> m;           // maps from name to species
    vector<vector<species>> tree(n);           // save species in the tree with their name and age (index is implicit)
    typedef pair<int, int> query;              // a query is defined as the index of a specie and an age
    vector<vector<pair<int, int>>> queries(n); // records all the queries for a given species by the index of the query and the age to query
    vector<pair<int, string>> answers(q);      // holds the answers to the queries (index of query and name)

    int max_age = 0;
    string luca;
    // read all species
    for (int i = 0; i < n; i++)
    {
        string name;
        int age;
        cin >> name >> age;
        m[name] = make_pair(i, age);
        if (age > max_age)
        {
            max_age = age;
            luca = name;
        }
    }

    // build tree of life
    for (int i = 0; i < n - 1; i++)
    {
        string child, parent;
        cin >> child >> parent;
        int child_age = m[child].second;
        int parent_id = m[parent].first;
        tree[parent_id].emplace_back(child, child_age);
    }

    for (int i = 0; i < q; i++)
    {
        string s;
        int a;
        cin >> s >> a;
        queries[m[s].first].emplace_back(i, a);
    }

    // run DFS from LUCA and for every discovered species answer all queries
    stack<specie> s;
    unordered_map<int, bool> visited;
    vector<specie> leg;
    specie l = m[luca];
    s.push(l);
    visited[l.first] == true;
    leg.push_back(l);

    while (!s.empty())
    {
        specie curr = s.top();

        // if we came back to this species we have handled it and all its children - > pop it
        if (visited[curr.first])
        {
            s.pop();
            leg.pop_back();
            continue;
        }

        // if we have not seen this species, add it to the leg and run all it's queries
        leg.push_back(curr);

        for (auto q : queries[curr.first])
        {
            int index = q.first;
            int age = q.second;
        }
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
