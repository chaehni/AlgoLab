#include <iostream>


using namespace std;

void sum()
{
    int size;
    cin >> size;

    int temp;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        cin >> temp;
        sum += temp;
    }
    cout << sum << "\n";
}

int main()
{
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        sum();
    }
}
