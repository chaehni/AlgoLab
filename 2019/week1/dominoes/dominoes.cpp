#include <iostream>

using namespace std;

void run()
{
    int n;
    cin >> n;

    int max_l;
    cin >> max_l; // first dominoe
    max_l++;
    int count = 1;
    for (int i = 2; i <= n; i++)
    {
        // read input in any case
        int temp;
        cin >> temp;
        if (max_l > i)
        {
            count = i;
            max_l = max(max_l, i + temp);
        }
    }
    cout << count << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        run();
    }
}