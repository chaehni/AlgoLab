#include <iostream>
#include <set>


using namespace std;

void run()
{
    int q;
    cin >> q;

    set<int> s;

    int a;
    int b;
    for (int i = 0; i<q; i++){
        cin >> a;
        cin >> b;
        if (a == 0)
            s.insert(b);
        if (a == 1)
            if(s.find(b) != s.end())
                s.erase(s.find(b));
    }

    if (s.size() == 0){
        cout << "Empty";
    } else {
        for (auto e: s){
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
