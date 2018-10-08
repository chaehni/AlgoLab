#include <iostream>
#include <vector>

using namespace std;

void run(){

    int n; cin >> n; // #defenders
    int m; cin >> m; // #attackers
    int k; cin >> k; // attacker strength

    vector<int> defence(n);
    vector<int> cum_def(n);

    cin >> defence[0];
    cum_def[0] = defence[0];
    for (int i = 1; i < n; i++){
        cin >> defence[i];
        cum_def[i] = cum_def[i-1] + defence[i];
    }
    
    //sliding window
    int i = 0;
    int j = 0;
    vector<int> walls(n,0); // ith element saves the length of the defence-wall of value k that ends in i, if no wall ends there value is 0
    int cnt = 0;

    while (i < n){
        // get defence value uf interval [j, i]
        int value = cum_def[i] - cum_def[j] + defence[j];
        if (value == k){
            walls[i] = i-j+1;
            if (i == 0){
            }
            i++; j++;
        } else if (value < k){
            i++;
        } else if (value > k) {
            if (i == j){
                i++;
            } else {
                j++;
            }
        }
    }
    
    vector<vector<int>> table(m+1, vector<int>(n)); // table[i][j] saves the biggest value when first m attacker attack first j defenders

    for (int j = 0; j < n; j++){
        table[0][j] = 0;   // 0 attackers cannot attack any value
    }
    for (int i = 1; i < m+1; i++){
        table[i][0] = walls[0]; // can the first defender be attacked? (v0 == k)
    }

    for (int i = 1; i < m+1; i++){
        for(int j = 1; j < n; j++){
            table[i][j] = max(table[i][j-1], walls[j]+table[i-1][j-walls[j]]); // either don't pick the interval ending in j or pick it plus the maximum from j-interval_length
        }
    }

    if (table[m-1][n-1] != table[m][n-1]){
        cout << table[m][n-1] << "\n";
    } else {
        cout << "fail" << "\n";
    }
        
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}