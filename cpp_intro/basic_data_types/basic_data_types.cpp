#include <iostream>
#include <iomanip>



using namespace std;

void test()
{
    int i; cin >> i;
    long l; cin >> l;
    string s; cin >> s;
    double d; cin >> d;

    cout << setprecision(2) << fixed << i << " " << l << " " << s << " " << d << "\n";
}

int main()
{
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        test();
    }
}
