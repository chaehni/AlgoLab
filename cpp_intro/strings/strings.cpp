#include <iostream>
#include <iomanip>



using namespace std;

void reverse(string& str){
    char temp;
    for (int i = 0; i < str.length() / 2; i++){
        temp = str[i];
        str[i] = str[str.length() - i -1];
        str[str.length() - i -1] = temp;
    }
}

void rev_swap (string& s1, string& s2){
    
    reverse(s1);
    reverse(s2);

    char temp;
    temp = s1[0];
    s1[0] = s2[0];
    s2[0] = temp;
}

void run()
{
    string a; cin >> a;
    string b; cin >> b;
    string res;

    cout << a.length() << " " << b.length() << "\n" << a+b << "\n";
    rev_swap(a, b);
    cout << a << " " << b << "\n";
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
