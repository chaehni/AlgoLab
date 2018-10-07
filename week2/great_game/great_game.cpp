#include <iostream>
#include <vector>
#include <set>

using namespace std;

void run(){
    int n, m; cin >> n >> m;
    int r, b; cin >> n >> m;
    vector<set<int>> trans(m);

    for (int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        trans[u].insert(v); 
    }


    //Holmes: on even turn --> move black, on uneven -> move red, wins if red in goal
    //Moriarty: on even turn --> move red, on uneven -> move black, wins if black in goal
    //Holmes begins




}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}