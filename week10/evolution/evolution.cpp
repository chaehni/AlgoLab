#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

struct Species
{
    Species(string name, int age, vector<string> children) : name(name), age(age), children(children) {}
    string name;
    int age;
    vector<string> children;
};

struct Query
{
    Query(int index, int age, string species) : index(index), age(age), species(species) {}
    int index;
    int age;
    string species;
};
void run()
{
    int n, q;
    cin >> n >> q;
    map<string, Species> species;

    // read species
    for (int i = 0; i < n; i++)
    {
        string name;
        int age;
        cin >> name >> age;
        species[name] = Species(name, age, vector<string>());
    }

    /* // read offspring relations
    for (int i = 0; i < n - 1; i++)
    {
        string off, ances;
        cin >> off >> ances;
        species[ances].children.push_back(off);
    } */

    /*  // read queries
    vector<string> results(q);
    map<string, vector<Query>> query_species;
    for (int i = 0; i < q; i++)
    {
        string species;
        int age;
        cin >> species >> age;
        Query q(i, age, species);
        query_species[species].push_back(q);
    }

    // run DFS starting from root and for every found species run all quries for that species
    stack<Species> s;
    vector<int> segment;
    map<string, bool> visited;
    s.push(species["luca"]);
    segment.push_back(species["luca"].age);
    visited["luca"] == true;

    while (!s.empty())
    {
        Species current = s.top();

        // if we have seen this node already, we are back and can remove this species from stack and segment
        if (visited[current.name])
        {
            s.pop();
            segment.pop_back();
        }

        // the segment now contains ages for all species from root to current
        // run all queries for current

        //TODO: run binary search

        // for each of the children push
    } */
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