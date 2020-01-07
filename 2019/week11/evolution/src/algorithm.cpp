#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

struct species
{
    int index;
    int age;
    string name;
};

void run()
{
    int n, q;
    cin >> n >> q;
    unordered_map<string, species> m;  // maps from name to species
    vector<vector<species>> tree(n);   // models the tree. Every species has a vector indices of its children
    typedef pair<int, int> query;      // a query is defined as the index of the query and an age
    vector<vector<query>> queries(n);  // records all the queries for a given species by the index of the query and the age to query
    vector<pair<int, string>> answers; // holds the answers to the queries (index of query and name)
    answers.reserve(n);

    int max_age = 0;
    string luca;
    int cnt = 0;

    // read all species
    for (int i = 0; i < n; i++)
    {
        string name;
        int age;
        cin >> name >> age;
        m[name] = species{cnt++, age, name};
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
        tree[m[parent].index].push_back(m[child]);
    }

    for (int i = 0; i < q; i++)
    {
        string s;
        int a;
        cin >> s >> a;
        queries[m[s].index].emplace_back(i, a);
    }

    // run DFS from LUCA and for every discovered species answer all queries
    stack<species> s;
    unordered_map<int, bool> visited;
    vector<species> leg;
    species l = m[luca];
    s.push(l);

    while (!s.empty())
    {
        species curr = s.top();

        // if we came back to this species we have handled it and all its children - > pop it
        if (visited[curr.index])
        {
            s.pop();
            leg.pop_back();
            continue;
        }

        visited[curr.index] = true;

        // if we have not seen this species, add it to the leg and run all it's queries
        leg.push_back(curr);

        for (auto q : queries[curr.index])
        {
            int q_index = q.first;
            int q_age = q.second;

            // run a binary search on leg to find oldest ancestor of curr not older than age
            int l = 0;
            int r = leg.size() - 1;
            while (l != r)
            {
                int middle = (l + r) / 2;
                if (leg[middle].age > q_age)
                    l = middle + 1;
                else
                    r = middle;
            }
            answers.emplace_back(q_index, leg[l].name);
        }

        // add all children to the stack
        for (species sp : tree[curr.index])
            s.push(sp);
    }

    // sort answers array and produce output
    sort(answers.begin(), answers.end());

    for (int i = 0; i < q; i++)
    {
        cout << answers[i].second;
        if (i != q - 1)
            cout << " ";
    }
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
        run();
}
