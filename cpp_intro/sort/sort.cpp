#include <iostream>
#include <list>


using namespace std;

void run()
{
    int n;
    cin >> n;

    list<int> l;

    int temp;
    for (int i = 0; i<n; i++){
        cin >> temp;
        l.push_back(temp);
    }

    int x; cin >> x;

    if (x == 0)
        l.sort();
    if (x != 0)
        l.sort(greater<int>());
    
    for (int e: l)
        cout << e << " ";
    
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
