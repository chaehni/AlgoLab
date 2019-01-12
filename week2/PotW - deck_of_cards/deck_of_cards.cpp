#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void sum()
{
    int n; cin >> n;
    int k; cin >> k;

    vector<int> cards;
    vector<int> partial;
    int sum = 0;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        partial.push_back(sum+=temp);
    }

    int score = INT_MAX;
    int res_i;
    int res_j;
    int i = 0;
    int j = 0;
    int temp;

    while (j < n){

        temp = partial[j] - partial[i-1];
        temp = (i == 0 ? partial[j] : (partial[j] - partial[i-1]));

        if (abs(temp-k) < score){
                score = abs(temp-k);
                res_i = i;
                res_j = j;
            }

        if (temp == k) {
            break;
        } else if (temp < k) {
            j++;
        } else if (temp > k) {
            if (i < j) {
                i++;
            } else {
                j++;
            }
        }
    }

    cout << res_i << " " << res_j << "\n";
}

int main()
{   
    std::ios_base::sync_with_stdio(false);
    int n_tests;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i++)
    {
        sum();
    }
}
