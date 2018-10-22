#include <iostream>
#include <vector>
#include <set>

using namespace std;

//Holmes: on even turn --> move black, on odd -> move red, wins if red on target
//Moriarty: on even turn --> move red, on odd -> move black, wins if black on target
//Holmes begins

int play(int moves_so_far, int m, int target, vector<set<int>> &trans, vector<vector<int>> &mem){

    // Basecase
    if (m == target)
        return moves_so_far;

    // return value from memo if available
    if (mem[moves_so_far % 2][m] != -1)
        return mem[moves_so_far % 2][m] + moves_so_far;


    // alternate between maximizing and minimizing number of moves (depending on parity of moves)
    // minimize on odd moves, maximize on even moves
    int mov = (moves_so_far % 2 == 0 ? INT32_MAX : 0);
    for (auto p: trans[m]){
        int temp = play(moves_so_far + 1, p, target, trans, mem);
        if (moves_so_far % 2 == 0 && temp < mov)
            mov = temp;
        if(moves_so_far % 2 == 1 && temp > mov)
            mov = temp;

    }
    mem[moves_so_far % 2][m] = mov - moves_so_far;
    return mov;
}

void run(){
    int n, m; cin >> n >> m;
    int r, b; cin >> r >> b;
    vector<set<int>> trans(n+1);

    for (int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        trans[u].insert(v); 
    }

    vector<vector<int>> mem(2, vector<int>(n+1, -1)); // stores how many moves are needed from position i, 
                                                      // first column (even) max moves, second column (odd) min moves

    int red = play(0, r, n, trans, mem);
    int black = play(0, b, n, trans, mem);

    if(red < black)
        cout << 0 << "\n";

    else if(red > black)
        cout << 1 << "\n";
    
    else if (red % 2 == 1)
        cout << 0 << "\n";

    else cout << 1 << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}