#include <iostream>

using namespace std;

void test()
{
    int size;
    cin >> size;
    
    double dropped = 0;
    double temp;
    for (int i = 0; i < size; i++)
    {
        //consume input in any case
        cin >> temp;

        //if current stone still stands abort
        if (i > dropped)
            continue;

        if (i + temp - 1 > dropped)
            dropped = i + temp - 1;
    }

    if (dropped > size)
        dropped = size-1;
    cout << dropped + 1 << "\n";
}

int main()
{
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        test();
    }
    return 0;
}
