#include <iostream>
#include <map>
#include <list>


using namespace std;

void run()
{
    int q;
    cin >> q;

    multimap<string, int> m;

    int x;
    string b;
    for (int i = 0; i<q; i++){
        cin >> x;
        cin >> b;
        if (x == 0){
            m.erase(b);
        } else {
            m.insert(make_pair(b, x));
            //cout << "added " << x << " with key " << b << endl;
        }
    }

    //cout << m.size();

    string key; cin >> key;
    int cnt = 0;
    list<int> l; 

    for (auto e: m){
        //cout << "found element " << e.second << " with key " << e.first << endl;
        if (e.first.compare(key) == 0)
            l.push_back(e.second);
            cnt++;
    }
    if (cnt == 0){
        cout << "Empty";
    } else {
        l.sort();
        for (auto e: l){
            cout << e << " ";
        }
    }
    cout << "\n";
    
}

int main()
{
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        run();
    }
}
