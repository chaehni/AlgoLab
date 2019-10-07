#include <iostream>

using namespace std;

void test()
{
    int size;
    cin >> size;

    int even = 0;
    int odd = 0;
    int temp;
    int sum = 0;

    for (int i = 0; i < size; i++)
    {
        cin >> temp;
        sum += temp;
        if (sum % 2 == 0)
            even++;
        if (sum % 2 == 1)
            odd++;
    }

    cout << (even * (even - 1)) / 2 + (odd * (odd - 1)) / 2 + even << "\n";
}

int main()
{
    int t;
    cin >> t;
    while (t--)
        test();
}
