#include <iostream>
#include <vector>
#include <climits>

using namespace std;


void find(){

    int n, k;
    cin >> n >> k;
    vector<int> partial(n);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        partial[i]=(sum += temp);
    }

    //cout << "here";
    // sliding window to find best indices
    int best_l = 0;
    int best_r = 0;
    int l = 0;
    int r = 0;
    int smallest = INT_MAX;

    while (r < n){
        int cur = (l == 0 ? partial[r] : (partial[r] - partial[l - 1]));

        if (abs(cur - k) < smallest){
            best_l = l;
            best_r = r;
            smallest = abs(cur - k);
        }

        if (cur == k){
            break;
        }

        if (cur < k){
            r++;
            continue;
        }

        if (r > l){
            l++;
        } else {
            r++;
            l++;
        }
                
    }
cout << best_l << " " << best_r << "\n";

}

int main() {
    std::ios_base::sync_with_stdio(false);
    int num_tests;
    cin >> num_tests;
    for (int i = 0; i < num_tests; i++)
    {
        find();
    }
}