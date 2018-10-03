#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

vector<vector<double>> max_prob;
vector<double> probs;

double rec(int k, int m, int depth, int n){

    //recursion termination: after the last game n, we need at least m money
    if (k >= m)
        return 1;
    if (depth == n && k < m)
        return 0;
    
    if (max_prob[k][depth] != -1){
        return max_prob[k][depth];
    } else {
        double max = 0;
        double p = probs[depth];
        for (int i = 0; i <= k; i++){
            double temp = p * rec(k+i, m, depth+1, n) + (1-p) * rec(k-i, m, depth+1, n);
            if(temp > max)
                max = temp;
        }
        max_prob[k][depth] = max;
        return max;
    }
}

void run(){

    int n; cin >> n;
    int k; cin >> k;
    int m; cin >> m;
    probs = vector<double>(n);

    for (int i = 0; i < n; i++){
        double temp; cin >> temp;
        probs[i] = temp;
    }
    
    max_prob = vector<vector<double>> (m+1, vector<double>(n, -1));

    cout << fixed << setprecision(5);
    cout << rec(k,m,0,n) << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}