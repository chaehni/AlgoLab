#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


double rec(int k, int m, int depth, int n, vector<vector<double>> &table, vector<double> &probs){

    //recursion termination: after the last game n, we need at least m money
    if (k >= m)
        return 1;
    if (depth == n && k < m)
        return 0;
    
    if (table[k][depth] != -1){
        return table[k][depth];
    } else {
        double max = 0;
        double p = probs[depth];
        for (int i = 0; i <= k; i++){
            double temp = p * rec(k+i, m, depth+1, n, table, probs) + (1-p) * rec(k-i, m, depth+1, n, table, probs);
            if(temp > max)
                max = temp;
        }
        table[k][depth] = max;
        return max;
    }
}

void run(){

    int n; cin >> n;
    int k; cin >> k;
    int m; cin >> m;
    vector<double> probs(n);

    for (int i = 0; i < n; i++){
        double temp; cin >> temp;
        probs[i] = temp;
    }
    
    vector<vector<double>> max_prob(m+1, vector<double>(n, -1));

    cout << fixed << setprecision(5);
    cout << rec(k,m,0,n,max_prob, probs) << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}