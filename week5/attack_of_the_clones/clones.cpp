#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Jedi{
    int start;
    int end;
};

void run(){
    int n, m; cin >> n >> m;
    cout << "n is " << n << " m is " << m << endl; 

    vector<Jedi> jedis(n);
    map<int, int> count;

    for (int i = 0; i < n; i++){
        int s, e; cin >> s >> e;

        jedis[i].start = s;
        jedis[i].end = e;

        count[s]++;
        count[e]--;

        if (s > e){
            count[1]++;
        }

    }

    // find segment with 0 jedis
    int c = -1;
    int overlaps = 0;
    int flag = false;
    for (int i = 1; i < m +1; i++){
        overlaps += count[i];
        if (overlaps == 0){
            if (flag)
                c = i;
            else
                flag = true;
        }else{
            if (flag)
                flag = false;
        }
    }

    //cout << "c is: " << c << endl;
   
   // we found the empty segment, adapt the start- and end points for every jedi to start from there
    map<int, int> centered;
    for (auto j: jedis){
        int s, e;
        s = j.start;
        e = j.end;
        
        int s_new, e_new;

        if (s > c)
            s_new = s-c;
        else
            s_new = s-c+m;

        if (e > c)
            e_new = e-c;
        else
            e_new = e-c+m;

        if (s <= e && s <= c && c <= e || s > e && (s <= c || e >= c)){
            cout << "!!ERROR!!\n";
        }

        centered[e_new] = s_new; // putting end first since maps are sorted by key   
    }

    //cout << "centered size is: " << centered.size() << endl;

    // Run a EDF scheduler on centered data
    int right_end = -1;
    int cnt = 0;
    for (auto e: centered){
        if (e.second > right_end){
            right_end = e.first;
            cnt++;
        }
    }

    cout << cnt << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}