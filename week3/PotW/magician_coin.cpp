#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


double rec(int k, double m, int depth, int n, double p, vector<vector<double>> &table, vector<double> &probs){

    //if we have the goal of m already, return 1 (shortcut)
    if (k >= m)
        return 1;

    //recursion termination: after the last game n, we need at least m money
    if (depth == n && k >= m)
        return 1;
    if (depth == n && k < m)
        return 0;
    
    //int money = (k > m ? m : k); //table limit is m, if k is bigger than that just cut it back to m since probability will be 1 anyways
    int money = k;

    if (table[k][depth] != -1){ //table limit is m, at this point k will be at smaller than m because of the shortcut above
        return table[k][depth];
    } else {
        double max = 0;
        double prob = probs[depth+1];
        for (int i = 0; i <= money; i++){ //again only loop up to at most m, for larger k we would have taken the shortcut
            double temp = p * rec(k+i, m, depth+1, n, prob, table, probs) + (1-p) * rec(k-i, m, depth+1, n, prob, table, probs);
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
    cout << rec(k,m,0,n,probs[0], max_prob, probs) << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}