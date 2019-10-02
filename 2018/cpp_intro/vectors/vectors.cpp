#include <iostream>
#include <vector>


using namespace std;

void run()
{
    int n;
    cin >> n;

    vector<int> vec;

    int temp;
    for (int i = 0; i < n; i++){
        cin >> temp;
        vec.push_back(temp);
    }

    int del; cin >> del;
    int start; cin >> start;
    int end; cin >> end;

    vec.erase(vec.begin()+del);
    vec.erase(vec.begin()+start, vec.begin()+end+1);

    if (vec.size() == 0){
        cout << "Empty";
    } else {
        for (int i = 0; i < vec.size(); i++){
            cout << vec[i] << " ";
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
