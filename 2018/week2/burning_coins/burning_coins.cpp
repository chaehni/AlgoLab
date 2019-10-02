#include <iostream>
#include <vector>

using namespace std;

void run(){
    int n; cin >> n;
    vector<int> numbers(n);
    vector<vector<int>> me(n, vector<int>(n)); //use vectors as stack arrays would create a seg fault
    vector<vector<int>> they(n, vector<int>(n)); //for large n (stack overflow)

    for (int i = 0; i < n; i++){
        int temp; cin >> temp;
        numbers[i] = temp;
    }

    //fill in the the two tables in diagonal fashion, starting with the table where the main player goes first
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n-k; i++){
            int j = i+k;
            
            if (i == j){
                me[i][i] = numbers[i];
                they[i][i] = 0;
            } else {
                me[i][j] = max(numbers[i] + they[i+1][j], numbers[j] + they[i][j-1]);
                they[i][j] = min(me[i+1][j], me[i][j-1]);
            }
        }
    }

    cout << me[0][n-1] << "\n";

}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}