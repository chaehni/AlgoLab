#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int right_end;

struct Boat{
    int ring;
    int length;
};

int compare_boats(Boat b1, Boat b2){
    return max(b1.ring, right_end + b1.length) < max(b2.ring, right_end + b2.length);
}

void run(){
    int n; cin >> n;
    vector<Boat> boats (n);

    for (int i = 0; i < n; i++){
        cin >> boats[i].length;
        cin >> boats[i].ring;
    }

    int count = 0;
    right_end = INT32_MIN;
    for (int i = 0; i < n; i++){
        
        // sort boats by earliest finish position
        sort(boats.begin() + i, boats.end(), compare_boats);

        if (right_end <= boats[i].ring){  // we can place the boat
            right_end = max(right_end + boats[i].length, boats[i].ring);
            count++;
        }
    }

    cout << count << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}